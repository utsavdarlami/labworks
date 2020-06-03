CFLAGS=-Wall -g -Werror -std=gnu99 -pedantic -ggdb3
OBJS=singlylinkedlist.o main.o
PROGRAM=linkedlist

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)
%.o: %.c singlylinkedlist.h
	gcc -c $(CFLAGS) $<
clean:
	rm -f $(OBJS) $(PROGRAM) *~

