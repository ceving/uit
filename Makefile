VERSION:=$(shell cat VERSION)

CC=gcc
CFLAGS=-g -Wall

SHARED=message.o daemonize.o terminate.o \
tcpsocket.o udpsocket.o relay.o

CLIENT=uitcd.o tcpclient.o udpserver.o

SERVER=uitsd.o tcpserver.o udpclient.o

SRC=$(CLIENT:.o=.c) $(SERVER:.o=.c) $(SHARED:.o=.c)

all: uitcd uitsd

clean:
	rm -f uitcd uitsd $(CLIENT) $(SERVER) $(SHARED)

dist: FILES
	tar --transform 's,^,uit-$(VERSION)/,' -T FILES -czf uit-$(VERSION).tar.gz

files: .gitignore FILES

uitcd: $(CLIENT) $(SHARED)

uitsd: $(SERVER) $(SHARED)

.gitignore: Makefile
	echo '*~' > $@
	echo '*.o' >> $@
	echo '.#*' >> $@
	echo '*.tar.gz' >> $@
	echo uitcd >> $@
	echo uitsd >> $@

FILES: Makefile
	echo $@ > $@
	echo LICENSE >> $@
	echo Makefile >> $@
	echo README.md >> $@
	echo VERSION >> $@
	echo $(SRC) | tr ' ' '\n' >> $@
