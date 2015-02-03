#include<sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 4096


int cmdtoargulist(char* cmdLine,char* argList[20]);

int main(void){
        char buf[MAXLINE];
        pid_t pid;
        int status;
        char* argulist[20];
        int i=0,j=0;
        printf("%% ");
        while(fgets(buf,MAXLINE,stdin)!=NULL){
             if (buf[strlen(buf)-1] == '\n'){
                 buf[strlen(buf)-1] = 0;
               }   

       for(i=0;i<20;i++)
       {
           argulist[i]=(char*)malloc(sizeof(char)*100);
           memset(argulist[i],'\0',sizeof(char)*100);
                   }
             
       if(cmdtoargulist(buf,argulist)==1)
       {printf("explan the cmd is wrong");}

             if((pid = fork())<0){
               printf("fork error");
               }else if(pid == 0){ 
                      printf("%s",buf);
                      execvp(argulist[0],argulist);
                      printf("couldn't execute: %s",buf);
                      exit(127);
                  }   

                                                    /*parent*/
        if ((pid=waitpid(pid,&status,0))<0){
            printf("waitpid error");
            }   
         printf("%% ");
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
