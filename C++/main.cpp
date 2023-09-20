//
// Created by adi.amuzig on 24/01/2021.
//
#include "../partB/base_event.h"
#include "../partB/closed_event.h"
#include "../partB/custom_event.h"
#include "../partA/date_wrap.h"
#include "../partB/event_container.h"
#include "../partA/exceptions.h"
#include "../partB/festival.h"
#include "../partB/one_time_event.h"
#include "../partB/open_event.h"
#include "../partB/recurring_event.h"
#include "../partC/schedule.h"
#include "../partB/doubly_linked_list.h"
#include "../partB/student.h"
#include <cstdlib>
#include <iostream>
#include <fstream>


using mtm::Schedule;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using mtm::Festival;
using mtm::RecurringEvent;
using mtm::OneTimeEvent;
using mtm::DateWrap;
using mtm::BaseEvent;
using mtm::OpenEvent;
using mtm::ClosedEvent;
using mtm::CustomEvent;
using mtm::DoublyLinkedList;
using mtm::Student;

int main(){
    DoublyLinkedList<DateWrap> date_list;
    int size = date_list.getSize();
    DateWrap date1(1,1,1);
    DateWrap date2(2,1,1);
    DateWrap date22(2,1,1);
    DateWrap date3(3,1,1);
    date_list.insert(date1);
    date_list.insert(date2);
    date_list.insert(date22);
    date_list.erase(date3);
    date_list.insert(date3);
    date_list.erase(date22);
    date_list.insert(date2);
    *(date_list.returnHead());
    return 0;
}
