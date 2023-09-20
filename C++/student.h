//
// Created by adi.amuzig on 19/01/2021.
//

#ifndef HW3_STUDENT_H
#define HW3_STUDENT_H

namespace mtm {
    class Student {
    public:
        int value;

        Student(int value);

        Student *clone() const;

        friend bool
        operator==(const Student &student1, const Student &student2);

        friend bool operator<(const Student &student1, const Student &student2);
    };
}


#endif //HW3_STUDENT_H
