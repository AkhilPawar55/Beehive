#ifndef Worker_h
#define Worker_h

#include "worker.h"
#include <chrono>

using namespace bees;
using std::lock_guard;
using std::mutex;
using namespace world;
using std::chrono::seconds;
using std::this_thread::sleep_for;

/**
  * A female bee who has the specific job of gathering resources (nectar or pollen) from a field of flowers
  */
Flowerfield *Worker::flower_field = nullptr;
Beehive *Worker::beehive = nullptr;

Worker::Worker(int id, string role, int nectar_units, int pollen_units) :
        Bee::Bee(id, role, nectar_units, pollen_units),
        nectar_units_(nectar_units),
        pollen_units_(pollen_units) {}

//Run method for the bee to be invoked
void Worker::run() {
    int resources_claimed = 0;
    do {
        //enter field
        enter_field();

        {
            lock_guard<mutex> lg{beehive->print_mutex};
            if (get_pollen_units() == 0) {
                std::cout << "*FF* NECTAR(" << get_nectar_units() << ") WORKER #" << get_id() << " enters field"
                          << std::endl;
            } else if (get_nectar_units() == 0) {
                std::cout << "*FF* POLLEN(" << get_pollen_units() << ") WORKER #" << get_id() << " enters field"
                          << std::endl;
            }
        }
        //sleep for number_of_resources * 1 seconds(gather resources)
        sleep_for(seconds(getNectar_units_() + get_pollen_units()));
        //leave field

        {
            lock_guard<mutex> lg{beehive->print_mutex};
            if (get_pollen_units() == 0)
                std::cout << "*FF* NECTAR(" << get_nectar_units() << ") WORKER #" << get_id() << " leaves field"
                          << std::endl;
            else if (get_nectar_units() == 0)
                std::cout << "*FF* POLLEN(" << get_pollen_units() << ") WORKER #" << get_id() << " leaves field"
                          << std::endl;
        }

        leave_field();

        //deposit to beehive
        beehive->deposit_resource(get_id(), nectar_units_, pollen_units_);

        if (beehive->isSimulationStopped) {
            flower_field->cond.notify_all();
            beehive->res_cond.notify_all();
            break;
        }

        //claim resource
        resources_claimed = beehive->claim_resource(1);
        if (resources_claimed == 0) {

        } else {
            {
                lock_guard<mutex> lg{beehive->print_mutex};
                if (get_pollen_units() == 0)
                    std::cout << "*W* NECTAR(" << get_nectar_units() << ") WORKER #" << get_id() << " is refueling"
                              << std::endl;
                else if (get_nectar_units() == 0)
                    std::cout << "*W* POLLEN(" << get_pollen_units() << ") WORKER #" << get_id() << " is refueling"
                              << std::endl;
            }
        }
    } while (resources_claimed > 0);
    if (resources_claimed == 0) {
        {
            lock_guard<mutex> lg{beehive->print_mutex};
            if (get_pollen_units() == 0)
                std::cout << "*BH* NECTAR(" << get_nectar_units() << ") WORKER #" << get_id() << " perished!"
                          << std::endl;
            else if (get_nectar_units() == 0)
                std::cout << "*BH* POLLEN(" << get_pollen_units() << ") WORKER #" << get_id() << " perished!"
                          << std::endl;
            beehive->bees_perished.emplace_back(get_id());
        }
    }
    beehive->res_cond.notify_all();

}

//return the number of nectar this worker bee can gather
int Worker::get_nectar_units() {
    return nectar_units_;
}

//return the number of nectar this worker bee can gather
int Worker::get_pollen_units() {
    return pollen_units_;
}

void Worker::enter_field() {

    unique_lock<mutex> ul{flower_field->collector_mutex};
    flower_field->cond.wait(ul, [this] { return flower_field->bee_counter_ < flower_field->max_bee; });
    //inc count
    flower_field->bee_counter_++;
}

void Worker::leave_field() {
    lock_guard<mutex> lg{flower_field->bee_smutex};
    flower_field->bee_counter_--;
    flower_field->cond.notify_all();
}

Worker::~Worker() {

}

#endif