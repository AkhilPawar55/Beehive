#ifndef UTIL_random_H
#define UTIL_random_H

#include <random>

namespace util {

    /**
     * A random number generator suitable for generating 64 bit values.
     *
     * @author Sean Strout @ RIT CS
     */
    class random {
    public:
        /**
         * Create a seeded random number generator.
         *
         * @param seed the seed
         */
        random(unsigned long long seed);

        /**
         * Roll the dice to get a random value between min and max (inclusive).
         *
         * @param min smallest value
         * @param max largest value
         * @return random value
         */
        unsigned int roll_dice(unsigned int min, unsigned int max);

    private:
        /**
         * Get the next pseudo-random number.
         *
         * @return next number
         */
        unsigned long long rand();

        /** the mersenne twister generator */
        std::mt19937_64 gen_;

        /** produces random numbers that are uniformly distributed */
        std::uniform_int_distribution<unsigned long long> dis_;
    }; // random

} // util

#endif // UTIL_random_H
