#include "beehive.h"
#include "../bees/worker.h"
#include "../bees/queen.h"
#include "../bees/drone.h"

using namespace world;
using namespace util;
using std::lock_guard;

Beehive::Beehive(int seed, int simulation_time, int number_of_drones, int number_of_nectar_workers,
                 int number_of_pollen_workers) :
        seed_(seed),
        simulation_time_(simulation_time),
        number_of_drones_(number_of_drones),
        number_of_nectar_workers_(number_of_nectar_workers),
        number_of_pollen_workers_(number_of_pollen_workers),
        rp{make_unique<random>(seed_)},
        id_(0),
        flower_field(new Flowerfield()),
        queens_chamber(new QueensChamber()),
        isSimulationStopped(false) {
    bees::Worker::flower_field = this->flower_field;
    bees::Worker::beehive = this;
    bees::Queen::beehive = this;
    bees::Drone::beehive = this;
    bees::Queen::queensChamber = this->queens_chamber;
    bees::Drone::queensChamber = this->queens_chamber;
    cout << "Seed: " << seed_ << endl;
    cout << "Simulation time: " << simulation_time_ << endl;
    cout << "Starting drones: " << number_of_drones_ << endl;
    cout << "Starting nectar workers: " << number_of_nectar_workers_ << endl;
    cout << "Starting pollen workers: " << number_of_pollen_workers_ << endl;
}

void Beehive::add_bees() {
    // add bees to the list
    beehive_.emplace_back(bees::Bee::create_a_bee(++id_, "Queen", 0, 0));
    cout << "*B* QUEEN #" << id_ << " is born" << endl;
    total_number_of_bees_born += 1;
    for (int i = 0; i < number_of_drones_; ++i) {
        beehive_.emplace_back(bees::Bee::create_a_bee(++id_, "Drone", 0, 0));
        cout << "*B* DRONE #" << id_ << " is born" << endl;
        total_number_of_bees_born += 1;
    }
    for (int i = 0; i < number_of_nectar_workers_; ++i) {
        int number_of_nectar_per_worker_ = rp->roll_dice(min_, max_);
        beehive_.emplace_back(
                bees::Bee::create_a_bee(++id_, "Nectar Worker", number_of_nectar_per_worker_, 0));
        cout << "*B* NECTAR(" << number_of_nectar_per_worker_ << ") WORKER #" << id_ << " is born" << endl;
        total_number_of_bees_born += 1;
    }
    for (int i = 0; i < number_of_pollen_workers_; ++i) {
        int number_of_pollens_per_worker_ = rp->roll_dice(min_, max_);
        beehive_.emplace_back(
                bees::Bee::create_a_bee(++id_, "Pollen Worker", 0, number_of_pollens_per_worker_));
        cout << "*B* POLLEN(" << number_of_pollens_per_worker_ << ") WORKER #" << id_ << " is born" << endl;
        total_number_of_bees_born += 1;
    }
}


void Beehive::reproduce_bee(string role) {
    if (role == "Drone") {
        {
            lock_guard<mutex> lg{print_mutex};
            beehive_.emplace_back(bees::Bee::create_a_bee(++id_, "Drone", 0, 0));
            cout << "*B* DRONE #" << id_ << " is born" << endl;
        }
    } else if (role == "Nectar Worker") {
        {
            lock_guard<mutex> lg{print_mutex};
            int number_of_nectar_per_worker_ = rp->roll_dice(min_, max_);
            beehive_.emplace_back(
                    bees::Bee::create_a_bee(++id_, "Nectar Worker", number_of_nectar_per_worker_, 0));
            cout << "*B* NECTAR(" << number_of_nectar_per_worker_ << ") WORKER #" << id_ << " is born" << endl;
        }
    } else if (role == "Pollen Worker") {
        {
            lock_guard<mutex> lg{print_mutex};
            int number_of_pollens_per_worker_ = rp->roll_dice(min_, max_);
            beehive_.emplace_back(
                    bees::Bee::create_a_bee(++id_, "Pollen Worker", 0, number_of_pollens_per_worker_));
            cout << "*B* POLLEN(" << number_of_pollens_per_worker_ << ") WORKER #" << id_ << " is born" << endl;
        }
    }
    beehive_.back()->start();
    total_number_of_bees_born += 1;
}

void Beehive::remove_bee(int id) {
    for (auto itr = beehive_.begin(); itr != beehive_.end(); ++itr) {
        if (itr->get()->get_id() == id) {
            beehive_.erase(itr);
        }
    }
}

void Beehive::start_simulation() {
    cout << "*BH* Beehive begins buzzing!" << endl;
    for (int i = 0; i < beehive_.size(); i++) {
        int j = rp->roll_dice(0,beehive_.size());
        try {
            beehive_[i]->start();
//            remove_bee(beehive_[j]->get_id());
        }
        catch (const exception &e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }
    this_thread::sleep_for(std::chrono::seconds(simulation_time_));
    stop_simulation();
}

void Beehive::stop_simulation() {
    cout << "*BH* stops simulation!" << endl;
    isSimulationStopped = true;
    queens_chamber->qcond_.notify_all();
    flower_field->cond.notify_all();
    for (int i = 0; i < beehive_.size(); ++i) {
        try {
            beehive_[i]->join();
        }
        catch (const exception &e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }
    cout << "*BH* Beehive stops buzzing!" << endl;
    print_statistics();
}

void Beehive::deposit_resource(int id, int number_of_nectar, int number_of_pollens) {
    if (number_of_pollens == 0) {
        {
            lock_guard<mutex> lgn{nectar_accessor_mutex};

            total_number_of_nectar_ += number_of_nectar;
            total_number_of_nectar_gathered += number_of_nectar;
            {
                lock_guard<mutex> lg{print_mutex};
                std::cout << "*BH* NECTAR(" << number_of_nectar << ") WORKER #" << id << " deposits resources"
                          << std::endl;
            }
        }
        res_cond.notify_all();
    } else if (number_of_nectar == 0) {
        {
            lock_guard<mutex> lgp{pollen_accessor_mutex};

            total_number_of_pollens_ += number_of_pollens;
            total_number_of_pollens_gathered += number_of_pollens;
            {
                lock_guard<mutex> lg{print_mutex};
                std::cout << "*BH* POLLEN(" << number_of_pollens << ") WORKER #" << id << " deposits resources"
                          << std::endl;
            }
        }
        res_cond.notify_all();
    }
}

int Beehive::claim_resource(int resource) {
    bool hasResource_nectar = false;
    bool hasResource_pollen = false;
    {
        lock_guard<mutex> lgn{nectar_accessor_mutex};

        if (total_number_of_nectar_ >= resource) {
            hasResource_nectar = true;
        }
    }
    {
        lock_guard<mutex> lgp{pollen_accessor_mutex};
        if (total_number_of_pollens_ >= resource) {
            hasResource_pollen = true;
        }
    }
    res_cond.notify_all();
    if (hasResource_nectar && hasResource_pollen) {
        {
            lock_guard<mutex> lgn{nectar_accessor_mutex};

            total_number_of_nectar_ -= resource;
        }
        {
            lock_guard<mutex> lgp{pollen_accessor_mutex};

            total_number_of_pollens_ -= resource;
        }
        res_cond.notify_all();
        return 1;
    } else
        return 0;
}

int Beehive::checkMinimumTotalResourcesDemanded(int demand) {
    int nectar = 0;
    int pollen= 0;
    {
        lock_guard<mutex> lg{nectar_accessor_mutex};
        if(total_number_of_nectar_ < demand)
            nectar = total_number_of_nectar_;
        else if(total_number_of_nectar_ >= demand)
            nectar = demand;
    }
    {
        lock_guard<mutex> lg{pollen_accessor_mutex};
        if(total_number_of_pollens_ < demand)
            pollen = total_number_of_pollens_;
        else if(total_number_of_pollens_ >= demand)
            pollen = demand;
    }
    res_cond.notify_all();
    if(nectar < pollen)
        return nectar;
    else if(nectar > pollen)
        return pollen;
    else if(nectar == pollen)
        return nectar;
}

void Beehive::print_statistics() {
    std::cout<<"STATISTICS"<<std::endl;
    std::cout<<"=========="<<std::endl;
    std::cout<<"Bees born: "<<total_number_of_bees_born<<std::endl;
    std::cout<<"Bees perished: "<<bees_perished.size()<<std::endl;
    for(int i = 0; i<bees_perished.size(); ++i){
        std::cout<<"\t"<<*(beehive_[bees_perished[i]-1]);
    }
    std::cout<<"Nectar remaining: "<<total_number_of_nectar_<<std::endl;
    std::cout<<"Pollen remaining: "<<total_number_of_pollens_<<std::endl;
    std::cout<<"Nectar gathered: "<<total_number_of_nectar_gathered<<std::endl;
    std::cout<<"Pollen gathered: "<<total_number_of_pollens_gathered<<std::endl;
}