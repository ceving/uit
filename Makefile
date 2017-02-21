CC=gcc
CFLAGS=-g -Wall

SHARED=message.o daemonize.o terminate.o \
tcpsocket.o udpsocket.o relay.o

CLIENT=uitcd.o tcpclient.o udpserver.o

SERVER=uitsd.o tcpserver.o udpclient.o

all: .gitignore uitcd uitsd

clean:
	rm -f uitcd uitsd $(CLIENT) $(SERVER) $(SHARED)

uitcd: $(CLIENT) $(SHARED)

uitsd: $(SERVER) $(SHARED)

.gitignore: Makefile
	echo '*~' > $@
	echo '*.o' >> $@
	echo uitcd >> $@
	echo uitsd >> $@
