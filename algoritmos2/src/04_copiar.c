#include <stdio.h>

int main(int argc, char *argv[]) {

	if(argc != 3) {
		fprintf(stderr, "Uso: %s <origen> <destino>\n", argv[0]);
		return 1;
	}

	FILE *fi, *fo;

	if((fi = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "No pudo abrirse \"%s\"!\n", argv[1]);
		return 1;
	}

	if((fo = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "No pudo abrirse \"%s\"!\n", argv[2]);

		fclose(fi);
		return 1;
	}

	int c;
	while((c = fgetc(fi)) != EOF)
		fputc(c, fo);

	fclose(fi);

	if(fclose(fo) == EOF) {
		fprintf(stderr, "Hubo algún error al escribir \"%s\"!\n", argv[2]);
		return 1;
	}

	return 0;
}
