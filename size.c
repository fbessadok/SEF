#include <stdio.h>
int main()
{
unsigned char *msg="chaine",*m;
*m="chaine";
printf("char %d\nshort %d\nint %d\nunsigned char %d\nunsigned short %d\nunsigned int %d",sizeof(char),sizeof(short), sizeof(int), sizeof(unsigned char), sizeof(unsigned short), sizeof(unsigned int));
printf("\nmsg:\n");
while(*msg!=0)
{
	printf("%c",*msg++);
}
printf("\nm:\n");
while(*m!=0)
{
	printf("%c",*m++);
}
printf("\n");
return 1;
} 
