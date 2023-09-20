//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_FESTIVAL_H
#define HW3_FESTIVAL_H

#include "event_container.h"
#include "../partA/date_wrap.h"

namespace mtm {
    class Festival : public EventContainer {
        DateWrap festival_date;
    public:
        Festival(const DateWrap &date);

        void add(const BaseEvent &event) override;
    };
}


#endif //HW3_FESTIVAL_H
