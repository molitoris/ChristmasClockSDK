#pragma once

#include "subscriber.hpp"

#include <vector>
#include <functional>

namespace ChristmasClock {

template<typename T>
struct Publisher : public Subscriber<T> {

    void subscribe(Subscriber<T>& s);
    void unsubscribe(Subscriber<T>& s);
    void publish(const EventType<T>& event);
private:
    std::vector<std::reference_wrapper<Subscriber<T>>> subscribers;
};

}