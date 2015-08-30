#CC	= arm-linux-gnueabihf-gcc
CC = gcc
CFLAGS	= -O0 -std=gnu99 -g

objects	= rgba2bw

default: rgba2bw

.PHONY: default clean

rgba2bw: main.o rgba2bw_modified.o rgba2bw_origin.o imgio.o
	$(CC) -o $@ main.o rgba2bw_modified.o rgba2bw_origin.o imgio.o -lpng12

%.o: %.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(objects) *.o

qemu: rgba2bw_modified
	qemu-arm -L /usr/arm-linux-gnueabihf ./rgba2bw -lrt
