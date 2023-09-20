//
// Created by adi.amuzig on 21/01/2021.
//

#include "base_event.h"
#include "exception"
#include <cstring>
#include <iostream>

using std::ostream;
using std::endl;

namespace mtm {
    void BaseEvent::checkLegalStudent(Student student) {
        if (student.value < 1 || student.value > 1234567890) {
            throw InvalidStudent();
        }
    }

    BaseEvent::BaseEvent(const DateWrap &date,
                         const std::string &given_name) :
            date(date),
            name(given_name),
            participatingStudents(){
    }

    void BaseEvent::registerParticipant(const int &student_id) {
        Student student(student_id);
        checkLegalStudent(student);
        if (participatingStudents.dataExists(student)) {
            throw AlreadyRegistered();
        }
        participatingStudents.insert(student);
    }

    void BaseEvent::unregisterParticipant(const int &student_id) {
        Student student(student_id);
        checkLegalStudent(student);
        if (!participatingStudents.dataExists(student)) {
            throw NotRegistered();
        }
        participatingStudents.erase(student);
    }

    const std::string &BaseEvent::getName() const {
        return name;
    }

    const DateWrap &BaseEvent::getDate() const {
        return date;
    }

    int BaseEvent::getSize() const {
        return participatingStudents.getSize();
    }

    ostream &BaseEvent::printShort(ostream &output) {
        return output << name << " " << date << endl;
    }

    ostream &BaseEvent::printLong(ostream &output) {
        printShort(output);
        int size = getSize();
        if (size == 0) {
            return output;
        }
        DoublyLinkedList<Student>::Iterator iterator =
                participatingStudents.returnHead();
        int student_id = 0;
        for (int i = 0; i < size; ++i) {
            student_id = (iterator.operator*()).value;
            output << student_id << endl;
            ++iterator;
        }
        return output;
    }

    bool operator==(const BaseEvent &event1, const BaseEvent &event2) {
        return (event1.getDate() == event2.getDate() &&
                (event1.getName()).compare(event2.getName()) == 0);
    }

    bool operator<(const BaseEvent &event1, const BaseEvent &event2) {
        if (event1.getDate() < event2.getDate()) {
            return true;
        }
        if (event1.getDate() == event2.getDate() &&
            (event1.getName()).compare(event2.getName()) < 0) {
            return true;
        }
        return false;
    }

    bool operator!=(const BaseEvent &event1, const BaseEvent &event2) {
        return (!(event1 == event2));
    }

}
