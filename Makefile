CC = gcc
OPTION =-W -Wall -pedantic -ansi -O3 

mygrep :  main.o  fonction.o liste.o
	$(CC) $(OPTIONS) main.c  fonction.o liste.o -o mygrep 

main.o : main.c
	$(CC) $(OPTIONS) -c main.c

fonction.o : fonction.c fonction.h
	$(CC) $(OPTIONS) -c fonction.c

liste.o : liste.c liste.h
	$(CC) $(OPTIONS) -c liste.c

clean :
	rm -rf *.o *~ grep



