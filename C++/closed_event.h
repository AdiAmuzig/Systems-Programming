//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_CLOSED_EVENT_H
#define HW3_CLOSED_EVENT_H

#include "base_event.h"
#include "student.h"

namespace mtm {
    class ClosedEvent : public BaseEvent {
        DoublyLinkedList<Student> invitedStudents;
    public:
        ClosedEvent(const DateWrap &date, const std::string &name);

        void addInvitee(int student_id);

        void registerParticipant(const int &student_id) override;

        BaseEvent *clone() const override;
    };
}


#endif //HW3_CLOSED_EVENT_H
