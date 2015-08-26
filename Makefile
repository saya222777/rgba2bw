CC	= arm-linux-gnueabihf-gcc
CFLAGS	= -O0 

objects	= rgba2bw_modified.o

default: rgba2bw_modified

.PHONY: default clean

rgba2bw_modified: $(objects)
	$(CC) -o $@ $^

rgba2bw_modified.o: rgba2bw_modified.c

%.o: %.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(objects) rgba2bw_modified

qemu: rgba2bw_modified
	qemu-arm -L /usr/arm-linux-gnueabihf ./rgba2bw_modified -lrt
