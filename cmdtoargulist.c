#include "cmdtoargulist.h"

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


