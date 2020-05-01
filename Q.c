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
    
    sprintf(path,"/tmp/%d.%d",args->pid,args->tid);
    fd = open(path,O_WRONLY);

    if(fd = -1)
    {
        printf("%ld;%d ; %d ; %d ; %d ; %d ; GAVUP\n", time(NULL), args->i, args->pid, args->tid, args->dur, args->pl);        
    }
    else
    {
        char  message[MAX_FILE_NAME_LENGHT];
        int messagelen;
        
        if(!wc_open)
        {
            printf("%ld;%d ; %d ; %d ; -1 ; -1 ; 2LATE\n", time(NULL), args->i, args->pid, args->tid);
            printf(message,"%d; %d; %d; -1; -1", args->i, args->pid, args->tid);
            messagelen=strlen(message)+1;
            write(fd,message,messagelen);
        }
        else
        {

            for(int i = 0; i < MAX_THREADS; i++)
            {
                if(places[i] == 0)
                {
                    args->pl = i;
                    places[i] = 1;
                }
            }            
            printf(message,"%d; %d; %d; %d; %d", args->i, args->pid, args->tid, args->dur, args->pl);
            messagelen=strlen(message)+1;
            write(fd,message,messagelen);
            printf("%ld;%d ; %d ; %d ; %d ; %d ; ENTER\n", time(NULL), args->i, args->pid, args->tid, args->dur, args->pl);
            usleep(args->dur * 1000);
            printf("%ld;%d ; %d ; %d ; %d ; %d ; TIMUP\n", time(NULL), args->i, args->pid, args->tid, args->dur, args->pl+1);
            places[args->pl] = 0;
        }
    }
    free(arg);
    close(fd);
    return NULL;
}

void* look_for_clients(void* FIFO_path)
{
    pthread_t tid[MAX_THREADS];
    int curr_thread = 0;
    char  str[100];
    mkfifo(FIFO_path,0660);
    main_fifo_fd=open((char*)FIFO_path,O_RDONLY);
    while(readline(main_fifo_fd,str))
    {
        process_client_args* args = new_ProcessClientArgs();
        if(!parse_client_args(args,str))
        {
            fprintf(stderr,"Communication error: bad args\n");
        }    
        else{
            printf("%ld;%d ; %d ; %d ; %d ; %d ; RECVD\n", time(NULL), args->i, args->pid, args->tid, args->dur, args->pl);
            if(pthread_create(&tid[curr_thread], NULL, process_client, args) != OK)
            {
                pthread_join(tid[curr_thread],NULL);
                fprintf(stderr,"System max threads reached\n");
                curr_thread++;
                pthread_exit(NULL);
            }
        }
    }
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
    
    wc_open = false;
    if(main_fifo_fd != -1)
        pthread_join(tid,NULL);
    

    remove(FIFO_path);

	return 0;
}