#include</usr/include/lib.h>
#include</usr/include/stdio.h>
#include<stdlib.h> 
#include<unistd.h>

int setscheduler(int proc_id);

int main(int argc, char* argv[])
{
	int result;
	int arg;
	message m;
	
	if(argc < 2)
	{
		printf("no argument\n");
	}
	else
	{
		arg = atoi(argv[1]);
		result = setscheduler(arg);
		if(result == 0)
		{
			printf("sheduler set\n");
		}
		else
		{
			printf("cant set sheduler, pid: %d, err: %d\n", getpid(), result);
		}
	}
	
	return 0;
}

int setscheduler(int arg)
{
	message msg;
	msg.m1_i1=arg;
	return(_syscall(0,SETSCHEDULER,&msg));
}
