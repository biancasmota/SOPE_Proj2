#include "U.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int nsecs = atoi(argv[2]);
    char* fifo = argv[3];

    //mkfifo(fifo, 0660); //abrir o fifo

    pedidos(nsecs);


    return 0;
}

int pedidos(int nsecs){
    time_t start, end;
    double elapsed;  // seconds
    start = time(NULL);
    int terminate = 1;
    while (terminate) {
        end = time(NULL);
        elapsed = difftime(end, start);
        if (elapsed >= nsecs /* seconds */)
            terminate = 0;
        /*else  // No need to sleep when 90.0 seconds elapsed.
            usleep(50000);*/
        lancar_tread();
    }
    return 0;
}

