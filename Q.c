#include "Q.h"

bool numStr(char* str)
{
    bool started = false;
    bool finished = false;
    int first = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(!started && str[i] != ' ')
            if(!isdigit(str[i]) && str[i] != '-') return false;
            else{started = true; first = i;}
        if(started)
        {
            if(i == first && (!isdigit(str[i]) && str[i] != '-')) return false;
            if(i != first && !isdigit(str[i]))
                if(str[i] == ' ') finished = true;
                else return false;
            if(finished && str[i] != ' ') return false;
        }
    }
    return started;
}

bool processArgs(int argc, char* argv[], double* nsecs, char* FIFO_path)
{
	if(argc != 4) return false;

	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i],"-t") == 0)
        {
            if(numStr(argv[i+1]))
            {
                *nsecs = atoi(argv[i+1]);
            }
            else return false;
            i++;
        }
        else
        {
        	strcpy(FIFO_path,argv[i]);
        }
	}
	return true;
}

int readline(int fd, char *str)
{
    int n;
    do
    {
        n = read(fd,str,1);
    }
    while (n>0 && *str++ != '\0');
    return (n>0);
}

process_client_args* new_ProcessClientArgs()
{
    process_client_args* args;
    args = malloc(sizeof(process_client_args));
    args->i = -1;
    args->pid = -1;
    args->tid = -1;
    args->dur = -1;
    args->pl = -1;
    return args;
}

bool parse_client_args(process_client_args* args, char* str)
{
    char * token = strtok(str,";");
    if(token != NULL && numStr(token))
    {
        args->i = atoi(token);
    }
    else return false;
    token = strtok(NULL,";");
    if(token != NULL && numStr(token))
    {
        args->pid = atoi(token);
    }
    else return false;
    token = strtok(NULL,";");
    if(token != NULL && numStr(token))
    {
        args->tid = atoi(token);
    }
    else return false;
    token = strtok(NULL,";");
    if(token != NULL && numStr(token))
    {
        args->dur = atoi(token);
    }
    else return false;
    token = strtok(NULL,";");
    if(token != NULL && numStr(token))
    {
        args->pl = atoi(token);
        return true;
    }
    return false;
}

void* process_client(void* arg)
{
    int fd;
    char path[MAX_FILE_NAME_LENGHT];
    process_client_args* args = (process_client_args*) arg;
    sprintf(path,"/tmp/%d.%d",args->pid, args->tid);
    do
    {
        fd=open(path,O_WRONLY);
        
    }while(fd == -1);
    free(arg);
    close(fd);
    return NULL;
}

int main_fifo_fd = -1;

void* look_for_clients(void* FIFO_path)
{
    pthread_t tid[MAX_THREADS];
    int curr_thread = 0;
    char  str[100];
    mkfifo(FIFO_path,0660);
    main_fifo_fd=open((char*)FIFO_path,O_RDONLY);
    while(readline(main_fifo_fd,str) && wc_open)
    {
        process_client_args* args = new_ProcessClientArgs();
        if(!parse_client_args(args,str))
        {
            fprintf(stderr,"Communication error: bad args\n");
        }
        
        if(pthread_create(&tid[curr_thread], NULL, process_client, args) != OK)
        {
            pthread_join(tid[curr_thread],NULL);
            fprintf(stderr,"System max threads reached\n");
            curr_thread++;
            pthread_exit(NULL);
        }
    }
    printf("finished reading, wc_open = %d \n", wc_open);
    close(main_fifo_fd);
    return NULL;
}

int main(int argc, char* argv[])
{
	double nsecs;
	char FIFO_path[MAX_FILE_NAME_LENGHT];   
    pthread_t tid;

	if(!processArgs(argc, argv, &nsecs, FIFO_path))
	{
		fprintf(stderr,"Argument error\n");
		return -1;
	}

    pthread_create(&tid, NULL, look_for_clients, FIFO_path);	
    time_t start, end;
    double elapsed;
    start = time(NULL);
    do
    {
        end = time(NULL);
        elapsed = difftime(end, start);
    }
    while (elapsed < nsecs);
    
    if(main_fifo_fd != -1)
        pthread_join(tid,NULL);
    
    wc_open = false;

    remove(FIFO_path);

	return 0;
}