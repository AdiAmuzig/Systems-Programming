//
// Created by adi.amuzig on 21/01/2021.
//

#include "closed_event.h"

namespace mtm {
    ClosedEvent::ClosedEvent(const mtm::DateWrap &date,
                             const std::string &name)
            : BaseEvent(date, name),
              invitedStudents() {
    }

    void ClosedEvent::addInvitee(int student_id) {
        Student student(student_id);
        checkLegalStudent(student);
        if (invitedStudents.dataExists(student)) {
            throw AlreadyInvited();
        }
        invitedStudents.insert(student);
    }

    void ClosedEvent::registerParticipant(const int &student_id) {
        Student student(student_id);
        checkLegalStudent(student);
        if (invitedStudents.dataExists(student) == false) {
            throw RegistrationBlocked();
        }
        BaseEvent::registerParticipant(student_id);
    }

    BaseEvent *ClosedEvent::clone() const {
        ClosedEvent *new_closed_event =
                new ClosedEvent(getDate(), getName());
        new_closed_event->invitedStudents = invitedStudents;
        new_closed_event->participatingStudents = participatingStudents;
        return new_closed_event;
    }

}