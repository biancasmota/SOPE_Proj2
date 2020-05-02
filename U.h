#ifndef SOPE_PROJ2_U_H
#define SOPE_PROJ2_U_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_THR 100000
#define SIZE 256
#define RAND 3000

int i = 0;
bool wc_open = true;

bool numStr(char* str);
bool processArgs(int argc, char* argv[], double* nsecs, char* FIFO_path);

#endif //SOPE_PROJ2_U_H
