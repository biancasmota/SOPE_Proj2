all: Q U

program1:
	gcc  -o Q Q.c -lpthread -Wall -ansi -pedantic

program2:
	gcc -o U U.c -pthread -Wall -ansi -pedantic 