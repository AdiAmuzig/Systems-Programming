CC = gcc
DIR = tests/
OBJS_ALL = date.o event_data.o event_manager.o int_functions.o \
	member_data.o member_priority.o node.o priority_queue.o
OBJS_EM = date.o event_data.o event_manager.o int_functions.o \
	member_data.o member_priority.o node.o priority_queue.o
OBJS_PQ = priority_queue.o node.o
EXEC_EM = event_manager
EXEC_PQ = priority_queue
DEBUG = # -g
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror $(DEBUG)

$(EXEC_EM) : $(OBJS_EM)
	gcc -std=c99 -o event_manager -Wall -pedantic-errors -Werror \
	-DNDEBUG tests/event_manager_tests.c -L. -lpriority_queue \
	$(OBJS_EM)

$(EXEC_PQ) : $(OBJS_PQ)
	gcc -std=c99 -o priority_queue -Wall -pedantic-errors -Werror \
	-DNDEBUG tests/priority_queue_tests.c $(OBJS_PQ)

date.o: date.c date.h

event_data.o: event_data.c event_data.h priority_queue.h date.h \
	int_functions.h member_data.h

event_manager.o: event_manager.c event_manager.h date.h priority_queue.h \
	member_data.h event_data.h member_priority.h

int_functions.o: int_functions.c int_functions.h priority_queue.h

member_data.o: member_data.c member_data.h priority_queue.h

member_priority.o: member_priority.c member_priority.h priority_queue.h

node.o: node.c priority_queue.h node.h

priority_queue.o: priority_queue.c priority_queue.h node.h

clean:
	rm -f $(OBJS_ALL) priority_queue event_manager