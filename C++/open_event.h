//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_OPEN_EVENT_H
#define HW3_OPEN_EVENT_H

#include "base_event.h"
#include "student.h"

namespace mtm {
    class OpenEvent : public BaseEvent {
    public:
        OpenEvent(const DateWrap &date, const std::string &name);

        BaseEvent *clone() const override;
    };
}


#endif //HW3_OPEN_EVENT_H
