#ifndef Beehive_h
#define Beehive_h

#include "../bees/bee.h"
#include <memory>
#include <vector>
#include "../util/random.h"
#include "../util/logger.h"
#include "flower_field.h"
#include "queens_chamber.h"
#include <iomanip>
#include <mutex>
#include <ctime>
#include <chrono>
#include <list>

using namespace util;
using namespace std;
using std::mutex;
using world::Flowerfield;
using world::QueensChamber;

namespace bees{
    class Bee;
    class Worker;
    class Drone;
    class Queen;
}

namespace world {
    class Beehive {
    public:
        Beehive(int seed, int simulation_time, int number_of_drones, int number_of_nectar_workers,
                int number_of_pollen_workers);

        void add_bees();

        void start_simulation();

        void stop_simulation();

        void deposit_resource(int id, int number_of_nectar, int number_of_pollens);

        int claim_resource(int resource);

        int checkMinimumTotalResourcesDemanded(int demand);

        void reproduce_bee(string role);

        void remove_bee(int id);

        mutex nectar_accessor_mutex;

        mutex pollen_accessor_mutex;

        mutex print_mutex;

        Flowerfield* flower_field;

        QueensChamber* queens_chamber;

        condition_variable res_cond;

        unique_ptr<random> rp;

        vector<int> bees_perished;

        bool isSimulationStopped;

        bool isBeehiveAvailable = true;
    private:

        void print_statistics();

        vector<unique_ptr<bees::Bee>> beehive_;

        int seed_;

        int number_of_drones_;

        int number_of_nectar_workers_;

        int number_of_pollen_workers_;

        int simulation_time_;   //seconds

        const int min_ = 1;

        const int max_ = 6;

        int id_;

//        static const logger log_{std::ostream& os};

        int total_number_of_pollens_ = 0;

        int total_number_of_nectar_ = 0;

        int total_number_of_pollens_gathered = 0;

        int total_number_of_nectar_gathered = 0;

        int total_number_of_bees_born = 0;

    };
}
#endif