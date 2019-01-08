CC=gcc
CFLAGS=-I.
PREFIX=/usr/local

all: main.o
	$(CC) -o main main.o -lcurl

.PHONY: clean
clean:
	rm main main.o

.PHONY: install
install: main
	mkdir -p ${PREFIX}/bin
	cp $< ${PREFIX}/bin/xmgt


.PHONY: uninstall
uninstall:
	rm -f $< ${PREFIX}/bin/xmgt
