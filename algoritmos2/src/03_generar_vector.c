#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("Uso: %s <cantidad>\n", argv[0]);
		return 1;
	}

	int n = atoi(argv[1]);
	printf("%d\n", n);

	srand(time(NULL));

	for(int i = 0; i < n; i++)
		printf("%d\n", rand() % MAX);

	return 0;
}
