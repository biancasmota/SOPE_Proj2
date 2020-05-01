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


int main(int argc, char* argv[])
{
	int   fd;
	double nsecs;
	char FIFO_path[MAX_FILE_NAME_LENGHT];

	if(!processArgs(argc, argv, &nsecs, FIFO_path))
	{
		printf("Argument error\n");
		return -1;
	}

	fd = open(FIFO_path,O_RDONLY);


	/*time_t start, end;
    double elapsed;
    start = time(NULL);
    do
    {
		end = time(NULL);
        elapsed = difftime(end, start);
    }
    while (elapsed < nsecs);
*/	

	return 0;
}