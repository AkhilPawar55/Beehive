#include "bee.h"
#include "../world/beehive.h"

using namespace world;

namespace bees {

    /**
     * A female bee who has the specific job of gathering resources (nectar or pollen) from a field of flowers
     */

    class Worker : public Bee {
    public:
        Worker(int id, string role, int nectar_units, int pollen_units);

        //Run method for the bee to be invoked
        void run();

        static Flowerfield* flower_field;

        static Beehive* beehive;

    private:
        void enter_field();

        void leave_field();

        ~Worker();

        //return the number of nectar this worker bee can gather
        int get_nectar_units();

        //return the number of pollen this worker bee can gather
        int get_pollen_units();

        //number of nectar this worker bee can gather
        int nectar_units_ = 0;

        //number of pollen this worker bee can gather
        int pollen_units_ = 0;
    };
}