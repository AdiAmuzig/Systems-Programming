//
// Created by adi.amuzig on 13/12/2020.
//

#ifndef PART3_MEMBER_PRIORITY_H
#define PART3_MEMBER_PRIORITY_H

#include "priority_queue.h"

typedef struct MemberPriority_t *MemberPriority;

PQElementPriority memberPriorityCreate(int number_of_events, int member_id);

void memberPriorityDestroy(PQElementPriority member_priority);

PQElementPriority memberPriorityCopy(PQElementPriority member_priority);

int memberPriorityCompare (PQElementPriority member_priority1,
                           PQElementPriority member_priority2);

#endif //PART3_MEMBER_PRIORITY_H
