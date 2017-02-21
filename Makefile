OS:=$(shell uname -s)
VERSION:=$(shell cat VERSION)
PACKAGE:=uit

CC=gcc
CFLAGS=-g -Wall
ifeq ($(OS),SunOS)
LDLIBS=-lsocket -lnsl
endif

SHARED=message.o daemonize.o terminate.o \
tcpsocket.o udpsocket.o relay.o

CLIENT=uitcd.o tcpclient.o udpserver.o
SERVER=uitsd.o tcpserver.o udpclient.o

SRC=uit.h $(CLIENT:.o=.c) $(SERVER:.o=.c) $(SHARED:.o=.c)
TGZ=$(PACKAGE)-$(VERSION).tar.gz

.PHONY: all clean dist files

all: uitcd uitsd

clean:
	rm -f uitcd uitsd $(CLIENT) $(SERVER) $(SHARED)

dist: FILES
	tar --transform 's,^,$(PACKAGE)-$(VERSION)/,' -T FILES -czf $(TGZ)

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
