#include<sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 4096


int cmdtoargulist(char* cmdLine,char* argList[20]);
void printprompt();
int buildincmd(char * arguments[]);
int main(void)
{
        char buf[MAXLINE];
        pid_t pid;
        int status;
        char* argulist[20];
        int i=0,j=0;
        printf("Welcome to afushell !\n ");
        printprompt();
        while(fgets(buf,MAXLINE,stdin)!=NULL)
        {
             if (buf[strlen(buf)-1] == '\n')
             {
                 buf[strlen(buf)-1] = 0;
            }   

            for(i=0;i<20;i++)
            {
                argulist[i]=(char*)malloc(sizeof(char)*100);
                memset(argulist[i],'\0',sizeof(char)*100);
           }
             
             if(cmdtoargulist(buf,argulist)==1)
            {
              printf("explan the cmd is wrong");
            }

             if(buildincmd(argulist))
             {
                 if((pid = fork())<0)
                 {
                    printf("fork error");
                }
                 else if(pid == 0)
                 { 
                      printf("%s",buf);
                      execvp(argulist[0],argulist);
                      printf("couldn't execute: %s\n",buf);
                      exit(127);
                  }   

                                                    /*parent*/
                 if ((pid=waitpid(pid,&status,0))<0)
                 {
                    printf("waitpid error");
                }
             }
         printprompt();
             }   
          exit(0);
}
 
int cmdtoargulist(char* cmdLine,char* argList[20])
{
        char aChar;
        char* pChar;
        int i = 0;
        pChar = argList[0];
        while(1)
        {
          aChar = *cmdLine;
          cmdLine++;
          if(aChar == ' ')
             {
              *pChar = '\0';
              i++;
              pChar = argList[i];
             }
         else if(aChar == '\0')
             {
              *pChar = '\0';
              i++;
              argList[i] = 0; 
              return 0;
             }
          else
             {
             *pChar = aChar;
             pChar++;
             }
        }

}
void printprompt()
{
    char *promptenvironment=getenv("PE");
         char buf[MAXLINE];
    if(promptenvironment==NULL)
    {

                         printf("%s@",getlogin());
                        gethostname(buf,MAXLINE);
                        printf("%s:",buf);
                         getcwd(buf,MAXLINE);
                         printf("%s>",buf);
    }
    else 
    {
         int len=strlen(promptenvironment);
         int i;
         for(i=0;i<len;i++)
         {
             if(promptenvironment[i]='\\')
             {
                 switch(promptenvironment[++i])
                 {
                     case 'u':
                         printf("%s",getlogin());
                         break;
                     case 'h':
                         getcwd(buf,MAXLINE);
                         printf("%s",buf);
                         break;
                    case 'w':
                        gethostname(buf,MAXLINE);
                        printf("%s",buf);
                        break;
                    default:
                        printf("%c",promptenvironment[i]);
                }
             }
             printf("%c",promptenvironment[i]);
         }
    }         if(strcmp("root",getlogin())==0)
             printf(" # ");
         else printf(" $ ");
    
    fflush(NULL);
}


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
