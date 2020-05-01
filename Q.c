#include "Q.h"

bool numStr(char* str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(!isdigit(str[i])) return false;
    }
    return true;
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

void* look_for_clients(void* FIFO_path)
{
    mkfifo(FIFO_path,0660);
    char  str[100];
    int fd=open((char*)FIFO_path,O_RDONLY);
    while(readline(fd,str)) printf("%s",str);
    close(fd);
    return NULL;
}

int main(int argc, char* argv[])
{
	int   fd;
	double nsecs;
	char FIFO_path[MAX_FILE_NAME_LENGHT];
    
    pthread_t tid;

	if(!processArgs(argc, argv, &nsecs, FIFO_path))
	{
		printf("Argument error\n");
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

    close(fd);

	return 0;
}