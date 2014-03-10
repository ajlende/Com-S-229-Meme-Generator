# Makefile for the SIMP Program.
# 
#   Contents:
#    1. Default make command
#    2. clean command
#    3. tarball command
#    4. debug commands
#

CC=gcc -ansi -pedantic
CFLAGS= 
DEPS=simp.h memelib.h


# 1. Default make command to compile all of the programs normally
all : overlay crop colorshift bw meme

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

overlay : overlay.o simp.o
	$(CC) $(CFLAGS)  -o overlay overlay.o simp.o

crop : crop.o simp.o
	$(CC) $(CFLAGS)  -o crop crop.o simp.o

colorshift : colorshift.o simp.o
	$(CC) $(CFLAGS)  -o colorshift colorshift.o simp.o

bw : bw.o simp.o
	$(CC) $(CFLAGS)  -o bw bw.o simp.o

meme : meme.o memelib.o simp.o
	$(CC) $(CFLAGS)  -o meme meme.o memelib.o simp.o



# 2. This will clean out any non-source files from the directory
clean : 
	rm *.o bw colorshift crop overlay meme



# 3. This will make a tarball from the files for submission
tarball : 
	tar czf ajlende.tar.gz *.c *.h Makefile README

