#include "publisher.h"

namespace ChristmasClock {

template <typename EventType>

template <typename EventSubscriber>
void Publisher::subscribe(EventSubscriber& s) {
    m_subscribers.emplace_back(std::reference_wrapper<EventSubscriber>(s));
}

template <typename EventSubscriber>
void Publisher::unsubscribe(EventSubscriber& s) {
    m_subscribers.erase(
        // erase–remove idiom
        std::remove_if(
            m_subscribers.begin(),
            m_subscribers.end(),
            // remove if reference is identical
            [&s](auto i) { return &i.get() == &s; },
            m_subscribers.end()
        )
    )
}

template <typename EventType>
void Publisher::notify(const EventType& e) {
    for(auto s: m_subscribers) {
        s.update(e);
    }
}

}