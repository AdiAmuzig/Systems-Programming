//
// Created by adi.amuzig on 09/12/2020.
//

#ifndef PART3_MEMBER_DATA_H
#define PART3_MEMBER_DATA_H

#include "priority_queue.h"
#include <stdbool.h>

typedef struct MemberData_t *MemberData;

PQElement memberDataCreate(int id, char* name, int number_of_events);

void memberDataDestroy(PQElement member_data);

PQElement memberDataCopy(PQElement member_data);

bool memberDataEqual(PQElement member_data1, PQElement member_data2);

int getMemberId(PQElement member_data);

char* getMemberName(PQElement member_data);

int getMembersEvents(PQElement member_data);

int increaseMembersEvents(PQElement member_data);

int decreaseMembersEvents(PQElement member_data);

#endif //PART3_MEMBER_DATA_H
