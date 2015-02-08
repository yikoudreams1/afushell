#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int buildincmd(char * arguments[]);
void excute_externcmd();
extern int count;
extern int status;
extern char *argulist[],*argulist1[];
extern char *buf;
