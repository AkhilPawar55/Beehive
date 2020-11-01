#include "bee.h"
#include "../world/queens_chamber.h"

using namespace world;

namespace bees {

    class Drone : public Bee {
    public:
        Drone(int id, string role);

        void run();

        static Beehive* beehive;

        static QueensChamber* queensChamber;

        void enter_queens_chamber();

        void exit_queens_chamber();

        void doit();

    private:
        const int mate_time = 2; //seconds
    };
}
