/*********************************************************/
/*	Project to create parent-child process		*/
/*	using execl(built in fork)		       */
/******************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
 	int status;	
	char buff[50];
	int proc_pid = getpid();
	printf("The process pid is %d\t",proc_pid);

	//while(gets(buff))
	while(fgets(buff,sizeof(buff),stdin) != NULL )
	{ printf("Enter the command");
	status = execl("/usr/pkg/bin/bash",buff,NULL);
 	return(status);
	}
}
