#ifndef AFFICHAGE_H
#define AFFICHAGE_H

void ecrirec(unsigned char);
void ecrire(unsigned char *);
void ecrirerc(unsigned char *);
void ecrireok(unsigned char *);
void effacer(void);
void glisser(void);
void maj_mode(int);

unsigned char *memvid=(unsigned char*) 0xB8000;
unsigned int i=0;
unsigned int atr=0x0B;

void ecrirec(unsigned char c)
{
	memvid[i++]=(unsigned char) c;
	memvid[i++]=(unsigned char) atr;
}

void ecrire(unsigned char *msg)
{
	unsigned short ind=0,ligne;
	while(msg[ind]!=0)
	{
		if(i==4000)
		{
			glisser();
		}
		if(msg[ind]=='\n')
		{
			for(ligne=0;ligne*160<i;ligne++);
			i=ligne*160;
			ind++;
		}
		else
		{
			memvid[i++]=(unsigned char) msg[ind++];
			memvid[i++]=(unsigned char) atr;
		}
	}
}

void ecrirerc(unsigned char *msg)
{
	unsigned short ind=0,ligne;
	while(msg[ind]!=0)
	{
		if(i==4000)
		{
			glisser();
		}
		if(msg[ind]=='\n')
		{
			for(ligne=0;ligne*160<i;ligne++);
			i=ligne*160;
			ind++;
		}
		else
		{
			memvid[i++]=(unsigned char) msg[ind++];
			memvid[i++]=(unsigned char) atr;
		}
	}
	for(ligne=0;ligne*160<i;ligne++);
	i=ligne*160;
}

void ecrireok(unsigned char *msg)
{
	int pts_restants=60,pts_a_ecrire;
	while(*msg!=0)
	{
		memvid[i++]=(unsigned char) *msg++;
		memvid[i++]=(unsigned char) atr;
		pts_restants--;
	}
	for(pts_a_ecrire=0;pts_a_ecrire<pts_restants;pts_a_ecrire++)
	ecrirec('.');
	memvid[i++]=(unsigned char) '[';
	memvid[i++]=(unsigned char) atr;
	memvid[i++]=(unsigned char) 'O';
	memvid[i++]=(unsigned char) 0x0F;
	memvid[i++]=(unsigned char) 'K';
	memvid[i++]=(unsigned char) 0x0F;
	memvid[i++]=(unsigned char) ']';
	memvid[i++]=(unsigned char) atr;
	ecrire("\n");
}

void effacer(void)
{
	int j=0;
	while(j<(160*25))
	{
		memvid[j++]=(unsigned char) 0;
		memvid[j++]=(unsigned char) atr;
	}
}

void glisser(void)
{
	int a=0,b=160;
	unsigned short ligne;
	for(a=0;a<80*24*2;b++,a++)
	{
		memvid[a]=memvid[b];
		if(b%2==0)memvid[b]=0;
	}
	if(i<0)
		i=0;
	else
		for(ligne=0;ligne*160<i;ligne++);
		i=ligne;
}

void maj_mode(int mode)
{
	if(mode==0)
		atr=0x0B;
	else
		atr=0x2B;
}
#endif
