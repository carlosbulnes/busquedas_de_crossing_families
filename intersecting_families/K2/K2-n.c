#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "k2.h"

int main(int argc, char *argv[]){
	
	/*
	if(argc < 2){
		printf("Se necesita el valor de n como argumento\n");
		return -1;
	}
	*/

	int n, otypes, bytes, npuntos, i, j, k, l, inicio, kotypes, nsegmentos, cont, err;
	char order_type[50], etiqueta, cadena[3];
	uint16_t a, b; 

	//n = atoi(argv[1]);
	printf("valor de n: "); err = scanf("%d", &n);

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

	strcpy(order_type, "intersecting_families/K2/logK2-");
	sprintf(cadena, "%d", n);
	strcat(order_type, cadena);
	strcat(order_type, "s");

	FILE *log = fopen(order_type, "w");
	
	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}

	npuntos = otypes*n;

	Punto *puntos = (Punto*)malloc(sizeof(Punto)*npuntos);
	Segmento *segmentos = (Segmento*)malloc(sizeof(Segmento)*nsegmentos);

  	// Lectura del archivo de la base de datos
	etiqueta = '1';
	for(i = 0; i < npuntos;){
		err = fread(&a, bytes, 1, file);
		err = fread(&b, bytes, 1, file);

		puntos[i].etiqueta = etiqueta;
		puntos[i].x = a;
		puntos[i].y = b;

		etiqueta += 1;
		i++;
		if(i % n == 0) etiqueta = '1';
	}
	fclose(file);

	printf("otype de inicio: "); err = scanf("%d", &inicio);
	printf("otypes a procesar: "); err = scanf("%d", &kotypes);

	l = (inicio - 1) * n;
	npuntos = (kotypes == 0) ? npuntos : (l + (kotypes * n));
	printf("iniciando desde otype: %d\n", (l/n)+1);

	clock_t start = clock();
	// Recorre los order types
	for(; l < npuntos; l+=n){
		// Construye los n en 2 segmentos para el l order type
		for(i = l, k = 0; i < (l+n); i++){
			for(j = i+1; j < (l+n); j++){
				segmentos[k].a = puntos[i];
				segmentos[k].b = puntos[j];
				segmentos[k].etiqueta[0] = puntos[i].etiqueta;
				segmentos[k].etiqueta[1] = puntos[j].etiqueta;
				segmentos[k].etiqueta[2] = '\0';
				k++;
			}	
		}

		switch(n){
			case 6:
				cont = n6(segmentos, nsegmentos, log);
				fprintf(log, "%d: %d\n", (l/n)+1, cont);
				//if(((l/n)+1) % 500000 == 0) printf("%d/%d\n", (l/n)+1, otypes);
				break;			
			case 8:
				cont = n8(segmentos, nsegmentos, log);
				fprintf(log, "%d: %d\n", (l/n)+1, cont);
				if(((l/n)+1) % 500000 == 0) printf("%d/%d\n", (l/n)+1, otypes);
				break;
			case 9:
				cont = n9(segmentos, nsegmentos, log);
				fprintf(log, "%d: %d\n", (l/n)+1, cont);
				if(((l/n)+1) % 50000 == 0) printf("%d/%d\n", (l/n)+1, otypes);
				break;
			case 10:
				cont = n10(segmentos, nsegmentos, log);
				fprintf(log, "%d: %d\n", (l/n)+1, cont);

				break;
		}
	}
	printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);

	free(puntos);
	free(segmentos);
	fclose(log);
	return 0;
}
