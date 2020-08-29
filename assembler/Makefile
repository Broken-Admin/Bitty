all: assembler.bin

clean:
	rm *.bin *.out

assembler.bin: assembler.c
	gcc -o $@ $^

clang: assembler.c
	clang -o assembler.bin $^