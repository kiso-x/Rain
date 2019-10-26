# define the compiler
CC      = g++

# path(s) to include files
CFLAGS  = -I.

# libraries to link
LDFLAGS = -ljack -llo -lsndfile

SRCS = main.cpp rain.cpp oscman.cpp singlesample.cpp grainplayer.cpp triangularwindow.cpp Biquad.cpp
DEPS = rain.h oscman.h singlesample.h grainplayer.h triangularwindow.h Biquad.h

all: rain

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rain: main.o rain.o oscman.o singlesample.o grainplayer.o triangularwindow.o Biquad.o
	$(CC) -o rain main.o rain.o oscman.o singlesample.o grainplayer.o triangularwindow.o Biquad.o $(LDFLAGS)

clean:
	rm *.o rain
