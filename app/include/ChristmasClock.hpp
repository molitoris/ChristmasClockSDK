#pragma once

#include "touch.hpp"

namespace ChristmasClock {

class ChristmasClock {
public:
    ChristmasClock();
    ~ChristmasClock() = default;

    // breif    setup all components
    int init();

    // brief    called by the main loop
    void update();
private:
    CapacitiveTouch _touch;
};
}