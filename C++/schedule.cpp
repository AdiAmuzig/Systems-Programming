//
// Created by adi.amuzig on 21/01/2021.
//

#include "schedule.h"
#include "../partB/open_event.h"

namespace mtm {
    Schedule::Schedule() :
            events_schedule() {
    }

    void Schedule::addEvents(const EventContainer &event_container) {
        EventContainer::EventIterator iterator = event_container.begin();
        if (event_container.containsMultipleSameEvent()){
            throw EventAlreadyExists();
        }
        while (!(iterator == event_container.end())) {
            if (events_schedule.dataExists(*iterator)) {
                throw EventAlreadyExists();
            }
            ++iterator;
        }
        iterator = event_container.begin();
        while (!(iterator == event_container.end())) {
            events_schedule.insert(*iterator);
            ++iterator;
        }
    }

    void Schedule::registerToEvent(const DateWrap &date,
                                   const char *name, int student) {
        OpenEvent temp_event(date, name);
        if (!(events_schedule.dataExists(temp_event))) {
            throw EventDoesNotExist();
        }
        DoublyLinkedList<BaseEvent>::Iterator iterator =
                events_schedule.returnHead();
        while (!(*iterator == temp_event)) {
            ++iterator;
        }
        (*iterator).registerParticipant(student);
    }

    void Schedule::unregisterFromEvent(const DateWrap &date,
                                       const char *name, int student) {
        OpenEvent temp_event(date, name);
        if (!(events_schedule.dataExists(temp_event))) {
            throw EventDoesNotExist();
        }
        DoublyLinkedList<BaseEvent>::Iterator iterator =
                events_schedule.returnHead();
        while (!(*iterator == temp_event)) {
            ++iterator;
        }
        (*iterator).unregisterParticipant(student);
    }

    void Schedule::printAllEvents() const {
        DoublyLinkedList<BaseEvent>::Iterator iterator =
                events_schedule.returnHead();
        int size = events_schedule.getSize();
        for (int i = 0; i < size; ++i) {
            (*iterator).printShort(cout);
            cout << endl;
            ++iterator;
        }
    }

    void Schedule::printMonthEvents(int month, int year) const {
        DoublyLinkedList<BaseEvent>::Iterator iterator =
                events_schedule.returnHead();
        int size = events_schedule.getSize();
        for (int i = 0; i < size; ++i) {
            DateWrap date = (*iterator).getDate();
            if (date.month() == month && date.year() == year) {
                (*iterator).printShort(cout);
                cout << endl;
            }
            ++iterator;
        }
    }

    void Schedule::printEventDetails(const DateWrap &date,
                                     const char *name) const {
        OpenEvent temp_event(date, name);
        if (!(events_schedule.dataExists(temp_event))) {
            throw EventDoesNotExist();
        }
        DoublyLinkedList<BaseEvent>::Iterator iterator =
                events_schedule.returnHead();
        while (!(*iterator == temp_event)) {
            ++iterator;
        }
        (*iterator).printLong(cout);
        cout << endl;
    }
}