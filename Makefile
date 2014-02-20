# Makefile for the SIMP Program.
# 
#   Contents:
#    1. Default make command
#    2. clean command
#    3. tarball command
#    4. debug commands
# 

# 1. Default make command to compile all of the programs normally
all : overlay crop colorshift bw

overlay.o : overlay.c simp.h
	gcc -ansi -pedantic -c overlay.c

crop.o : crop.c simp.h 
	gcc -ansi -pedantic -c crop.c

colorshift.o : colorshift.c simp.h
	gcc -ansi -pedantic -c colorshift.c

bw.o : bw.c simp.h
	gcc -ansi -pedantic -c bw.c

overlay : overlay.o simp.o
	gcc -pedantic -o overlay overlay.o simp.o

crop : crop.o simp.o
	gcc -pedantic -o crop crop.o simp.o

colorshift : colorshift.o simp.o
	gcc -pedantic -o colorshift colorshift.o simp.o

bw : bw.o simp.o
	gcc -pedantic -o bw bw.o simp.o



# 2. This will clean out any non-source files from the directory
clean : 
	rm *.o bw colorshift crop overlay



# 3. This will make a tarball from the files for submission
tarball : 
	tar czf ajlende.tar.gz *.c *.h Makefile



# 4. This runs all the compiling with the gcc -g flag for gdb debugging
debug : debugcrop debugcolorshift debugbw debugoverlay

debugcrop : crop crop.o simp.o crop.c simp.h
	gcc -ansi -pedantic -c crop.c
	gcc -pedantic -g -o crop crop.o simp.o

debugcolorshift : colorshift colorshift.o simp.o colorshift.c simp.h
	gcc -ansi -pedantic -c colorshift.c
	gcc -pedantic -g -o colorshift colorshift.o simp.o

debugbw : bw bw.o simp.o bw.c simp.h
	gcc -ansi -pedantic -c bw.c
	gcc -pedantic -g -o bw bw.o simp.o

debugoverlay : overlay overlay.o simp.o overlay.c simp.h
	gcc -ansi -pedantic -c overlay.c
	gcc -pedantic -g -o overlay overlay.o simp.o

