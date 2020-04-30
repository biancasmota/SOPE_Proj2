#ifndef SOPE_PROJ2_UTILS_H
#define SOPE_PROJ2_UTILS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>


#define IWANT "IWANT"
#define RECVD "RECVD"
#define ENTER "ENTER"
#define IAMIN "IAMIN"
#define TIMUP "TIMUP"
#define TOLATE "2LATE"
#define CLOSD "CLOSD"
#define FAILD "FAILD"
#define GAVUP "GAVUP"


void startTime();

double elapsed_time();

void writeRegister(int i, int pid, long tid, int dur, int pl, char *oper);


#endif //SOPE_PROJ2_UTILS_H
