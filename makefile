#Author:	Jesus Minjares BSEE
CC = gcc
Lib = -lpthread
file = catalan_sequence
$(file):	$(file).o
	$(CC) $(file).o -o $(file) $(Lib)
$(file).o:	$(file).c 
	$(CC) -c $(file).c 
clean:
	rm *.o $(file) *.dat 