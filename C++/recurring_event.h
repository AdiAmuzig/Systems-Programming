//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_RECURRING_EVENT_H
#define HW3_RECURRING_EVENT_H

#include "event_container.h"
#include "../partA/date_wrap.h"

namespace mtm {
    template<class EventType>
    class RecurringEvent : public EventContainer {
    public:
        RecurringEvent(const DateWrap &first_date, const std::string &name,
                       int num_occurrences, int interval_days);

        void add(const BaseEvent &event) override;
    };
}

namespace mtm {
    template<class EventType>
    RecurringEvent<EventType>::RecurringEvent(
            const DateWrap &first_date, const std::string &name,
            int num_occurrences, int interval_days) {
        if (num_occurrences <= 0) {
            throw InvalidNumber();
        }
        if (interval_days <= 0) {
            throw InvalidInterval();
        }
        for (int i = 0; i < num_occurrences; ++i) {
            EventType new_event(first_date + (i * interval_days), name);
            events.insert(new_event);
        }
    }

    template<class EventType>
    void RecurringEvent<EventType>::add(const BaseEvent &event) {
        throw NotSupported();
    }
}


#endif //HW3_RECURRING_EVENT_H
