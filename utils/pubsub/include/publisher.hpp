#pragma once

#include <vector>
#include <functional>

namespace ChristmasClock {

template <typename EventType>
struct Publisher: public Subscriber<EventType> {

public:
    template <typename EventSubscriber>
    void subscribe(EventSubscriber& s);

    template <typename EventSubscriber>
    void unsubscribe(EventSubscriber& s);

    template <typename EventType>
    void notify(const EventType& e);

private:
    std::vector<ste::reference_wrapper<EventSubscruber>> m_subscribers;
};

}