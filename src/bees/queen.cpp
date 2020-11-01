#include "queen.h"

using std::chrono::seconds;
using std::this_thread::sleep_for;

using namespace bees;

Beehive *Queen::beehive = nullptr;
QueensChamber *Queen::queensChamber = nullptr;

Queen::Queen(int id, string role) :
        Bee::Bee(id, role, 0, 0) {}

void Queen::run() {
    int can_produce_number_of_offspring = 0;
    while (!beehive->isSimulationStopped) {
        can_produce_number_of_offspring = beehive->rp->roll_dice(min_bees_produced, max_bees_produced);
        int resources_available = 0;
        while (resources_available == 0 && !queensChamber->chamber.empty()) {
            resources_available = beehive->checkMinimumTotalResourcesDemanded(can_produce_number_of_offspring);
            if (beehive->isSimulationStopped)
                break;
        }
        beehive->claim_resource(resources_available);

        queensChamber->showAvailable();
        queensChamber->qcond_.notify_one();
        queensChamber->showBusy();

        int chance = 0;
        int i = 0;
        while (i < resources_available && !beehive->isSimulationStopped) {
            chance = beehive->rp->roll_dice(0, 100);
            if (chance >= 60) {
                //drone
                beehive->reproduce_bee("Drone");
            } else {
                chance = beehive->rp->roll_dice(0, 100);
                if (chance >= 50) {
                    //nectar worker
                    beehive->reproduce_bee("Nectar Worker");
                } else {
                    //pollen worker
                    beehive->reproduce_bee("Pollen Worker");
                }
            }
            ++i;
        }
        sleep_for(seconds(mate_time));
    }
    //suspend each drone
    queensChamber->qcond_.notify_all();
}