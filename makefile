compil:
	nasm bootloader/boot.asm -o bin/boot.bin
	nasm -felf kernel/start.asm -o bin/start.o
	gcc -c kernel/kernel.c -o bin/kernel.o
	ld -Ttext=0x9000 --oformat binary bin/start.o bin/kernel.o -o bin/kernel.sfs -e 0x0
copier:
	dd if=bin/boot.bin of=/dev/fd0
	dd if=bin/kernel.sfs seek=1 of=/dev/fd0
all:
	nasm bootloader/boot.asm -o bin/boot.bin
	nasm -felf kernel/start.asm -o bin/start.o
	gcc -c kernel/kernel.c -o bin/kernel.o
	ld -Ttext=0x9000 --oformat binary bin/start.o bin/kernel.o -o bin/kernel.sfs -e 0x0
	rm -f ./device/disk
	touch ./device/disk
	dd if=bin/boot.bin of=./device/disk
	dd if=bin/kernel.sfs seek=1 of=./device/disk
b:
	bochs -f ./bochsrc.txt
allb:
	nasm bootloader/boot.asm -o bin/boot.bin
	nasm -felf kernel/start.asm -o bin/start.o
	gcc -c kernel/kernel.c -o bin/kernel.o
	ld -Ttext=0x1000 --oformat binary bin/start.o bin/kernel.o -o bin/kernel.sfs -e 0x0
	dd if=bin/boot.bin of=/dev/fd0
	dd if=bin/kernel.sfs seek=1 of=/dev/fd0
	bochs -f ./bochsrc.txt
clean:
	rm bin/*
