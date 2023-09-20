//
// Created by adi.amuzig on 09/12/2020.
//

#include "int_functions.h"
#include <stdlib.h>

PQElementPriority copyIntGeneric(PQElementPriority number) {
    if (number == NULL) {
        return NULL;
    }
    int *copy = malloc(sizeof(*copy));
    if (copy == NULL) {
        return NULL;
    }
    *copy = *(int *) number;
    return copy;
}

void freeIntGeneric(PQElementPriority number) {
    free(number);
}

int compareIntsGeneric(PQElementPriority number1,
                       PQElementPriority number2) {
    return (*(int *) number1 - *(int *) number2);
}

int compareIntsGenericReverse(PQElementPriority number1,
                              PQElementPriority number2) {
    return (*(int *) number2 - *(int *) number1);
}

bool equalIntsGeneric(PQElementPriority number1, PQElementPriority number2) {
    return *(int *) number1 == *(int *) number2;
}