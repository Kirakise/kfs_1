CFLAGS= -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -Wall -Wextra -Werror -m32 -std=gnu99
CC=gcc
ASMCOMP=nasm
ASMFLAGS= -f elf32
CSRCS= $(wildcard srcs/*.c)
COBJS= $(CSRCS:.c=.o)
CINC= inc
ASMSRCS = asm/*.asm
ASMOBJS = $(ASMSRCS:.asm=.o)
NAME = kernel
ISO = kfs_1.iso

all: $(ISO)

$(ISO): $(COBJS)
	$(ASMCOMP) $(ASMFLAGS) $(ASMSRCS)
	ld -m elf_i386 -T linker.ld -o kernel $(ASMOBJS) $(COBJS) 
	grub-file --is-x86-multiboot $(NAME)
	mkdir -p isodir/boot/grub
	cp $(NAME) isodir/boot/kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) isodir

%.o: %.c
	$(CC) $(CFLAGS) -I./inc -c $< -o $@

clean:
	rm -f $(COBJS) $(ASMOBJS)
	rm -rf isodir

fclean: clean
	rm -f $(NAME)
	rm -f $(ISO)
re: fclean all

run:
	qemu-system-x86_64 -cdrom $(ISO)
