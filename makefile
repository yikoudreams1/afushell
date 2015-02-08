afushelll : afushell.o cmdtoargulist.o excute.o
	gcc -o afushell afushell.o cmdtoargulist.o excute.o -D READLINE_ON -I /usr/include -lreadline

cmdtoargulist.o : cmdtoargulist.c cmdtoargulist.h
	gcc -c cmdtoargulist.c

excute.o : excute.c excute.h
	gcc -c excute.c

afushell.o : afushell.c afushell.h
	gcc -c afushell.c -D READLINE_ON -I /usr/include -lreadline 

clean :
	rm afushell *.o
