#include "afushell.h"

int main(void)
{
       
      
        int i=0;
        
        printf("Welcome to afushell !\n ");
        printprompt();
		 while((buf=readline(" "))!=NULL)
        {

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

             if(buildincmd(argulist))
             {
				excute_externcmd();
             	}
			 printprompt();
		 }
	exit(0);
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
