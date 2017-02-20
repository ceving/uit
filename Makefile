CC=gcc
CFLAGS=-g -Wall
EXE=uitsd

all: $(EXE)

clean:
	rm -f *.o $(EXE)

uitsd: uitsd.o daemonize.o terminate.o tcpserver.o message.o tcpsocket.o udprelay.o
