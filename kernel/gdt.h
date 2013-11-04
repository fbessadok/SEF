#define GDTBASE 0x800	/*adresse physique de la gdt*/
#define GDTTAILLE 0xFF	/*nbr max de descripteur*/
#include "types.h"
#include "mem.h"

typedef struct {	/*descripteur de segment*/
	u16 lim0_15;
	u16 base0_15;
	u8 base16_23;
	u8 acces;
	u8 lim16_19 : 4; /*seulement 4 bits*/
	u8 autre : 4;
	u8 base24_31;
} descgdt __attribute__ ((packed));

/*regstre gdtr*/
struct gdtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));

struct gdtr kgdtr;

/*table de gdt*/
descgdt kgdt[GDTTAILLE]={0,0,0,0,0,0,0};

/* nbr de descripteurs et aussi pointeur sur un descripteur vide*/
unsigned int nbrdesc = 1;

void init_gdt_abs(u32 base, u32 limite, u8 acces, u8 autre, descgdt *ptr)
{
	ptr->lim0_15 = (limite & 0xffff);
	ptr->base0_15 = (base & 0xffff);
	ptr->base16_23 = (base & 0xff0000)>>16;
	ptr->acces = acces;
	ptr->lim16_19 = (limite & 0xf0000)>>16;
	ptr->autre = autre;
	ptr->base24_31 = (base & 0xff00000)>>24;
}

void init_gdt_code(u32 base, u32 limite, descgdt *ptr)
{
	init_gdt_abs(base, limite, 0x93, 0x0D, ptr);
}

void init_gdt_donnee(u32 base, u32 limite, descgdt *ptr)
{
	init_gdt_abs(base, limite, 0x9B, 0x0D, ptr);
}

void ajout_desc(descgdt desc)
{
	kgdt[nbrdesc]=desc;
	nbrdesc++;
}

void init_gdt(void)
{
	descgdt code, donnee, pile;
	init_gdt_code(0, 0xFFFFF, &code);
	init_gdt_donnee(0, 0xFFFFF, &donnee);
	init_gdt_abs(0, 0x10, 0x97, 0x0D, &pile);
	ajout_desc(code);
	ajout_desc(donnee);
	ajout_desc(pile);

	kgdtr.limite=GDTTAILLE*8;	/*0xFF nbr max de desc et *8 en octets*/
	kgdtr.base=GDTBASE;

	copie_mem(kgdt, kgdtr.base, kgdtr.limite);

	asm("lgdtl (kgdtr)");
	asm("	movw $0x10, %ax	\n \
		movw %ax, %ds	\n \
		movw %ax, %es	\n \
		movw %ax, %fs	\n \
		movw %ax, %gs	\n \
		movw $0x18, %ax	\n \
		movw %ax, %ss	\n \
		movl $0x1FFFF, %esp	\n \
		nop	\n \
		nop	\n \
		ljmp $0x08,$next	\n \
		next:	\n");

	ecrire("Nouvelle GDT mise au point");
} 
