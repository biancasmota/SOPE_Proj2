#include "utils.h"

struct timespec start_time;

void startTime(){
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

double elapsed_time(){
    clock_gettime(CLOCK_MONOTONIC, &current);
    return (current.tv_sec-start_time.tv_sec)*1000+((current.tv_nsec-start_time.tv_nsec)/10e6);
}

void writeRegister(int i, int pid, long tid, int dur, int pl, char *oper) {
    printf("%ld ; %d ; %d ; %ld ; %d ; %d ; %s\n", time(NULL), i, pid, tid, dur, pl, oper);
    fflush(stdout);
}
