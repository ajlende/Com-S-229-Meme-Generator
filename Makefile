# Makefile for the SIMP Program.

all : overlay crop colorshift bw

tarball : 
	tar czf ajlende.tar.gz *.c *.h Makefile

clean : 
	rm *.o bw colorshift crop overlay

overlay.o : overlay.c simp.h
	gcc -ansi -c overlay.c

crop.o : crop.o simp.h 
	gcc -ansi -c crop.c

colorshift.o : colorshift.c simp.h
	gcc -ansi -c colorshift.c

bw.o : bw.c simp.h
	gcc -ansi -c bw.c

overlay : overlay.o
	gcc -ansi -o overlay overlay.o

crop : crop.o
	gcc -ansi -o crop crop.o

colorshift : colorshift.o
	gcc -ansi -o colorshift colorshift.o

bw : bw.o
	gcc -ansi -o bw bw.o

