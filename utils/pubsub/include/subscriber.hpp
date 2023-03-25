#pragma once

namespace ChristmasClock {

// Define the EventType template
template<typename T>
struct EventType {
    T data;
};

template<typename T>
struct Subscriber {
    virtual ~Subscriber() = default;
    virtual void update(const EventType<T>&) = 0;
};

}