//
// Created by adi.amuzig on 13/12/2020.
//

#include "member_priority.h"
#include <assert.h>
#include <stdlib.h>

struct MemberPriority_t{
    int member_id;
    int number_of_events;
};

PQElementPriority memberPriorityCreate(int number_of_events, int member_id){
    MemberPriority member_priority = malloc(sizeof(*member_priority));
    if (member_priority == NULL){
        return NULL;
    }
    member_priority -> member_id = member_id;
    member_priority -> number_of_events = number_of_events;
    return member_priority;
}

void memberPriorityDestroy(PQElementPriority member_priority){
    assert(member_priority != NULL);
    free(member_priority);
}

PQElementPriority memberPriorityCopy(PQElementPriority member_priority){
    if (member_priority == NULL){
        return NULL;
    }
    return memberPriorityCreate(
            ((MemberPriority)member_priority)->number_of_events,
            ((MemberPriority)member_priority)->member_id);
}

int memberPriorityCompare (PQElementPriority member_priority1,
                           PQElementPriority member_priority2){
    if (((MemberPriority)member_priority1) -> number_of_events !=
        ((MemberPriority)member_priority2) -> number_of_events){
        return (((MemberPriority)member_priority1) -> number_of_events -
                ((MemberPriority)member_priority2) -> number_of_events);
    }
    return (((MemberPriority)member_priority2) -> member_id -
            ((MemberPriority)member_priority1) -> member_id);
}


