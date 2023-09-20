//
// Created by adi.amuzig on 09/12/2020.
//

#ifndef PART3_NODE_H
#define PART3_NODE_H

# include "priority_queue.h"

typedef struct node *Node;

Node nodeCreate(PQElement element,
                PQElementPriority priority,
                CopyPQElement copy_element,
                CopyPQElementPriority copy_priority);

bool nodeDestroy(Node node,
                 FreePQElement free_element,
                 FreePQElementPriority free_priority);

Node nodeGetNext(Node node);

Node nodeGetPrev(Node node);

PQElement nodeGetElement(Node node);

PQElementPriority nodeGetPriority(Node node);

bool nodeNewNext(Node node, Node new_next_node);

bool nodeNewPrev(Node node, Node new_prev_node);

#endif //PART3_NODE_H
