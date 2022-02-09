CFLAGS= -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -Wall -Wextra -Werror -m32 -std=gnu99
CC=gcc
ASMCOMP=nasm
ASMFLAGS= -f elf32
CSRCS= $(wildcard srcs/*.c)
COBJS= $(CSRCS:.c=.o)
CINC= inc
ASMSRCS = asm/*.asm
ASMOBJS = $(ASMSRCS:.asm=.o)
NAME = kernel

all: $(COBJS)
	$(ASMCOMP) $(ASMFLAGS) $(ASMSRCS)
	ld -m elf_i386 -T linker.ld -o kernel $(ASMOBJS) $(COBJS) 

%.o: %.c
	$(CC) $(CFLAGS) -I./inc -c $< -o $@

clean:
	rm -f $(COBJS) $(ASMOBJS)

fclean: clean
	rm -f $(NAME)
re: fclean all
