#include <stdio.h>

#include "ChristmasClock.hpp"
#include "touch.hpp"

namespace ChristmasClock {

ChristmasClock::ChristmasClock(): _touch(19, 18, 17) {}

int ChristmasClock::init() {
    auto res = _touch.init();
    if(res != 0) {
        printf("Failed to configure touch: %d\n", res);
        return res;
    }

    // initialization successfull
    printf("Startup successfull");
    return 0;
}

void ChristmasClock::update() {
    printf("Update christmas clock\n");
    _touch.readTouchStatus();
}

}