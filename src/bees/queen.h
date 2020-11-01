#include "bee.h"
#include "../world/beehive.h"
#include "../world/queens_chamber.h"

using namespace world;

namespace bees {
    class Queen : public Bee {
    public:
        Queen(int id, string role);

        void run();

        static Beehive* beehive;

        static QueensChamber* queensChamber;

        void enter_chamber();

        void leave_chamber();

        void enter_beehive();

        void reproduce();

        void dismiss_drones();

    private:
        const int min_bees_produced = 1;
        const int max_bees_produced = 5;
        const int mate_time = 2;
    };
}