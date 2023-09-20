//
// Created by adi.amuzig on 09/12/2020.
//

#include "priority_queue.h"
#include "node.h"
#include <stdlib.h>

struct node{
    PQElement element;
    PQElementPriority priority;
    Node next;
    Node prev;
};

Node nodeCreate(PQElement element,
                PQElementPriority priority,
                CopyPQElement copy_element,
                CopyPQElementPriority copy_priority){
    if (element == NULL || priority == NULL){
        return NULL;
    }
    Node node = malloc(sizeof(*node));
    if (node == NULL){
        return NULL;
    }

    node -> element = copy_element(element);
    node -> priority = copy_priority(priority);
    node -> next = NULL;
    node -> prev = NULL;

    return node;
}

bool nodeDestroy(Node node,
                 FreePQElement free_element,
                 FreePQElementPriority free_priority){
    if (node == NULL) {
        return 0;
    }
    free_element(node -> element);
    free_priority(node -> priority);
    free(node);
    return 1;
}

Node nodeGetNext(Node node){
    if (node == NULL){
        return NULL;
    }
    return node -> next;
}

Node nodeGetPrev(Node node){
    if (node == NULL){
        return NULL;
    }
    return node -> prev;
}

PQElement nodeGetElement(Node node){
    if (node == NULL){
        return NULL;
    }
    return node -> element;
}

PQElementPriority nodeGetPriority(Node node){
    if (node == NULL){
        return NULL;
    }
    return node -> priority;
}

bool nodeNewNext(Node node, Node new_next_node){
    if (node == NULL){
        return 0;
    }
    node -> next = new_next_node;
    return 1;
}

bool nodeNewPrev(Node node, Node new_prev_node){
    if (node == NULL){
        return 0;
    }
    node -> prev = new_prev_node;
    return 1;
}
