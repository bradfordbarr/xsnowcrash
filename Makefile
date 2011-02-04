CC=gcc
EXE=xsnowcrash
LDFLAGS=-lX11 -lGL -lGLU
CFLAGS=-c -g -Wall

all: $(EXE)

$(EXE): main.o getroot.o
	$(CC) $(LDFLAGS) main.o getroot.o -o $(EXE)

main.o: main.c
	$(CC) $(CFLAGS) main.c

getroot.o: getroot.c
	$(CC) $(CFLAGS) getroot.c

clean:
	rm -rf *.o $(EXE)
