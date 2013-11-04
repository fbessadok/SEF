#include "affichage.h"
//#include "gdt.h"
void sef_main()
{
	maj_mode(0);
	effacer();
	ecrirec('s');
	ecrirerc("Salem");
	ecrirerc("Salem");
	ecrireok("Salem");
	ecrireok("Chargement du noyau de SEF");
	ecrireok("Lancement du noyau de SEF");
//	init_gdt();
	ecrire("Bon c'est tout pour l'instant\nMais la prochaine fois ce sera mieux");
	ecrire("\nAllez saluuuuuuuuuuut ;-) <:'(\n");
	ecrireok("");
	while(1);
}
