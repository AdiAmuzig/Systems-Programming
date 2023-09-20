//
// Created by adi.amuzig on 24/11/2020.
//

#include "event_manager.h"
#include "priority_queue.h"
#include "member_data.h"
#include "event_data.h"
#include "member_priority.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct EventManager_t{
    Date current_date;
    PriorityQueue all_members;
    PriorityQueue events;
};

static int reverseDateCompare(Date date1, Date date2){
    return dateCompare(date2, date1);
}

EventManager createEventManager(Date date){
    if (date == NULL){
        return NULL;
    }

    EventManager em = malloc(sizeof(*em));
    if (em == NULL){
        return NULL;
    }

    PriorityQueue all_members = pqCreate(memberDataCopy,
                                         memberDataDestroy,
                                         memberDataEqual,
                                         memberPriorityCopy,
                                         memberPriorityDestroy,
                                         memberPriorityCompare);
    if (all_members == NULL){
        free(em);
        return NULL;
    }

    PriorityQueue events = pqCreate(eventDataCopy,
                                    eventDataDestroy,
                                    eventDataEqual,
                                    (CopyPQElementPriority) dateCopy,
                                    (FreePQElementPriority) dateDestroy,
                                    (ComparePQElementPriorities)
                                    reverseDateCompare);
    if (events == NULL){
        pqDestroy(all_members);
        free(em);
        return NULL;
    }

    Date current_date = dateCopy(date);
    if (current_date == NULL){
        pqDestroy(all_members);
        pqDestroy(events);
        free(em);
        return NULL;
    }

    em -> events = events;
    em -> all_members = all_members;
    em -> current_date = current_date;
    return em;
}

void destroyEventManager(EventManager em){
    if (em == NULL){
        return;
    }
    pqDestroy(em -> events);
    pqDestroy(em -> all_members);
    dateDestroy(em -> current_date);
    free(em);
}

EventManagerResult emAddEventByDate(EventManager em,
                                    char* event_name,
                                    Date date,
                                    int event_id){
    if (em == NULL || event_name == NULL || date == NULL){
        return EM_NULL_ARGUMENT;
    }
    if (dateCompare(date,em->current_date) < 0){
        return EM_INVALID_DATE;
    }
    if (event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    PQ_FOREACH(PQElement, iterator, em->events){
        if (strcmp(getEventName(iterator), event_name) == 0 &&
        dateCompare(getEventDate(iterator), date) == 0){
            return EM_EVENT_ALREADY_EXISTS;
        }
    }
    PQ_FOREACH(PQElement, iterator, em->events){
        if (getEventId(iterator) == event_id){
            return EM_EVENT_ID_ALREADY_EXISTS;
        }
    }
    PQElement new_event_data = eventDataCreate(event_id, event_name, date);
    if (new_event_data == NULL){
        return EM_OUT_OF_MEMORY;
    }
    if (pqInsert(em -> events, new_event_data, date) == PQ_OUT_OF_MEMORY){
        return EM_OUT_OF_MEMORY;
    }
    eventDataDestroy(new_event_data);
    return EM_SUCCESS;
}

EventManagerResult emAddEventByDiff(EventManager em,
                                    char* event_name,
                                    int days,
                                    int event_id){
    if (em == NULL || event_name == NULL){
            return EM_NULL_ARGUMENT;
    }
    if (days < 0){
        return EM_INVALID_DATE;
    }
    Date new_date = dateCopy(em -> current_date);
    if (new_date == NULL){
        return EM_OUT_OF_MEMORY;
    }
    for (int i = 0; i < days; ++i) {
        dateTick(new_date);
    }
    EventManagerResult result = emAddEventByDate(em, event_name,
                                                 new_date, event_id);
    dateDestroy(new_date);
    return result;
}

EventManagerResult emRemoveEvent(EventManager em, int event_id){
    if (em == NULL){
        return EM_NULL_ARGUMENT;
    }
    if (event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    PQElement event_data = NULL;
    PQ_FOREACH(PQElement, iterator, em -> events){
        if (getEventId(iterator) == event_id) {
            event_data = iterator;
            break;
        }
    }
    if (event_data == NULL){
        return EM_EVENT_NOT_EXISTS;
    }
    while (pqGetSize(getEventDataMembers((EventData)event_data)) != 0){
        MemberData member_data =
                pqGetFirst(getEventDataMembers((EventData)event_data));
        if (emRemoveMemberFromEvent(em,getMemberId(member_data),event_id)==
        EM_OUT_OF_MEMORY){
            return EM_OUT_OF_MEMORY;
        }
    }
    pqRemoveElement(em -> events, event_data);
    return EM_SUCCESS;
}

EventManagerResult emChangeEventDate(EventManager em, int event_id,
                                     Date new_date){
    if (em == NULL || new_date == NULL){
        return EM_NULL_ARGUMENT;
    }
    if (dateCompare(new_date,em->current_date) < 0){
        return EM_INVALID_DATE;
    }
    if (event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    bool event_exists = false;
    PQElement event_data = NULL;
    PQ_FOREACH(PQElement, event_iterator, em->events){
        if (getEventId(event_iterator) == event_id){
            event_data = event_iterator;
            event_exists = true;
        }
    }
    if (event_exists == false){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    PQ_FOREACH(PQElement, iterator, em->events){
        if (strcmp(getEventName(iterator), getEventName(event_data)) == 0 &&
            dateCompare(getEventDate(iterator), new_date) == 0){
            return EM_EVENT_ALREADY_EXISTS;
        }
    }
    Date old_date = dateCopy(getEventDate(event_data));
    if (old_date == NULL){
        return EM_OUT_OF_MEMORY;
    }
    eventDataChangeDate(event_data,new_date);
    if (pqChangePriority(em->events, event_data, old_date, new_date) ==
    PQ_OUT_OF_MEMORY){
        return EM_OUT_OF_MEMORY;
    }
    dateDestroy(old_date);
    return EM_SUCCESS;
}

EventManagerResult emAddMember(EventManager em, char* member_name,
                               int member_id){
    if (em == NULL || member_name == NULL){
        return EM_NULL_ARGUMENT;
    }
    if (member_id < 0){
        return EM_INVALID_MEMBER_ID;
    }
    int number_of_events = 0;
    PQElement member_data = memberDataCreate(member_id, member_name,
                                             number_of_events);
    if (member_data == NULL){
        return EM_OUT_OF_MEMORY;
    }
    if (pqContains(em -> all_members, member_data) == 1){
        memberDataDestroy(member_data);
        return EM_MEMBER_ID_ALREADY_EXISTS;
    }
    PQElementPriority member_priority =
            memberPriorityCreate(number_of_events, member_id);
    if (member_priority == NULL){
        memberDataDestroy(member_data);
        return EM_OUT_OF_MEMORY;
    }
    if (pqInsert(em -> all_members, member_data, member_priority) ==
    PQ_OUT_OF_MEMORY){
        memberPriorityDestroy(member_priority);
        memberDataDestroy(member_data);
        return EM_OUT_OF_MEMORY;
    }
    memberPriorityDestroy(member_priority);
    memberDataDestroy(member_data);
    return EM_SUCCESS;
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id,
                                      int event_id){
    if (em == NULL){
        return EM_NULL_ARGUMENT;
    }
    if (event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    if (member_id < 0){
        return EM_INVALID_MEMBER_ID;
    }
    bool event_exists = false;
    PQElement event_data = NULL;
    PQ_FOREACH(PQElement, event_iterator, em->events){
        if (getEventId(event_iterator) == event_id){
            event_data = event_iterator;
            event_exists = true;
        }
    }
    if (event_exists == false){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    bool member_exists = false;
    PQElement member_data = NULL;
    PQ_FOREACH(PQElement, member_iterator, em->all_members){
        if (getMemberId(member_iterator) == member_id){
            member_data = member_iterator;
            member_exists = true;
        }
    }
    if (member_exists == false){
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    if (eventDataCheckMemberExists(event_data, member_id) == true){
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }
    MemberPriority old_priority =
            memberPriorityCreate(getMembersEvents(member_data),member_id);
    MemberPriority new_priority =
            memberPriorityCreate(increaseMembersEvents(member_data),member_id);
    if (eventDataAddMember(event_data,member_data) == PQ_OUT_OF_MEMORY){
        return EM_OUT_OF_MEMORY;
    }
    pqChangePriority(em -> all_members, member_data,
                     old_priority,
                     new_priority);
    memberPriorityDestroy(old_priority);
    memberPriorityDestroy(new_priority);
    return EM_SUCCESS;
}

EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id,
                                            int event_id){
    if (em == NULL){
        return EM_NULL_ARGUMENT;
    }
    if (event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    if (member_id < 0){
        return EM_INVALID_MEMBER_ID;
    }
    bool event_exists = false;
    PQElement event_data = NULL;
    PQ_FOREACH(PQElement, event_iterator, em->events){
        if (getEventId(event_iterator) == event_id){
            event_data = event_iterator;
            event_exists = true;
        }
    }
    if (event_exists == false){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    bool member_exists = false;
    PQElement member_data = NULL;
    PQ_FOREACH(PQElement, member_iterator, em -> all_members){
        if (getMemberId(member_iterator) == member_id){
            member_data = member_iterator;
            member_exists = true;
        }
    }
    if (member_exists == false){
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    if (eventDataCheckMemberExists(event_data, member_id) == false){
        return EM_EVENT_AND_MEMBER_NOT_LINKED;
    }
    eventDataRemoveMember(event_data, member_data);
    MemberPriority old_priority =
            memberPriorityCreate(getMembersEvents(member_data),member_id);
    MemberPriority new_priority =
            memberPriorityCreate(decreaseMembersEvents(member_data),member_id);
    pqChangePriority(em -> all_members, member_data,
                     old_priority,
                     new_priority);
    memberPriorityDestroy(old_priority);
    memberPriorityDestroy(new_priority);
    return EM_SUCCESS;
}

EventManagerResult emTick(EventManager em, int days){
    if (em == NULL){
        return EM_NULL_ARGUMENT;
    }
    if (days <= 0){
        return EM_INVALID_DATE;
    }
    for (int i = 0; i < days; ++i) {
        dateTick(em -> current_date);
    }

    while (pqGetSize(em -> events) > 0 &&
    dateCompare(getEventDate(pqGetFirst(em -> events)),
                em -> current_date) < 0){
        emRemoveEvent(em, getEventId(pqGetFirst(em -> events)));
    }

    return EM_SUCCESS;
}

int emGetEventsAmount(EventManager em){
    if (em == NULL){
        return -1;
    }
    return pqGetSize(em ->events);
}

char* emGetNextEvent(EventManager em){
    if (em == NULL){
        return NULL;
    }
    PQElement event = pqGetFirst(em -> events);
    if (event == NULL){
        return NULL;
    }
    return getEventName(event);
}

void emPrintAllEvents(EventManager em, const char* file_name){
    if (em == NULL || file_name == NULL){
        return;
    }
    FILE* file = fopen(file_name, "w");
    if (file == NULL){
        return;
    }
    int day;
    int month;
    int year;
    PQ_FOREACH(PQElement, event_data, em -> events){
        dateGet(getEventDate(event_data), &day, &month, &year);
        fprintf(file,"%s" , getEventName(event_data));
        fprintf(file,",%d.%d.%d" , day, month, year);
        PQ_FOREACH(PQElement, member_data,
                   getEventDataMembers((EventData)event_data)){
            fprintf(file,",%s" ,getMemberName(member_data));
        }
        fprintf(file,"\n");
    }
    fclose(file);
}

void emPrintAllResponsibleMembers(EventManager em, const char* file_name){
    if (em == NULL || file_name == NULL){
        return;
    }
    FILE* file = fopen(file_name, "w");
    if (file == NULL){
        return;
    }
    PQ_FOREACH(PQElement, member_data, em -> all_members){
        if (getMembersEvents(member_data) != 0){
            fprintf(file, "%s,%d\n",getMemberName(member_data),
                    getMembersEvents(member_data));
        }
    }
    fclose(file);
}