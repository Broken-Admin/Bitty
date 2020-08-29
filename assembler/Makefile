title := assembler
out := $(title).elf
in :=  $(title).c

.PHONY: all clean

all: $(out)

clean:
	rm -f *.bin *.elf

$(out): $(in)
	gcc -o $@ $^

clang: $(in)
	clang -o $(out) $^