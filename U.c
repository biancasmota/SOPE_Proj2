#include "utils.h"
#include "utils.c"
#include "U.h"

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

void *pedidos(void *arg)
{
    char *fifo = arg;
    int pid = getpid();
    long int tid = pthread_self();
    char msg[SIZE];
    int fd = open(fifo,O_WRONLY);
    int time = rand()% RAND + 1;

    if (fd==-1)
    {
        writeRegister(i,pid,tid,time,-1,CLOSD);
        //printf("WC is closed\n");
        return NULL;
    }


    sprintf(msg, "[ %d, %d, %ld, %d, %d ]\n", i, pid, tid, time, -1);
    if (write(fd, &msg, SIZE) < 0)
        return NULL;

    close(fd);
/*
    char private_fifo[SIZE]="tmp/";
    int fd_priv;
    char temp[SIZE];
    int id, s_pid, pl, dur, fd_private; //WC
    long s_tid;

    sprintf(temp,"%d",pid);
    strcat(private_fifo,temp);
    strcat(private_fifo,".");
    sprintf(temp,"%ld",tid);
    strcat(private_fifo,temp);

    printf("%s\n", private_fifo);

    if (mkfifo(private_fifo, 0660) != 0) //create private FIFO
    {
        writeRegister(i, pid, tid, time, -1, FAILD);
        printf("Error creating private FIFO\n");
        return NULL;
    }

    if ((fd_priv = open(private_fifo, O_RDONLY)) < 0) //open private FIFO
    {
        printf("Error opening private FIFO");
        return NULL;
    }

    if (read(fd_priv, &msg, SIZE) > 0) //read private FIFO
        sscanf(msg, "[ %d, %d, %ld, %d, %d ]\n", &id, &s_pid, &s_tid, &dur, &pl);

    if (pl == -1 && dur == -1) //closing
        writeRegister(i, pid, tid, dur, pl, CLOSD);
    else    //open
        writeRegister(i, pid, tid, dur, pl, IAMIN);

    close(fd_priv);
    if(unlink(private_fifo) < 0)    //Destroys private FIFO
        printf("Error destroying Private FIFO\n");
*/
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

int main(int argc, char *argv[])
{
    double nsecs;
    char fifo[1024];
    if(!processArgs(argc, argv, &nsecs, fifo))
    {
        fprintf(stderr,"Argument error\n");
        return -1;
    }
    //char fifopath[SIZE]="tmp/";
    pthread_t threads[MAX_THR];
    int thr=0;

    //strcat(fifopath,fifo);

    time_t start, end;
    double elapsed;
    start = time(NULL);
    do
    {
        end = time(NULL);
        pthread_create(&threads[thr],NULL,pedidos,fifo);
        //pthread_detach(threads[thr]);
        thr++;
        i++;
        usleep(100 * 1000);
        elapsed = difftime(end, start);
    }
    while (elapsed < nsecs);

    return 0;
}




