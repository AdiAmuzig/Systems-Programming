//
// Created by adi.amuzig on 21/01/2021.
//

#include "student.h"

namespace mtm {
    Student::Student(int value) : value(value) {
    }

    Student *Student::clone() const {
        Student *new_student = new Student(value);
        return new_student;
    }

    bool operator==(const Student &student1, const Student &student2) {
        return (student1.value == student2.value);
    }

    bool operator<(const Student &student1, const Student &student2) {
        return (student1.value < student2.value);
    }
}
