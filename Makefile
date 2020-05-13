CC = gcc
CFLAGS = -Wall -pthread
TARGETS = U1 Q1

all: U Q

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	echo $@

U: $(OBJ)
	rm -f $@1.o
	$(CC) -o $@1 $@.c $(OBJ) $(CFLAGS)
	echo Created $@1

Q: $(OBJ)
	rm -f $@1.o
	$(CC) -o $@1 $@.c $(OBJ) $(CFLAGS)
	echo Created $@1

clean:
	rm -f *.o $(TARGETS)
	rm -f *.log $(TARGETS)
	rm -f *.err $(TARGETS)

