//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_BASE_EVENT_H
#define HW3_BASE_EVENT_H

#include "../partA/date_wrap.h"
#include "doubly_linked_list.h"
#include "student.h"
#include "exception"
#include <cstring>
#include <iostream>

using std::ostream;
using std::endl;

namespace mtm {
    class BaseEvent {
    protected:
        DateWrap date;
        const std::string name;
        DoublyLinkedList<Student> participatingStudents;

        static void checkLegalStudent(Student student);

    public:
        const std::string &getName() const;

        int getSize() const;

        BaseEvent(const DateWrap &date, const std::string &given_name);

        virtual ~BaseEvent() = default;

        virtual void registerParticipant(const int &student_id);

        void unregisterParticipant(const int &student_id);

        ostream &printShort(ostream &output);

        ostream &printLong(ostream &output);

        virtual BaseEvent *clone() const = 0;

        const DateWrap &getDate() const;

        friend bool operator==(const BaseEvent &event1,
                               const BaseEvent &event2);

        friend bool operator<(const BaseEvent &event1,
                              const BaseEvent &event2);
    };

    bool operator!=(const BaseEvent &event1, const BaseEvent &event2);
}


#endif //HW3_BASE_EVENT_H
