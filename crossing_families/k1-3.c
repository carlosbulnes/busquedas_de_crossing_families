#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geom.h"

int main(int argc, char *argv[]){
	int n, i, l, npuntos, nsegmentos, otypes, bytes;
	char order_type[50], etiqueta;
	Punto apice;
	uint16_t a, b;

	if(argc < 2){
		printf("Se necesita el valor de n como argumento\n");
		return -1;
	}
	
	n = atoi(argv[1]);

	switch(n){
		case 3: strcpy(order_type, "order_types/otypes03.b08"); otypes = 1; bytes = 1; nsegmentos = 3; break;
		case 4: strcpy(order_type, "order_types/otypes04.b08"); otypes = 2; bytes = 1; nsegmentos = 6; break;
		case 5: strcpy(order_type, "order_types/otypes05.b08"); otypes = 3; bytes = 1; nsegmentos = 10; break;
		case 6: strcpy(order_type, "order_types/otypes06.b08"); otypes = 16; bytes = 1; nsegmentos = 15; break;
		case 7: strcpy(order_type, "order_types/otypes07.b08"); otypes = 135; bytes = 1; nsegmentos = 21; break;
		case 8: strcpy(order_type, "order_types/otypes08.b08"); otypes = 3315; bytes = 1; nsegmentos = 28; break;
		case 9: strcpy(order_type, "order_types/otypes09.b16"); otypes = 158817; bytes = 2; nsegmentos = 36; break;
		case 10: strcpy(order_type, "order_types/otypes10.b16"); otypes = 14309547; bytes = 2; nsegmentos = 45; break;
	}

	FILE *file = fopen(order_type, "rb");

	strcpy(order_type, "crossing_families/logk1-3-");
	strcat(order_type, argv[1]);

	FILE *log = fopen(order_type, "w");
	
	npuntos = otypes*n;

	Punto *puntos = (Punto*)malloc(sizeof(Punto)*npuntos);

	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}

	i = 0;
	etiqueta = 'a';
	while(!feof(file)){

		fread(&a, bytes, 1, file);
		fread(&b, bytes, 1, file);

		puntos[i].etiqueta = etiqueta;
		puntos[i].x = a;
		puntos[i].y = b;

		etiqueta += 1;
		i++;
		if(i % n == 0) etiqueta = 'a';
	}

	// Recorre los order types
	for(l = 0; l < npuntos; l+=n){
		
		/*
		// Imprime los puntos del order type
		printf("--------------------otype %d-----------------------\n", (l/n)+1);
		for(i = l; i < (l+n); i++){
			printf("%c: (%d, %d) ", puntos[i].etiqueta, puntos[i].x, puntos[i].y);	
		}
		printf("\n");
		*/

		// Recorre los n puntos del order type
		for(i = 0; i < n; i++){
			// Designa al punto i como el apice
			apice = puntos[l+i];

			//printf("apice %c: (%d, %d)\n", apice.etiqueta, apice.x, apice.y);

		}

	}
	return 0;
}