#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_FILE_NAME_LENGHT 1024
#define OK 0


bool numStr(char* str);
bool processArgs(int argc, char* argv[], double* nsecs, char* FIFO_path);