CC = gcc
OPTION =-W -Wall -pedantic -ansi -O3 

mygrep :  main.o  fonction.o
	$(CC) $(OPTIONS) main.c  fonction.o -o mygrep 

main.o : main.c
	$(CC) $(OPTIONS) -c main.c

fonction.o : fonction.c fonction.h
	$(CC) $(OPTIONS) -c fonction.c

clean :
	rm -rf *.o *~ grep



