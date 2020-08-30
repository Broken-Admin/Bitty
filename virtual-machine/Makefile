CC := gcc
out := bitty.elf

.PHONY: all clean

all: $(out)

%.o: %.c
	$(CC) $(CFLAGS) -c $@

$(out): main.c instructions.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o *.elf