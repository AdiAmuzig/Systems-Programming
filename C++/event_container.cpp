//
// Created by adi.amuzig on 21/01/2021.
//

#include "event_container.h"

namespace mtm {

    EventContainer::EventIterator::EventIterator() :
            inner_iterator() {
    }

    EventContainer::EventIterator
    &EventContainer::EventIterator::operator=(
            const EventContainer::EventIterator &event_iterator) {
        inner_iterator = event_iterator.inner_iterator;
        return *this;
    }

    EventContainer::EventIterator
    &EventContainer::EventIterator::operator++() {
        if (inner_iterator.isLast()) {
            DoublyLinkedList<BaseEvent>::Iterator new_iterator;
            inner_iterator = new_iterator;
        } else {
            ++inner_iterator;
        }
        return *this;
    }

    bool operator  ==(const EventContainer::EventIterator &event_iterator1,
                    const EventContainer::EventIterator &event_iterator2) {
        return (event_iterator1.inner_iterator ==
                event_iterator2.inner_iterator);
    }

    BaseEvent &EventContainer::EventIterator::operator*() {
        return *(inner_iterator);
    }

    bool operator!=(const EventContainer::EventIterator &event_iterator1,
                    const EventContainer::EventIterator &event_iterator2) {
        return (!(event_iterator1 == event_iterator2));
    }

    EventContainer::EventContainer() :
            events(),
            badContainer(false){
    }

    EventContainer::EventIterator EventContainer::begin() const {
        EventIterator iterator;
        iterator.inner_iterator = events.returnHead();
        return iterator;
    }

    EventContainer::EventIterator EventContainer::end() const {
        EventIterator iterator;
        return iterator;
    }

    bool EventContainer::containsMultipleSameEvent() const {
        return badContainer;
    }
}
