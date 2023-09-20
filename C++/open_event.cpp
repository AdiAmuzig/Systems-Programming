//
// Created by adi.amuzig on 21/01/2021.
//

#include "open_event.h"

namespace mtm {
    OpenEvent::OpenEvent(const mtm::DateWrap &date,
                         const std::string &name)
            : BaseEvent(date, name) {
    }

    BaseEvent *OpenEvent::clone() const {
        OpenEvent *new_open_event =
                new OpenEvent(date, name);
        new_open_event->participatingStudents = participatingStudents;
        return new_open_event;
    }
}