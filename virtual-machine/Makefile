CC := gcc
out := bitty.elf

.PHONY: all clang clean

all: $(out)

%.o: %.c
	$(CC) $(CFLAGS) -c $@

$(out): main.c instructions.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clang: main.c instructions.c
	clang -o $(out) $^

clean:
	rm -f *.o *.elf