# Makefile for the SIMP Program.

all : overlay crop colorshift bw

clean : 
	rm *.o bw colorshift crop overlay

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
	
tarball : 
	tar czf ajlende.tar.gz *.c *.h Makefile

testall : testcrop testcolorshift testbw testoverlay

testcrop : crop compare utils/bmp2simp utils/simp2bmp
	./utils/bmp2simp /test/BMP/insanity-cs229.bmp /test/SIMP/insanity-cs229.simp
	./crop /test/SIMP/insanity-cs229.simp /test/SIMP/o-insanity-cs229.simp
	./utils/simp2bmp /test/SIMP/o-insanity-cs229.simp /test/BMP/o-insanity-cs229.bmp

testcolorshift : colorshift compare utils/bmp2simp utils/simp2bmp
	./utils/bmp2simp keanu-cs229.bmp /test/SIMP/keanu-cs229.simp
	./colorshift /test/SIMP/keanu-cs229.simp /test/SIMP/keanurgb-cs229.simp RGB
	./colorshift /test/SIMP/keanu-cs229.simp /test/SIMP/keanurbg-cs229.simp RBG
	./colorshift /test/SIMP/keanu-cs229.simp /test/SIMP/keanurg-cs229.simp RG
	./colorshift /test/SIMP/keanu-cs229.simp /test/SIMP/keanurb-cs229.simp RB
	./colorshift /test/SIMP/keanu-cs229.simp /test/SIMP/keanugb-cs229.simp GB
	./utils/simp2bmp /test/SIMP/keanurgb-cs229.simp /test/BMP/keanurgb-cs229.bmp
	./utils/simp2bmp /test/SIMP/keanurbg-cs229.simp /test/BMP/keanurbg-cs229.bmp
	./utils/simp2bmp /test/SIMP/keanurg-cs229.simp /test/BMP/keanurg-cs229.bmp
	./utils/simp2bmp /test/SIMP/keanurb-cs229.simp /test/BMP/keanurb-cs229.bmp
	./utils/simp2bmp /test/SIMP/keanugb-cs229.simp /test/BMP/keanugb-cs229.bmp

testbw : bw compare utils/bmp2simp utils/simp2bmp
	./utils/bmp2simp /test/BMP/attached-cs229.bmp /test/SIMP/attached-cs229.simp
	./bw /test/SIMP/attached-cs229.simp /test/SIMP/o-attached-cs229.simp
	./utils/simp2bmp /test/SIMP/o-attached-cs229.simp /test/BMP/o-attached-cs229.bmp

testoverlay : overlay compare utils/bmp2simp utils/simp2bmp
	./utils/bmp2simp /test/BMP/doge-cs229.bmp /test/SIMP/doge-cs229.simp
	./overlay /test/SIMP/insanity-cs229.simp doge-cs229.simp /test/SIMP/o-insanedoge-cs229.simp 150 120
	./utils/simp2bmp /test/SIMP/o-insanedoge-cs229.simp /test/BMP/o-insanedoge-cs229.bmp

