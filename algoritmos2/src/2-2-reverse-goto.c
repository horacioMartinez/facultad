#include <stdio.h>
#include <string.h>

void reverse(char *s, int a, int b)
{
	char aux;
	START:
	if (b - a <= 0)
		return;
	aux = s[a];
	s[a] = s[b];
	s[b] = aux;
	a++;
	b--;
	goto START;
}

int main(void)
{
	char s[] = "hola";
	reverse(s, 0, strlen(s) - 1);
	printf("reverse recursivo: %s\n", s);
}
