#################################################
#	Make kernel
#################################################
SRCS = $(wildcard *.c) $(wildcard */*.c)
HEADERS = $(wildcard include/*.h)
OBJS = ${SRCS:.c=.o}

#$(info srcs = $(SRCS))
#$(info headers = $(HEADERS))
#$(info objs = $(OBJS))

all: kernel.bin
	@echo "--------------------------------------"
	@echo "Successfully generate kernel.bin"
	@echo "--------------------------------------"

# link obj files to generate the kernel.
kernel.bin: kernel_entry.o ${OBJS}
	@echo "--------------------------------------"
	@echo "Generate kernel.bin"
	@echo "--------------------------------------"	
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@	

# generate kernel entry
kernel_entry.o: kernel_entry.asm
	@echo "--------------------------------------"
	@echo "Generate kernel entry"
	@echo "--------------------------------------"	
	nasm $< -f elf64 -o $@

clean:
	@echo "--------------------------------------"
	@echo "Clean kernel subdirectory"
	@echo "--------------------------------------"
	rm *.o
	rm *.bin

.PHONY: all kernel.bin clean	