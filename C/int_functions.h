//
// Created by adi.amuzig on 09/12/2020.
//

#ifndef PART3_INT_FUNCTIONS_H
#define PART3_INT_FUNCTIONS_H

#include "priority_queue.h"
#include <stdbool.h>

PQElementPriority copyIntGeneric(PQElementPriority number);

void freeIntGeneric(PQElementPriority number);

int compareIntsGeneric(PQElementPriority number1, PQElementPriority number2);

int compareIntsGenericReverse(PQElementPriority number1, PQElementPriority number2);

bool equalIntsGeneric(PQElementPriority number1, PQElementPriority number2);

#endif //PART3_INT_FUNCTIONS_H
