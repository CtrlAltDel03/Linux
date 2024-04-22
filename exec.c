#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
void main()	
{
	int j=1;

	int i=0;
	pid_t p1;
	if(p1=fork()<0)
	{
		printf("lol");
		exit(0);
	}

	else if(p1==0 && j==0)
	{
		if(execl("/home/abhinav03g/Documents/tr","tr",(char*)0)<0)
		{
			printf("exec fucked");
			exit(0);

		}	
		i++;
		printf("%d",i);
		exit(0);
	}

			if(waitpid(p1,NULL,0)!=p1)
			 	printf("wait error");
			// if(p1=fork()<0)
			// {
			// 	printf("lol2");
			// 	exit(0);
			// }
	else if(p1==0 && j==1)
	{	
		if(execl("/home/abhinav03g/Documents/tr2","tr2",(char*)0)<0)
		{
			printf("exec 2 fucked");
			exit(0);

		}	
		i=100;
		printf("%d",i);
		exit(0);	
	}
	printf("sup");
	sleep(5);
	exit(0);
}
