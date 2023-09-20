//
// Created by adi.amuzig on 24/11/2020.
//

#include "date.h"
#include <stdbool.h>
#include <stdlib.h>

#define MIN_DAY 1
#define MAX_DAY 30
#define MIN_MONTH 1
#define MAX_MONTH 12

struct Date_t{
    int day;
    int month;
    int year;
};

static int compareValues(int value1, int value2){
    if (value1 < value2){
        return -1;
    }else if (value1 > value2){
        return 1;
    }else{
        return 0;
    }
}

static bool checkIsDayValid(int day){
    if (day < MIN_DAY || day > MAX_DAY){
        return 0;
    } else{
        return 1;
    }
}

static bool checkIsMonthValid(int month){
    if (month < MIN_MONTH || month > MAX_MONTH){
        return 0;
    } else{
        return 1;
    }
}

Date dateCreate(int day, int month, int year){
    if (checkIsDayValid(day) == 0 || checkIsMonthValid(month) == 0){
        return NULL;
    }

    Date date = malloc(sizeof(*date));
    if (date == NULL){
        return NULL;
    }

    date->day = day;
    date->month = month;
    date->year = year;

    return date;
}

void dateDestroy(Date date){
    free(date);
}

Date dateCopy(Date date){
    if (date == NULL){
        return NULL;
    }
    return dateCreate(date->day, date->month, date->year);
}

bool dateGet(Date date, int* day, int* month, int* year){
    if (date == NULL || day == NULL || month ==NULL || year ==NULL){
        return 0;
    }
    *day = date->day;
    *month = date->month;
    *year = date->year;
    return 1;
}

int dateCompare(Date date1, Date date2) {
    if (date1 == NULL || date2 == NULL){
        return 0;
    }

    if (compareValues(date1->year, date2->year) != 0){
        return compareValues(date1->year, date2->year);
    }else if (compareValues(date1->month, date2->month) != 0){
        return compareValues(date1->month, date2->month);
    }else if (compareValues(date1->day, date2->day) != 0){
        return compareValues(date1->day, date2->day);
    }else{
        return 0;
    }
}

void dateTick(Date date){
    if (checkIsDayValid(date->day + 1)){
        date->day = date->day + 1;
        return;
    } else if (checkIsMonthValid(date->month + 1)){
        date->day = 1;
        date->month = date->month + 1;
        return;
    } else{
        date->day = 1;
        date->month = 1;
        date->year = date->year + 1;
    }
}


