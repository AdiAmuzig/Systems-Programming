//
// Created by adi.amuzig on 09/12/2020.
//

#include "event_data.h"
#include "int_functions.h"
#include "member_data.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct EventData_t{
    int event_id;
    char* name;
    Date date;
    PriorityQueue members;
};

PQElement eventDataCreate(int event_id, char* name, Date date){
    if (name == NULL || date == NULL){
        return NULL;
    }

    EventData event_data = malloc(sizeof(*event_data));
    if (event_data == NULL){
        return NULL;
    }

    char* name_copy = malloc(sizeof(char) * (strlen(name) + 1));
    if (name_copy == NULL){
        free(event_data);
        return NULL;
    }
    strcpy(name_copy, name);

    Date date_copy = dateCopy(date);
    if (date_copy == NULL){
        free(name_copy);
        free(event_data);
        return NULL;
    }

    PriorityQueue members = pqCreate(memberDataCopy,
                                     memberDataDestroy,
                                     memberDataEqual,
                                     copyIntGeneric,
                                     freeIntGeneric,
                                     compareIntsGenericReverse);
    if (members == NULL){
        free(name_copy);
        dateDestroy(date_copy);
        free(event_data);
        return NULL;
    }

    event_data -> members = members;
    event_data -> event_id = event_id;
    event_data -> name = name_copy;
    event_data -> date = date_copy;
    return event_data;
}

void eventDataDestroy(PQElement event_data){
    assert(event_data != NULL);
    free(((EventData)event_data) -> name);
    dateDestroy(((EventData)event_data) -> date );
    pqDestroy(((EventData)event_data) -> members);
    free(event_data);
}

PQElement eventDataCopy(PQElement event_data){
    if (event_data == NULL){
        return NULL;
    }
    EventData new_event_data = eventDataCreate
            (((EventData)event_data) -> event_id,
             ((EventData)event_data) -> name,
             ((EventData)event_data) -> date);
    pqDestroy(new_event_data -> members);
    new_event_data -> members = pqCopy(((EventData)event_data) -> members);
    return new_event_data;
}

bool eventDataEqual(PQElement event_data1, PQElement event_data2){
    assert(event_data1 != NULL && event_data2 != NULL);
    return (((EventData)event_data1) -> event_id ==
    ((EventData)event_data2) -> event_id);
}

int getEventId(PQElement event_data){
    assert(event_data != NULL);
    return ((EventData)event_data) -> event_id;
}

char* getEventName(PQElement event_data){
    assert(event_data != NULL);
    return ((EventData)event_data) -> name;
}

Date getEventDate(PQElement event_data){
    assert(event_data != NULL);
    return ((EventData)event_data) -> date;
}

bool eventDataCheckMemberExists(PQElement event_data, int member_id){
    assert(event_data != NULL);
    PQ_FOREACH(PQElement, iterator, ((EventData)event_data)->members){
        if (getMemberId((MemberData)iterator) == member_id){
            return true;
        }
    }
    return false;
}

PriorityQueueResult eventDataAddMember(PQElement event_data,
                                       PQElement member_data){
    assert(event_data != NULL && member_data != NULL);
    int member_id = getMemberId(member_data);
    return pqInsert(((EventData)event_data) -> members,
                    member_data,
                    &member_id);
}

PriorityQueueResult eventDataRemoveMember(PQElement event_data,
                           PQElement member_data) {
    assert(event_data != NULL && member_data != NULL);
    return pqRemoveElement(getEventDataMembers((EventData)event_data),
                           member_data);
}

PriorityQueue getEventDataMembers(EventData event_data){
    if (event_data == NULL){
        return NULL;
    }
    return ((EventData)event_data) -> members;
}

bool eventDataChangeDate(EventData event_data, Date new_date){
    if(event_data == NULL || new_date == NULL){
        return false;
    }
    dateDestroy(event_data -> date);
    event_data -> date = dateCopy(new_date);
    if (event_data -> date == NULL){
        return false;
    }
    return true;
}