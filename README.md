# Welcome to SEF

SEF means *Système d'Exploitation de Firas* (Firas Operating System) and is a small project that I worked on when I was 19 yo (somewhere around 2004-2005). Unfortunately I haven't found the keyboard and screen drivers that I wrote, I also haven't found the second version of the memory managment which was slightly better than this one at that time.

SEF is composed of a kernel and a bootloader. The kernel contains programs that can manage the memory and print strings on the screen.

Comments in the files and many of the functions names are in french.

The file *scenario* contains a very small description of how SEF works.

* `make compil` : compiles the kernel and the bootloader.
* `make copier` : copy the binary files to a floppy disk mounted on /dev/fd0
* `make b` : launch SEF in a bochs instance
