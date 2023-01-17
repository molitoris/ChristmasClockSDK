#pragma once

namespace ChristmasClock {

/*
 * Abstract class that wishes to be informed
*/


template <typename EventType>
struct Subscriber{
public:
    virtual ~Subscriber(void) {};

    // Abstract event callback function
    virtual void update(EventType &theEvent) = 0;
};

}