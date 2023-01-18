#pragma once

#include <event.hpp>

namespace ChristmasClock {
    enum TouchButton {
        Btn1,
        Btn2, 
        Btn3,
        Btn4,
        Btn5,
        Btn6};

    struct TouchEvent {
        TouchButton buttonIdentifier;
    }
}