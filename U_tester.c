#include "Q.h"

int main(int argc, char* argv[])
{
	int   fd, messagelen, i;
	char  message[100];

	do
	{
		fd=open(argv[1],O_WRONLY);
		if(fd == -1) sleep(1);
	}while(fd == -1);

	for (i=1; i < 30; i++)
	{
		printf("msg n %d\n", i);
		int dur = (rand() % 1000)+1; 
		sprintf(message, "[ %d, %d, %ld, %d, %d ]\n", i, getpid(), (long int)i+111, dur, -1);
		messagelen=strlen(message)+1;
		write(fd,message,messagelen);
		usleep(250 *1000);
	}
	close(fd);
}