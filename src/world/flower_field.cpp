#include <iostream>
#include "flower_field.h"

using namespace world;

/**
 * Flower Filed is acting like a semaphore. It provides synchronized access to a counter
 * so that only a maximum of 10 worker bees caan access the flowerfield.
 */

Flowerfield::Flowerfield(){

}

//get current number of bees occupying the flowers
int Flowerfield::get_current_bees() {
    return bee_counter_;
}

//increase the bees occupying the flowers
void Flowerfield::inc_bees() {
    bee_counter_+=1;
}

//decrease the bees occupying the flowers
void Flowerfield::dec_bees() {
    bee_counter_-=1;
}