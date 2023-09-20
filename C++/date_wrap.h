//
// Created by adi.amuzig on 09/01/2021.
//

#ifndef HW3_DATE_WRAP_H
#define HW3_DATE_WRAP_H

#include <iostream>
#include "exceptions.h"

extern "C" {
#include "../provided/date.h"
}

namespace mtm {
    class DateWrap {
        Date date;
    public:
        DateWrap(int day, int month, int year);

        ~DateWrap();

        DateWrap(const DateWrap &old_date);

        DateWrap &operator=(const DateWrap &old_date);

        DateWrap *clone() const;

        int day() const;

        int month() const;

        int year() const;

        DateWrap operator++(int);

        DateWrap &operator+=(const int &days);

        friend std::ostream &operator<<(std::ostream &output,
                                        const DateWrap &date);

        friend bool operator==(const DateWrap &date1, const DateWrap &date2);

        friend bool operator<(const DateWrap &date1, const DateWrap &date2);
    };

    mtm::DateWrap operator+(const mtm::DateWrap &date, const int &days);

    mtm::DateWrap operator+(const int &days, const mtm::DateWrap &date);

    bool operator!=(const mtm::DateWrap &date1, const mtm::DateWrap &date2);

    bool operator>=(const mtm::DateWrap &date1, const mtm::DateWrap &date2);

    bool operator>(const mtm::DateWrap &date1, const mtm::DateWrap &date2);

    bool operator<=(const mtm::DateWrap &date1, const mtm::DateWrap &date2);
}


#endif //HW3_DATE_WRAP_H
