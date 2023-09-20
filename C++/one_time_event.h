//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_ONE_TIME_EVENT_H
#define HW3_ONE_TIME_EVENT_H

#include "event_container.h"
#include "../partA/date_wrap.h"
#include "student.h"

namespace mtm {
    template<class EventType>
    class OneTimeEvent : public EventContainer {
    public:
        OneTimeEvent(const DateWrap &date, const std::string &name);

        void add(const BaseEvent &event) override;
    };
}

namespace mtm {
    template<class EventType>
    OneTimeEvent<EventType>::OneTimeEvent(const DateWrap &date,
                                          const std::string &name) {
        EventType new_event(date, name);
        events.insert(new_event);
    }

    template<class EventType>
    void OneTimeEvent<EventType>::add(const BaseEvent &event) {
        throw NotSupported();
    }
}


#endif //HW3_ONE_TIME_EVENT_H
