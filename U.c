#include "utils.h"
#include "utils.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#define MAX_THR 100000
#define SIZE 256
#define RAND 30

int closed = 0;
int i = 1;

void *pedidos(void *arg){
    char *fifo = arg;
    int pid = getpid();
    long int tid = pthread_self();
    char msg[SIZE];
    int fd = open(fifo,O_WRONLY);
    int time = rand()% RAND + 1;

    if (fd==-1) {
        closed = 1;
        writeRegister(i,pid,tid,time,-1,CLOSD);
        printf("WC is closed!\n");
        return NULL;
    }

    //writeRegister(i,pid,tid, time, -1, IWANT);

}


int main(int argc, char *argv[])
{
    int nsecs = atoi(argv[2]);
    char* fifo = argv[3];
    char fifopath[SIZE]="tmp/";
    pthread_t threads[MAX_THR];
    int thr=0;

    strcat(fifopath,fifo);

    while(elapsed_time()< (double) nsecs)
    {
        pthread_create(&threads[thr],NULL,pedidos,fifopath);
        pthread_detach(threads[thr]);
        usleep(100000);
        thr++;
        i++;
    }

    return 0;
}



