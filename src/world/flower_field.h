#ifndef Flower_h
#define Flower_h

#include <mutex>
#include <condition_variable>

using std::mutex;

namespace world {
    /**
     * Flower Filed is acting like a semaphore. It provides synchronized access to a counter
     * so that only a maximum of 10 worker bees caan access the flowerfield.
     */

    class Flowerfield {
    public:
        Flowerfield();

        //mutex for accessing the flowers
        mutex collector_mutex;

        mutex bee_smutex;

        //condition variable
        std::condition_variable cond;

        //increase the bees occupying the flowers
        void inc_bees();

        //decrease the bees occupying the flowers
        void dec_bees();

        //get the current flowers occupied by bees
        int get_current_bees();

        //max flowers
        const int max_bee = 10;

        //current flowers occupied by bees
        int bee_counter_ = 0;
    };
}
#endif