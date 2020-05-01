#pragma once

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
#define MAX_THREADS 1000
#define OK 0

bool wc_open = true;
int main_fifo_fd = -1;
int places[MAX_THREADS] = {0};

typedef struct look_for_clients_args
{
	char FIFO_path[MAX_FILE_NAME_LENGHT];
}look_for_clients_args;

typedef struct process_client_args
{
	int i;
	int pid;
	int tid;
	int dur;
	int pl;
}process_client_args;

bool numStr(char* str);
bool processArgs(int argc, char* argv[], double* nsecs, char* FIFO_path);
