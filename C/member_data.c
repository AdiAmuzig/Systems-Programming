//
// Created by adi.amuzig on 09/12/2020.
//

#include "member_data.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

struct MemberData_t{
    int member_id;
    int number_of_events;
    char* member_name;
};

PQElement memberDataCreate(int id, char* name, int number_of_events){
    if (name == NULL){
        return NULL;
    }
    MemberData member_data = malloc(sizeof(*member_data));
    if (member_data == NULL){
        return NULL;
    }
    char* name_copy = malloc(sizeof(char) * (strlen(name) + 1));
    if (name_copy == NULL){
        free(member_data);
        return NULL;
    }
    strcpy(name_copy, name);
    member_data -> member_name = name_copy;
    member_data -> member_id = id;
    member_data -> number_of_events = number_of_events;
    return member_data;
}

void memberDataDestroy(PQElement member_data){
    assert(member_data != NULL);
    free(((MemberData)member_data)->member_name);
    free(member_data);
}

PQElement memberDataCopy(PQElement member_data){
    if (member_data == NULL){
        return NULL;
    }
    return memberDataCreate(((MemberData) member_data) -> member_id,
                            ((MemberData) member_data) -> member_name,
                            ((MemberData) member_data) -> number_of_events);
}

bool memberDataEqual(PQElement member_data1,
                     PQElement member_data2){
    assert(member_data1 != NULL && member_data2 != NULL);
    int member_id1 = ((MemberData) member_data1) -> member_id;
    int member_id2 = ((MemberData) member_data2) -> member_id;
    return (member_id1 == member_id2);
}

int getMemberId(PQElement member_data){
    assert(member_data != NULL);
    return ((MemberData)member_data) -> member_id;
}

char* getMemberName(PQElement member_data){
    assert(member_data != NULL);
    return((MemberData)member_data) ->member_name;
}

int getMembersEvents(PQElement member_data){
    assert(member_data != NULL);
    return ((MemberData)member_data) -> number_of_events;
}

int increaseMembersEvents(PQElement member_data) {
    assert(member_data != NULL);
    return ((MemberData) member_data)->number_of_events =
            ((MemberData) member_data)->number_of_events + 1;
}

int decreaseMembersEvents(PQElement member_data) {
    assert(member_data != NULL);
    assert(((MemberData) member_data)->number_of_events -1 >= 0);
    return ((MemberData) member_data)->number_of_events =
            ((MemberData) member_data)->number_of_events - 1;
}