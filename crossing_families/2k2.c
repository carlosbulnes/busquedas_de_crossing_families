#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geom.h"


int main(int argc, char *argv[]){
	
	int n, otypes, c = 1, i, j, k, l, m, bytes, nsegmentos, npuntos, inicio, kotypes;
	int crossings = 0, ncrossings = 0, siempre_existe = 1, bandera;
	char order_type[50], etiqueta;

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
	strcpy(order_type, "crossing_families/log2k2-");
	strcat(order_type, argv[1]);
	FILE *log = fopen(order_type, "w");
	uint16_t a, b;
	npuntos = otypes*n;

	Punto *puntos = (Punto*)malloc(sizeof(Punto)*npuntos);
	Segmento *segmentos = (Segmento*)malloc(sizeof(Segmento)*nsegmentos);
	Segmento srojos[2], sazules[2];


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

	printf("otype de inicio: "); scanf("%d", &inicio);
	printf("otypes a procesar: "); scanf("%d", &kotypes);

	l = (inicio - 1) * n;
	npuntos = (kotypes == 0) ? npuntos : (l + (kotypes * n));
	printf("iniciando desde otype: %d\n", (l/n)+1); //return 0; 
	// Recorre los order types
	for(; l < npuntos; l+=n){
		// Construye los n en 2 segmentos para el l order type
		for(i = l, k = 0; i < (l+n); i++){
			for(j = i+1; j < (l+n); j++){
				segmentos[k].a = puntos[i];
				segmentos[k].b = puntos[j];
				segmentos[k].etiqueta[0] = puntos[i].etiqueta;
				segmentos[k].etiqueta[1] = puntos[j].etiqueta;
				k++;
			}	
		}

		crossings = 0;

		/*
		// Imprime los puntos del order type
		printf("--------------------otype %d-----------------------\n", (l/n)+1);
		for(i = l; i < (l+n); i++){
			printf("%c: (%d, %d) ", puntos[i].etiqueta, puntos[i].x, puntos[i].y);	
		}
		printf("\n");
		*/
		//printf("--------------------otype %d-----------------------\n", (l/n)+1);
		for(i = 0; i < nsegmentos; i++){
			srojos[0] = segmentos[i];
			
			// Busca la pareja del segmento rojo
			for(j = i; j < nsegmentos; j++){
				if(!comparten_punto(srojos[0],segmentos[j])){
					// Encuentra la pareja roja
					srojos[1] = segmentos[j];

					// Busca los segmentos azules
					for(k = i; k < nsegmentos; k++){
						if(strcmp(segmentos[k].etiqueta, srojos[0].etiqueta) == 0 || strcmp(segmentos[k].etiqueta, srojos[1].etiqueta) == 0
							|| comparten_punto(segmentos[k], srojos[0]) || comparten_punto(segmentos[k], srojos[1])){
							continue;
						}
						
						// Determina el primer segmento azul
						sazules[0] = segmentos[k];
						
						// Busca pareja del segmento azul
						for(m = k; m < nsegmentos; m++){
							if(!comparten_punto(sazules[0], segmentos[m]) && !comparten_punto(segmentos[m], srojos[0]) && !comparten_punto(segmentos[m], srojos[1])
								&& strcmp(segmentos[m].etiqueta, srojos[0].etiqueta) != 0 && strcmp(segmentos[m].etiqueta, srojos[1].etiqueta) != 0){
								// Pareja azul encontrada
								sazules[1] = segmentos[m];

								// Verifica si algun segmento rojo intersecta a algun segmento azul
								if(interseccion(srojos[0], sazules[0]) || interseccion(srojos[0], sazules[1])
									|| interseccion(srojos[1], sazules[0]) || interseccion(srojos[1], sazules[1])){
									
									crossings++;
									
									//fprintf(log, "Rojos: %s y %s, ", srojos[0].etiqueta, srojos[1].etiqueta);
									fprintf(log, "%c%c%c%c", srojos[0].etiqueta[0], srojos[0].etiqueta[1], srojos[1].etiqueta[0], srojos[1].etiqueta[1]);
									fprintf(log, "%c%c%c%c\n", sazules[0].etiqueta[0], sazules[0].etiqueta[1], sazules[1].etiqueta[0], sazules[1].etiqueta[1]);
									
									//fprintf(log, "Azules: %s y %s\n", sazules[0].etiqueta, sazules[1].etiqueta);
								}
								/*else{
									printf("Rojos: %s y %s, ", srojos[0].etiqueta, srojos[1].etiqueta);
									
									printf("Azules: %s y %s no son CF\n", sazules[0].etiqueta, sazules[1].etiqueta);

									getchar();
									getchar();
								}*/
							}
						}
					}
				}
			}
		}

		ncrossings += crossings;
		fprintf(log, "%d: %d\n", (l/n)+1, crossings);
		if(((l/n)+1) % 500000 == 0) printf("%d/%d\n", (l/n)+1, otypes);
	}

	printf("\nTotal de Crossing Families: %d\n", ncrossings);

	return 0;
}