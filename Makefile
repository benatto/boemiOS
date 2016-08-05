all:
	#$(source env.sh)
	i686-elf-as -o boot.o boot.s
	i686-elf-gcc -c main.c -o main.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o boemiOS -ffreestanding -O2 -nostdlib boot.o main.o -lgcc
test:
	qemu-system-i386 -kernel boemiOS
