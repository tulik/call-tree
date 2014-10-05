objects = main.o druk.o decyzja.o analizator.o plik.o

all: $(objects)
	gcc -Wall -o drzewo $(objects)

install: $(objects)
	gcc -Wall -o drzewo $(objects)
	cp drzewo test1.c test2.c pomin.cfg ../build/

main.o: main.c

druk.o: druk.c druk.h

decyzja.o: decyzja.c decyzja.h

analizator.o: analizator.c analizator.h

plik.o: plik.c plik.h

clean:
	-rm *.o
	-rm drzewo
	-rm -f ../build/*
