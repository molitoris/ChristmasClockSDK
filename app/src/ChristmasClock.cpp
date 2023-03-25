#include <stdio.h>

#include "ChristmasClock.hpp"
#include "touch.hpp"

namespace ChristmasClock {

ChristmasClock::ChristmasClock(): _touch(19, 18, 17) {}

int ChristmasClock::init() {
    // initialization successfull
    return 0;
}

void ChristmasClock::update() {
    printf("Update christmas clock");
    _touch.readTouchStatus();
}

}