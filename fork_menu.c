#include<stdio.h>
#include<string.h>
//#include<wait.h>
#include<time.h>
#include<signal.h>


void update_list(pid_t chdpid,char methodname[255])//, int* listsize; pid_t* list )
{ int k,j;
	int killindex=0;
	char matchfound = "false";
	
	int listsize =0;
	pid_t list[50];

	if(methodname == "kill")
	{
		for (k = 0; k<listsize;k++)
		{
			if (list[k] == chdpid)
			{
			killindex = k;
			matchfound = "true";
			break;
			}
		} 
		if(matchfound == "true")
		{
			if(killindex != (listsize -1))
			{
				for(j = killindex; j<listsize ; j--)
				{
					if(j != (listsize -1))
					{
					list[j] = list[j++];
					}
				}
				listsize--;
			}
			else
			{
				listsize--;
			}
		}
		else
		{
			printf("No such PID: %s found",chdpid);
		}
	}
	else if (methodname == "sleep")
	{
		list[listsize] = chdpid;
		listsize++;
	}
}	
		
int main(int argc,char* argv[])
{
	
	FILE* fptime;
	pid_t list[50];//array of pid
	char line[100];
	int wstat;
	pid_t chdpid,pid2,pid;	
	int listsize = 0;
	/*int * ptrsize;
	ptrsize = &listsize;
	pid_t* listptr;
	listptr = &list[0];*/
		
	if ((strcmp(argv[1],"sleep")) == 0)
	{
	  	  	pid = fork();


		if(pid>0)
		{
			printf("hello parent,child pid = %d\n",pid);
		}
		else if (pid == 0)
		{

			printf("hello from child\n");

			chdpid = getpid();

			printf("My pid%d\n",chdpid);

		//	update_list(chdpid,"sleep",&listsize, list);		
			
		       int stat = sleep(atoi(argv[2]));
			
			if(stat == 0)
			{
			printf("Child process has finished sleeping");
			}


		}
		else
		{
			printf("fork failed\n");

		}
	}

/*	if (strcmp(argv[1],"wait") == 0)
	{
		pid2 = atoi(argv[2]);
		{
		wstat =	wait(pid2);
		printf("Wait status%d",wstat);
		}
	}

	if (strcmp(argv[1],"time")==0)
	{
	time_t start,end;

	start= time(NULL);
	sleep(10);
	end = time(NULL);
	 diff = difftime(end,start);
	printf("Time%.2f",diff);

	}
*/
	if(strcmp(argv[1],"time")==0)
	{
		pid_t pid_time = atoi(argv[2]);
		char command[50];
		sprintf(command,"ps|grep %d",pid_time);
		printf(command);
		fptime = popen(command,"r");
		char* timepos;
		int colcount;

		while(fgets(line, 100, fptime) != NULL)
		{
			timepos = strtok(line, " ");
			//printf(timepos);
			while((timepos != NULL)) //&& (colcount != 4))
			{
				if(strchr(timepos, ':') != NULL)
					printf("time%s\n",timepos);
				timepos = strtok(NULL, " ");
				/*printf("time%s\n",timepos);
				colcount = 2;
				colcount++;*/
			}
		}
	}

	if (strcmp(argv[1],"kill")==0)
	{
		pid_t pid_tobe_killed = atoi(argv[2]);
		int status = kill(pid_tobe_killed,SIGINT);
		if(status > 0)
		{printf("Error occurred during kill\n");}
		else if (status == 0)
		{
			printf("%d has been killed\n",pid_tobe_killed);
			//update_list(pid_tobe_killed,"kill",&listsize,list);
		}
	}

	if(strcmp(argv[1],"list") == 0)
	{int l;
		if(listsize >0)
		{printf("List of PIDS:\n");
		for(l=0;l<listsize;l++)
		{
		printf("%d\t%s",l+1,list[l]);
		}
		}
		else
		printf("There are no child processes running");
	}

		

return(0);

}
