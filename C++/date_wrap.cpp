//
// Created by adi.amuzig on 09/01/2021.
//

#include "date_wrap.h"

namespace mtm {

    DateWrap::DateWrap(int day, int month, int year) {
        Date new_date = dateCreate(day, month, year);
        if (new_date == NULL) {
            throw InvalidDate();
        }
        date = new_date;
    }

    DateWrap::~DateWrap() {
        dateDestroy(date);
    }

    DateWrap::DateWrap(const DateWrap &old_date) {
        date = dateCopy(old_date.date);
    }

    int DateWrap::day() const {
        int day;
        int month;
        int year;
        if (dateGet(date, &day, &month, &year) == false) {
            return -1;
        }
        return day;
    }

    int DateWrap::month() const {
        int day;
        int month;
        int year;
        if (dateGet(date, &day, &month, &year) == false) {
            return -1;
        }
        return month;
    }

    int DateWrap::year() const {
        int day;
        int month;
        int year;
        if (dateGet(date, &day, &month, &year) == false) {
            return -1;
        }
        return year;
    }

    DateWrap DateWrap::operator++(int) {
        DateWrap new_date(*this);
        dateTick(date);
        return new_date;
    }

    DateWrap &DateWrap::operator+=(const int &days) {
        if (days < 0) {
            throw mtm::NegativeDays();
        }
        if (days == 0) {
            return *this;
        }
        if (days > 0) {
            for (int i = 0; i < days; ++i) {
                (*this)++;
            }
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &output, const DateWrap &date) {
        output << date.day() << "/" << date.month() << "/" << date.year();
        return output;
    }

    bool operator==(const DateWrap &date1, const DateWrap &date2) {
        return (dateCompare(date1.date, date2.date) == 0);
    }

    bool operator<(const DateWrap &date1, const DateWrap &date2) {
        return (dateCompare(date1.date, date2.date) < 0);
    }

    DateWrap *DateWrap::clone() const {
        DateWrap *new_date =
                new DateWrap(day(), month(), year());
        return new_date;
    }

    DateWrap &DateWrap::operator=(const DateWrap &old_date) {
        if (this == &old_date) {
            return *this;
        }
        dateDestroy(date);
        date = dateCopy(old_date.date);
        return *this;
    }

    DateWrap operator+(const DateWrap &date, const int &days) {
        DateWrap new_date(date);
        new_date += days;
        return new_date;
    }

    DateWrap operator+(const int &days, const DateWrap &date) {
        return date + days;
    }

    bool operator!=(const DateWrap &date1, const DateWrap &date2) {
        return (!(date1 == date2));
    }

    bool operator>=(const DateWrap &date1, const DateWrap &date2) {
        return (!(date1 < date2));
    }

    bool operator>(const DateWrap &date1, const DateWrap &date2) {
        return ((date1 >= date2) && (date1 != date2));
    }

    bool operator<=(const DateWrap &date1, const DateWrap &date2) {
        return (!(date1 > date2));
    }

}
