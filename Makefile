# Makefile for the SIMP Program.
# 
#   Contents:
#    1. Default make command
#    2. clean command
#    3. tarball command
#    4. debug commands
#    5. test commands
#    6. run commands
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
debugall : debugcrop debugcolorshift debugbw debugoverlay

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



# 5. These are for comparing the simp output image to the one downloaded from the cs229 website
testall : testcrop testcolorshift testbw testoverlay

testcrop : crop utils/compare utils/bmp2simp utils/simp2bmp
	./crop test/SIMP/insanity.simp test/SIMP/c_insanity_o.simp 150 112 220 290
	./utils/compare test/SIMP/c_insanity.simp test/SIMP/c_insanity_o.simp

testcolorshift : colorshift utils/compare utils/bmp2simp utils/simp2bmp
	./colorshift test/SIMP/keanu.simp test/SIMP/keanurgb_o.simp RGB
	./colorshift test/SIMP/keanu.simp test/SIMP/keanurbg_o.simp RBG
	./colorshift test/SIMP/keanu.simp test/SIMP/keanurg_o.simp RG
	./colorshift test/SIMP/keanu.simp test/SIMP/keanurb_o.simp RB
	./colorshift test/SIMP/keanu.simp test/SIMP/keanugb_o.simp GB
	./utils/compare test/SIMP/keanurgb.simp test/SIMP/keanurgb_o.simp
	./utils/compare test/SIMP/keanurbg.simp test/SIMP/keanurbg_o.simp
	./utils/compare test/SIMP/keanurg.simp test/SIMP/keanurg_o.simp
	./utils/compare test/SIMP/keanurb.simp test/SIMP/keanurb_o.simp
	./utils/compare test/SIMP/keanugb.simp test/SIMP/keanugb_o.simp

testbw : bw utils/compare utils/bmp2simp utils/simp2bmp
	./bw test/SIMP/attached.simp test/SIMP/bw_attached_o.simp
	./utils/compare test/SIMP/bw_attached.simp test/SIMP/bw_attached_o.simp

testoverlay : overlay utils/compare utils/bmp2simp utils/simp2bmp
	./overlay test/SIMP/insanity.simp test/SIMP/doge.simp test/SIMP/insanedoge_o.simp 150 120
	./utils/compare test/SIMP/insanedoge.simp test/SIMP/insanedoge_o.simp



# 6. These use the simp files from the cs229 website run the command, and then export a bmp image for viewing
runall : runcrop runcolorshift runbw runoverlay

runcrop : crop utils/bmp2simp utils/simp2bmp
	./crop test/SIMP/insanity.simp test/SIMP/c_insanity_o.simp
	./utils/simp2bmp test/SIMP/c_insanity_o.simp test/BMP/c_insanity_o.bmp

runcolorshift : colorshift utils/bmp2simp utils/simp2bmp
	./colorshift test/SIMP/keanu.simp test/SIMP/keanurgb_o.simp RGB
	./colorshift test/SIMP/keanu.simp test/SIMP/keanurbg_o.simp RBG
	./colorshift test/SIMP/keanu.simp test/SIMP/keanurg_o.simp RG
	./colorshift test/SIMP/keanu.simp test/SIMP/keanurb_o.simp RB
	./colorshift test/SIMP/keanu.simp test/SIMP/keanugb_o.simp GB
	./utils/simp2bmp test/SIMP/keanurgb_o.simp test/BMP/keanurgb_o.bmp
	./utils/simp2bmp test/SIMP/keanurbg_o.simp test/BMP/keanurbg_o.bmp
	./utils/simp2bmp test/SIMP/keanurg_o.simp test/BMP/keanurg_o.bmp
	./utils/simp2bmp test/SIMP/keanurb_o.simp test/BMP/keanurb_o.bmp
	./utils/simp2bmp test/SIMP/keanugb_o.simp test/BMP/keanugb_o.bmp

runbw : bw utils/bmp2simp utils/simp2bmp
	./bw test/SIMP/attached.simp test/SIMP/bw_attached_o.simp
	./utils/simp2bmp test/SIMP/c_attached_o.simp test/BMP/bw_attached_o.bmp

runoverlay : overlay utils/bmp2simp utils/simp2bmp
	./overlay test/SIMP/insanity.simp test/SIMP/doge.simp test/SIMP/insanedoge_o.simp 150 120
	./utils/simp2bmp test/SIMP/insanedoge_o.simp test/BMP/insanedoge_o.bmp

