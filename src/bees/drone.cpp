#include "drone.h"

using std::chrono::seconds;
using std::this_thread::sleep_for;

using namespace bees;

Beehive *Drone::beehive = nullptr;
QueensChamber *Drone::queensChamber = nullptr;

Drone::Drone(int id, string role) : Bee::Bee(id, role, 0, 0) {}

void Drone::run() {
    enter_queens_chamber();
}

void Drone::enter_queens_chamber() {
    {
        lock_guard<mutex> lg{queensChamber->queue_accessor_};

        queensChamber->chamber.push_back(get_id());
    }
    {
        lock_guard<mutex> ul{beehive->print_mutex};
        std::cout << "*QC* DRONE #" << get_id() << " enters chamber"
                  << std::endl;
    }
    doit();
}

void Drone::exit_queens_chamber() {
    {
        lock_guard<mutex> lg{queensChamber->queue_accessor_};

        queensChamber->chamber.pop_front();
    }
    {
        lock_guard<mutex> ul{beehive->print_mutex};
        std::cout << "*QC* DRONE #" << get_id() << " leaves chamber"
                  << std::endl;
        if(!beehive->isSimulationStopped) {
            std::cout << "*QC* DRONE #" << get_id() << " perishes"
                      << std::endl;
            beehive->bees_perished.emplace_back(get_id());
        }else{
//            queensChamber->qcond_.notify_all();
        }
    }
}

void Drone::doit() {
    {
        unique_lock<mutex> ul{queensChamber->queen_accesor_};
        //wait for queen
        queensChamber->qcond_.wait(ul);
        //if queen not busy have erotic sex with queen
        exit_queens_chamber();
    }
}