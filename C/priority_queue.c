//
// Created by adi.amuzig on 24/11/2020.
//
#include "priority_queue.h"
#include "node.h"
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

struct PriorityQueue_t{
    int size;
    Node current;
    Node head;
    Node end;

    CopyPQElement copy_element;
    FreePQElement free_element;
    EqualPQElements equal_elements;
    CopyPQElementPriority copy_priority;
    FreePQElementPriority free_priority;
    ComparePQElementPriorities compare_priorities;
};

static bool currentDestroy(PriorityQueue queue){
    assert(queue != NULL);
    assert(queue -> current != NULL);

    if (nodeGetPrev(queue -> current) !=
    NULL && nodeGetNext(queue -> current)!= NULL){
        Node prev_node = nodeGetPrev(queue -> current);
        Node next_node = nodeGetNext(queue -> current);
        nodeNewNext(prev_node,next_node);
        nodeNewPrev(next_node,prev_node);
        nodeDestroy(queue -> current,
                    queue -> free_element,
                    queue -> free_priority);
    } else if (nodeGetPrev(queue -> current) != NULL
    && nodeGetNext(queue -> current) == NULL){
        Node prev_node = nodeGetPrev(queue -> current);
        nodeNewNext(prev_node,NULL);
        queue -> end = prev_node;
        nodeDestroy(queue -> current,
                    queue -> free_element,
                    queue -> free_priority);
    } else if (nodeGetPrev(queue -> current) == NULL &&
    nodeGetNext(queue -> current) != NULL){
        Node next_node = nodeGetNext(queue -> current);
        nodeNewPrev(next_node,NULL);
        queue -> head = next_node;
        nodeDestroy(queue -> current,
                    queue -> free_element,
                    queue -> free_priority);
    }else{
        queue -> head = NULL;
        queue -> end = NULL;
        nodeDestroy(queue -> current,
                    queue -> free_element,
                    queue -> free_priority);
    }
    queue -> current = NULL;
    queue -> size = (queue -> size) - 1;
    return 1;
}

static PQElement pqGetLast(PriorityQueue queue){
    if (queue == NULL){
        return NULL;
    }
    if ((queue -> size) == 0){
        return NULL;
    }
    queue -> current = queue -> end;
    return nodeGetElement(queue -> current);
}

static PQElement pqGetPrev(PriorityQueue queue){
    if (queue == NULL){
        return NULL;
    }
    if (queue -> current == NULL){
        return NULL;
    }
    if (nodeGetPrev(queue -> current) == NULL){
        return NULL;
    }
    queue -> current = nodeGetPrev(queue -> current);
    return nodeGetElement(queue -> current);
}

PriorityQueue pqCreate(CopyPQElement copy_element,
                       FreePQElement free_element,
                       EqualPQElements equal_elements,
                       CopyPQElementPriority copy_priority,
                       FreePQElementPriority free_priority,
                       ComparePQElementPriorities compare_priorities){
    if (copy_element == NULL || free_element == NULL ||
    equal_elements == NULL || copy_priority == NULL ||
    free_priority == NULL || compare_priorities == NULL){
        return NULL;
    }

    PriorityQueue queue = malloc(sizeof(*queue));
    if (queue == NULL){
        return NULL;
    }

    queue -> size = 0;
    queue -> current = NULL;
    queue -> head = NULL;
    queue -> end = NULL;

    queue -> copy_element = copy_element;
    queue -> free_element = free_element;
    queue -> equal_elements = equal_elements;
    queue -> copy_priority = copy_priority;
    queue -> free_priority = free_priority;
    queue -> compare_priorities = compare_priorities;

    return queue;
}

void pqDestroy(PriorityQueue queue){
    pqClear(queue);
    free(queue);
}

PriorityQueue pqCopy(PriorityQueue queue){
    if (queue == NULL){
        return NULL;
    }
    PriorityQueue new_queue = pqCreate(queue -> copy_element,
                                       queue -> free_element,
                                       queue -> equal_elements,
                                       queue -> copy_priority,
                                       queue -> free_priority,
                                       queue -> compare_priorities);
    pqGetLast(queue);
    for (int i = 0; i < (queue -> size); ++i) {
        if (pqInsert(new_queue,
                 nodeGetElement(queue -> current),
                 nodeGetPriority(queue -> current)) == PQ_OUT_OF_MEMORY){
            return NULL;
        }
        pqGetPrev(queue);
    }
    queue -> current = NULL;
    return new_queue;
}

int pqGetSize(PriorityQueue queue){
    if (queue == NULL){
        return -1;
    }
    return queue -> size;
}

bool pqContains(PriorityQueue queue, PQElement element){
    if (queue == NULL || element == NULL){
        return false;
    }
    Node current_save = queue -> current;
    PQ_FOREACH(PQElement, iterator, queue){
        if (queue -> equal_elements(element, iterator)){
            queue -> current = current_save;
            return true;
        }
    }
    queue -> current = current_save;
    return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue,
                             PQElement element,
                             PQElementPriority priority){
    if (queue == NULL || element == NULL || priority == NULL){
        return PQ_NULL_ARGUMENT;
    }
    Node node = nodeCreate(element, priority,
                           queue -> copy_element,
                           queue -> copy_priority);
    if (node == NULL){
        return PQ_OUT_OF_MEMORY;
    }
    if ((queue -> size) == 0){
        queue -> head = node;
        queue -> end = node;
    }else{
        pqGetFirst(queue);
        while ((queue -> compare_priorities(
                nodeGetPriority(queue -> current),priority)) >= 0){
            if (pqGetNext(queue) == NULL){
                break;
            }
        }
        if (nodeGetNext(queue -> current) == NULL &&
                (queue -> compare_priorities(
                        nodeGetPriority(queue -> current),priority)) >= 0){
            Node prev = queue -> end;
            nodeNewNext(prev,node);
            nodeNewPrev(node,prev);
            queue -> end = node;
        } else if ((nodeGetPrev(queue -> current)) == NULL){
            Node next = queue -> head;
            nodeNewPrev(next,node);
            nodeNewNext(node,next);
            queue -> head = node;
        }else{
            Node next = queue -> current;
            Node prev = nodeGetPrev(next);
            nodeNewNext(prev,node);
            nodeNewPrev(next,node);
            nodeNewNext(node,next);
            nodeNewPrev(node,prev);
        }
    }
    queue -> current = NULL;
    queue -> size = (queue -> size) + 1;
    return PQ_SUCCESS;
}

PriorityQueueResult pqChangePriority(PriorityQueue queue,
                                     PQElement element,
                                     PQElementPriority old_priority,
                                     PQElementPriority new_priority){
    if (queue == NULL || element == NULL ||
    old_priority == NULL || new_priority == NULL){
        return PQ_NULL_ARGUMENT;
    }
    if ((queue -> size) == 0){
        return PQ_ELEMENT_DOES_NOT_EXISTS;
    }
    pqGetFirst(queue);
    while (queue -> equal_elements (
            nodeGetElement(queue -> current),element) != 1 ||
    queue -> compare_priorities(
            nodeGetPriority(queue -> current), old_priority) != 0){
        if (pqGetNext(queue) == NULL){
            return PQ_ELEMENT_DOES_NOT_EXISTS;
        }
    }
    PQElement element_copy = (queue -> copy_element)(element);
    if (element_copy == NULL){
        return PQ_OUT_OF_MEMORY;
    }
    currentDestroy(queue);
    PriorityQueueResult result = pqInsert(queue, element_copy, new_priority);
    (queue -> free_element)(element_copy);
    return result;
}

PriorityQueueResult pqRemove(PriorityQueue queue){
    if (queue == NULL){
        return PQ_NULL_ARGUMENT;
    }
    if (queue -> size == 0){
        queue -> current = NULL;
        return PQ_SUCCESS;
    }else{
        pqGetFirst(queue);
        currentDestroy(queue);
        return PQ_SUCCESS;
    }
}

PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element){
    if (queue == NULL || element == NULL){
        return PQ_NULL_ARGUMENT;
    }

    if (pqContains(queue,element) == 0){
        return PQ_ELEMENT_DOES_NOT_EXISTS;
    }

    PQElement queue_element = pqGetFirst(queue);
    while (queue -> equal_elements(element, queue_element) == 0){
        queue_element = pqGetNext(queue);
    }

    currentDestroy(queue);
    return PQ_SUCCESS;
}

PQElement pqGetFirst(PriorityQueue queue){
    if (queue == NULL){
        return NULL;
    }
    if ((queue -> size) == 0){
        return NULL;
    }
    queue -> current = queue -> head;
    return nodeGetElement(queue -> current);
}

PQElement pqGetNext(PriorityQueue queue){
    if (queue == NULL){
        return NULL;
    }
    if (queue -> current == NULL){
        return NULL;
    }
    if (nodeGetNext(queue -> current) == NULL){
        return NULL;
    }
    queue -> current = nodeGetNext(queue -> current);
    return nodeGetElement(queue -> current);
}

PriorityQueueResult pqClear(PriorityQueue queue){
    if (queue == NULL){
        return PQ_NULL_ARGUMENT;
    }
    while (queue -> size > 0){
        pqRemove(queue);
    }
    return PQ_SUCCESS;
}
