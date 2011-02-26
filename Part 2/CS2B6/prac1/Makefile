#The CC variable holds the compiler to use
CC = gcc

#The default target executes practical1 dependancy
all : practical1

#Compiles the executable
practical1: mycat.c filecopy.o
	$(CC) -o practical1 filecopy.o mycat.c

#Compiles the object file
filecopy.o: filecopy.c
	$(CC) -c filecopy.c

#Clear all object files
clean :
	rm *.o
