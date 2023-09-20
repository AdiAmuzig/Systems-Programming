//
// Created by adi.amuzig on 21/01/2021.
//

#include "festival.h"

namespace mtm {
    Festival::Festival(const DateWrap &date) :
            EventContainer(),
            festival_date(date) {
    }

    void Festival::add(const BaseEvent &event) {
        if (!(event.getDate() == festival_date)) {
            throw DateMismatch();
        }
        if (events.dataExists(event)){
            badContainer = true;
        }
        events.insert(event);
    }
}
