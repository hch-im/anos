#################################################
#	Make kernel
#################################################
SRCS = $(wildcard *.c) $(wildcard */*.c) $(wildcard ../drivers/*/*.c)
HEADERS = $(wildcard include/*.h) $(wildcard ../drivers/*/*.h)
OBJS = ${SRCS:.c=.o}
CFLAGS = -m32

$(info srcs = $(SRCS))
$(info headers = $(HEADERS))
$(info objs = $(OBJS))

all: kernel.bin
	@echo "--------------------------------------"
	@echo "Successfully generate kernel.bin"
	@echo "--------------------------------------"

# link obj files to generate the kernel.
kernel.bin: kernel_entry.o ${OBJS}
	@echo "--------------------------------------"
	@echo "Generate kernel.bin"
	@echo "--------------------------------------"	
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	gcc ${CFLAGS} -ffreestanding -masm=intel -c $< -o $@	

# generate kernel entry
kernel_entry.o: kernel_entry.asm
	@echo "--------------------------------------"
	@echo "Generate kernel entry"
	@echo "--------------------------------------"	
	nasm $< -f elf -o $@

clean:
	@echo "--------------------------------------"
	@echo "Clean kernel subdirectory"
	@echo "--------------------------------------"
	rm *.o
	rm *.bin
	rm ../drivers/*/*.o
	
.PHONY: all kernel.bin clean	