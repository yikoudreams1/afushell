#include<sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#define MAXLINE 4096


extern int cmdtoargulist(char* cmdLine,char* argList[20]);

extern int buildincmd(char * arguments[]);

extern void excute_externcmd();

void printprompt();

char* argulist[20],*argulist1[20];

int status;

int count=0;

char *buf;
