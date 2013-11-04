void copie_mem(void *src, void *dest, int n)
{
	char *s,*d;
	int i;
	s=(char *)src;
	d=(char *)dest;
	for(i=0;i<n;i++)
	*(d+i)=*(s+i);
} 
