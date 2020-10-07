.PHONY: all clean assembler virtual-machine newline

all: assembler newline virtual-machine

clean:
	@echo "Cleaning \"assembler\""
	@cd assembler && make clean && cd ..
	@cd ..
	@make newline
	@echo "Cleaning \"virtual-machine\""
	@cd virtual-machine && make clean && cd ..

assembler:
	@echo "Making \"assembler\""
	@cd assembler && make && cd ..

virtual-machine:
	@echo "Making \"vitual-machine\""
	@cd virtual-machine && make && cd ..

newline:
	@echo