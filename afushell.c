#include<sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#define MAXLINE 4096


int cmdtoargulist(char* cmdLine,char* argList[20]);
void printprompt();
int buildincmd(char * arguments[]);
int main(void)
{
        char *buf;
        pid_t pid,pid1;
        int status;
       int count=0;
        char* argulist[20],*argulist1[20];
        int i=0,j=0;
        int fd[2];
        printf("Welcome to afushell !\n ");
        printprompt();
        while((buf=readline(" "))!=NULL)
        {
//             if (buf[strlen(buf)-1] == '\n')
//             {
//                 buf[strlen(buf)-1] = 0;
//            }   

            for(i=0;i<20;i++)
            {
                argulist[i]=(char*)malloc(sizeof(char)*100);
                argulist1[i]=(char*)malloc(sizeof(char)*100);
                memset(argulist[i],'\0',sizeof(char)*100);
                memset(argulist1[i],'\0',sizeof(char)*100);
           }
             
             if(!(count=cmdtoargulist(buf,argulist)))
            {
              printf("explan the cmd is wrong");
            }
//             for(i=0;i<20;i++)
//    {
//        if(argulist[i][0]!='\0'){ count++;}
//printf("%d\n",count);
//for(i=0;i<20;i++)
//{printf("%s\n",argulist[i]);}
//    }
             if(buildincmd(argulist))
             {
                 j=0;
                 for(i=0;i<count;i++)
                 {
                     if(argulist[i][0]=='|')
                     j=i;
                 }
                 if(j!=0)
                 {
//                        printf("in |\n");
                         argulist[j]=(char*)0;
                        for(i=0;i<20;i++)
                        {
                        argulist1[i]=argulist[i+1+j];
                        }
 //printf("%s,%s\n",argulist[0],argulist1[0]);
                        if((pid = fork())<0)
                        {
                         printf("fork error");
                        }
                        
                        else if(pid == 0)
                        { 

                            if(pipe(fd)<0)
                            {printf("pipe error");
                                exit(0);
                            }
                            printf("%s",buf);
                            if((pid1= fork())<0)
                            {
                            printf("fork error");
                            }
                             else if(pid1==0)
                             {
                                 close(fd[1]);
                                dup2(fd[0],0);
                                execvp(argulist1[0],argulist1);
                                printf("couldn't execute: %s\n",buf);
                                exit(127);
                             }
                             else
                             {
                             close(fd[0]);
                        dup2(fd[1],1);
                        execvp(argulist[0],argulist);
                        printf("couldn't execute: %s\n",buf);
                        exit(127);
                        }  } 

                        else{                         /*parent*/
                        if ((pid=waitpid(pid,&status,0))<0)
                         {
                            printf("waitpid error");
                            }

                        }
                 }
                 else{
//                     printf("not in |");
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
                 else if ((pid=waitpid(pid,&status,0))<0)
                 {
                    printf("waitpid error");
                }
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
        int i = 0,j=1;
        pChar = argList[0];
        while(1)
        {
          aChar = *cmdLine;
          cmdLine++;
          if(aChar == ' ')
             {
              *pChar = '\0';
              i++;
              j++;
              pChar = argList[i];
             }
         else if(aChar == '\0')
             {
              *pChar = '\0';
              i++;
              argList[i] = 0; 
             
              return j;
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
