//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_EVENT_CONTAINER_H
#define HW3_EVENT_CONTAINER_H

#include "base_event.h"
#include "doubly_linked_list.h"

namespace mtm {
    class EventContainer {
    protected:
        DoublyLinkedList<BaseEvent> events;
        bool badContainer;

    public:

        struct EventIterator {
            DoublyLinkedList<BaseEvent>::Iterator inner_iterator;

            EventIterator();

            EventIterator(const EventIterator &event_iterator) = default;

            EventIterator &operator=(const EventIterator &event_iterator);

            EventIterator &operator++();

            BaseEvent &operator*();

            friend bool operator==(const EventIterator &event_iterator1,
                                   const EventIterator &event_iterator2);
        };

        EventContainer();

        virtual void add(const BaseEvent &event) = 0;

        EventIterator begin() const;

        EventIterator end() const;

        bool containsMultipleSameEvent() const;
    };

    bool operator!=(const mtm::EventContainer::EventIterator &event_iterator1,
                    const mtm::EventContainer::EventIterator &event_iterator2);
}


#endif //HW3_EVENT_CONTAINER_H