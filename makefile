CC = gcc
CFLAGS = -Wall -pthread
DEPS = utils.h
OBJ = utils.o
TARGETS = U1 Q1

all: U Q

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo $@

U: $(OBJ)
	@$(CC) $(CFLAGS) -o $@1 $@.c $(OBJ)
	@echo $@

Q: $(OBJ)
	@$(CC) $(CFLAGS) -o $@1 $@.c $(OBJ)
	@echo $@

clean:
	@rm *.o $(TARGETS)