#include "publisher.hpp"

namespace ChristmasClock {


// Add a subscriber to the list of subscribers
template<typename T>
void Publisher<T>::subscribe(Subscriber<T>& s) {
    subscribers.emplace_back(std::reference_wrapper<Subscriber<T>>(s));
}

// Remove a subscriber from the list of subscribers
template<typename T>
void Publisher<T>::unsubscribe(Subscriber<T>& s) {
    subscribers.erase(
        // erase–remove idiom
        std::remove_if(
            subscribers.begin(),
            subscribers.end(),
            // remove if reference is identical
            [&s](auto i) { return &i.get() == &s; },
            subscribers.end()
        )
    );
}

// Publish an event to all subscribers
template<typename T>
void Publisher<T>::publish(const EventType<T>& event) {
    for (auto s : subscribers) {
        s.update(event);
    }
}

}