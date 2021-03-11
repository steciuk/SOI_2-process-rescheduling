#include</usr/include/lib.h>
#include</usr/include/stdio.h>
#include<stdlib.h> 
#include<time.h>
#include<unistd.h>

int changegroup();
int getgroup();

int main(int argc, char* argv[])
{
	int i;

	if(getgroup() != 1)
	{	
		changegroup();
		printf("B pid: %d, zmiana grupy\n", getpid());
	}
	else
	{
		printf("B pid: %d, bez zmiany grupy\n", getpid());
	}		
	
	while(1 > 0)
    {
        for(i = 0; i<100000; i++)
        {
            ;
        }
    }
	
	return 0;
}

int changegroup()
{
	message msg;
	return(_syscall(0,CHANGEGROUP,&msg));
}

int getgroup()
{
	message msg;
	return(_syscall(0,GETGROUP,&msg));
}
