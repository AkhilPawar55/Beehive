#include "queens_chamber.h"

using namespace world;

QueensChamber::QueensChamber() : isBusy_{false}{}

bool QueensChamber::checkIfBusy() {
    return isBusy_;
}

void QueensChamber::showAvailable() {
    isBusy_ = false;
}

void QueensChamber::showBusy() {
    isBusy_ = true;
}