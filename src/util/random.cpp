#include "random.h"

using util::random;

using std::random_device;

random::random(unsigned long long seed) :
        gen_{seed},
        dis_{} {
}

unsigned int random::roll_dice(unsigned int min, unsigned int max) {
    return min + static_cast<unsigned int>(rand() % (max - min + 1));
}

unsigned long long random::rand() {
    return dis_(gen_);
}
