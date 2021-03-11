#include</usr/include/lib.h>
#include</usr/include/stdio.h>
#include<stdlib.h> 
#include<time.h>
#include<unistd.h>

int changegroup();
int getgroup();

int main(int argc, char* argv[])
{
	int i, j;
	time_t begin;
	time_t end;

	time(&begin);

	if(getgroup() != 0)
	{	
		changegroup();
		printf("A pid: %d, zmiana grupy\n", getpid());
	}
	else
	{
		printf("A pid: %d, bez zmiany grupy\n", getpid());
	}
			
	
	for(i=0; i<1000000;i++)
	{
		for(j=0; j<500;j++)
		{
			;
		}
	}
		
	time(&end);
	
	printf("A: %f\n", difftime(end, begin));
	
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
