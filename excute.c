#include "excute.h"

int buildincmd(char * arguments[])
{
    if(strcmp(arguments[0],"cd")==0)
    {
            if(chdir(arguments[1])!=0)
                    printf("change directory failed\n");
            return 0;
    }
    else if(strcmp(arguments[0],"exit")==0)
    {        printf("Thank you for use afushell,bye!\n");
            exit(0);       
    }    
    else if(strcmp(arguments[0],"export")==0)
    {        char *name,*value;
            name=strtok(arguments[1],"=");
            value=strtok(NULL,"+");
            if(name==NULL || value==NULL)
            {
                printf("set environment failed\n");
                return 0;
            }
            if(setenv(name,value,1)!=0)
            {
                printf("set environment failed\n");
                return 0;
            }
    }
    else if(strcmp(arguments[0],"echo")==0)
    {        printf("%s\n",getenv(arguments[1]));
            return 0;
    }
    else    return 1;
    
    
}

void excute_externcmd()
{
	int i=0,j=0;
	 pid_t pid,pid1;
	 int fd[2];
					 for(i=0;i<count;i++)
					 {
						 if(argulist[i][0]=='|')
						 j=i;
					 }
			 if(j!=0)
			{
							 argulist[j]=(char*)0;
							for(i=0;i<20;i++)
							{
							argulist1[i]=argulist[i+1+j];
							}
								if(pipe(fd)<0)
								{printf("pipe error");
									exit(0);
								}
							if((pid = fork())<0)
							{
							 printf("fork error");
							}
							
							else if(pid != 0)
							{ 
	
							//	printf("%s",buf);
							   /* if ((pid=waitpid(pid,&status,0))<0)
							        {
								        printf("waitpid error");
								    }
                                    */
								if((pid1= fork())<0)  //the second command
								{
								printf("fork error");
								}
								 else if(pid1==0)
								 {
									 close(fd[1]);
									dup2(fd[0],0);
                                    close(fd[0]);
									execvp(argulist1[0],argulist1);
									printf("couldn't execute: %s\n",buf);
									exit(127);
								 }
	
							    else{						  /*parent*/
							        close(fd[0]);
                                    close(fd[1]);
                                    if ((pid=waitpid(pid1,&status,0))<0)
							        {
								        printf("waitpid error");
								    }
	
							    }
                            }
							 else // the first comman
								 {
								 close(fd[0]);
							dup2(fd[1],1);
                            close(fd[1]);
							execvp(argulist[0],argulist);
							printf("couldn't execute: %s\n",buf);
							exit(127);
							}   
			 }
		else
			{
					 if((pid = fork())<0)
					 {
						printf("fork error");
					}
					 else if(pid == 0)
					 { 
			//			  printf("%s",buf);
						  execvp(argulist[0],argulist);
						  printf("couldn't execute: %s\n",buf);
						  exit(127);
					  }   
	
														/*parent*/
					 else if ((pid=waitpid(pid,&status,0))<0)
					 {
						printf("waitpid error");
					}
			}
}

