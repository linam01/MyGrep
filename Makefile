CC = gcc
OPTION =-W -Wall -pedantic -ansi -O3 

mygrep :  main.o  fonction.o liste.o option.o recherche.o utilitaire.o
	$(CC) $(OPTIONS) main.o fonction.o liste.o option.o recherche.o utilitaire.o -o mygrep 

main.o : main.c
	$(CC) $(OPTIONS) -c main.c

fonction.o : fonction.c fonction.h
	$(CC) $(OPTIONS) -c fonction.c

liste.o : liste.c liste.h
	$(CC) $(OPTIONS) -c liste.c

option.o : option.c option.h
	$(CC) $(OPTIONS) -c option.c

recherche.o : recherche.c recherche.h
	$(CC) $(OPTIONS) -c recherche.c

utilitaire.o : utilitaire.c utilitaire.h
	$(CC) $(OPTIONS) -c utilitaire.c

clean :
	rm -rf *.o *~ grep



