//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_SCHEDULE_H
#define HW3_SCHEDULE_H

#include "../partB/event_container.h"
#include "../partA/date_wrap.h"
#include <iostream>

using std::cout;

namespace mtm {
    class Schedule {
        DoublyLinkedList<BaseEvent> events_schedule;
    public:
        Schedule();

        void addEvents(const EventContainer &event_container);

        void registerToEvent(const DateWrap &date,
                             const char *name, int student);

        void unregisterFromEvent(const DateWrap &date,
                                 const char *name, int student);

        void printAllEvents() const;

        void printMonthEvents(int month, int year) const;

        void printEventDetails(const DateWrap &date, const char *name) const;

        template<class predict>
        void printSomeEvents(predict predict_function,
                             bool verbose = false) const;
    };
}

namespace mtm {
    template<class predict>
    void Schedule::printSomeEvents(predict predict_function,
                                   bool verbose) const {
        DoublyLinkedList<BaseEvent>::Iterator iterator =
                events_schedule.returnHead();
        int size = events_schedule.getSize();
        for (int i = 0; i < size; ++i) {
            if (predict_function(*iterator)) {
                if (verbose) {
                    (*iterator).printLong(cout);
                    cout << endl;
                } else {
                    (*iterator).printShort(cout);
                    cout << endl;
                }
            }
            ++iterator;
        }
    }
}

#endif //HW3_SCHEDULE_H
