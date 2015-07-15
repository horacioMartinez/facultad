#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
	int a = 0;
	int b = strlen(s) - 1;
	while (b - a > 0)
	{
		char aux = s[a];
		s[a] = s[b];
		s[b] = aux;

		a++;
		b--;
	}
}

int main(void)
{
	char s[] = "hola";
	reverse(s);
	printf("reverse recursivo: %s\n", s);
}

