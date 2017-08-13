#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "geom.h"

typedef struct k2{
	Segmento s1;
	Segmento s2;
}s2K2;

int main(int argc, char *argv[]){
	
	int n, otypes, c = 1, i, j, k, l, m, bytes, nsegmentos, npuntos, inicio, kotypes;
	int crossings = 0, ncrossings = 0, siempre_existe = 1, n2k2;
	char order_type[50], etiqueta, nchar[3];

	do{
		printf("n: "); scanf("%d", &n);
	}while(n < 3 || n > 10);

	switch(n){
		case 3: strcpy(order_type, "order_types/otypes03.b08"); otypes = 1; bytes = 1; nsegmentos = 3; break;
		case 4: strcpy(order_type, "order_types/otypes04.b08"); otypes = 2; bytes = 1; nsegmentos = 6; break;
		case 5: strcpy(order_type, "order_types/otypes05.b08"); otypes = 3; bytes = 1; nsegmentos = 10; break;
		case 6: strcpy(order_type, "order_types/otypes06.b08"); otypes = 16; bytes = 1; nsegmentos = 15; break;
		case 7: strcpy(order_type, "order_types/otypes07.b08"); otypes = 135; bytes = 1; nsegmentos = 21; break;
		case 8: strcpy(order_type, "order_types/otypes08.b08"); otypes = 3315; bytes = 1; nsegmentos = 28; n2k2 = 378; break;
		case 9: strcpy(order_type, "order_types/otypes09.b16"); otypes = 158817; bytes = 2; nsegmentos = 36; n2k2 = 630; break;
		case 10: strcpy(order_type, "order_types/otypes10.b16"); otypes = 14309547; bytes = 2; nsegmentos = 45; n2k2 = 990; break;
	}

	FILE *file = fopen(order_type, "rb");
	strcpy(order_type, "crossing_families/log2k2-");
	sprintf(nchar, "%d", n);
	strcat(order_type, nchar);
	
	FILE *log = fopen(order_type, "r");
	if(log == NULL){
		log = fopen(order_type, "w");
	}
	else{
		fclose(log);
		log = fopen(order_type, "a");		
	}

	uint16_t a, b;
	npuntos = otypes*n;

	Punto *puntos = (Punto*)malloc(sizeof(Punto)*npuntos);
	Segmento *segmentos = (Segmento*)malloc(sizeof(Segmento)*nsegmentos);
	s2K2 *a2k2 = (s2K2*)malloc(sizeof(s2K2)*n2k2);
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
				segmentos[k].etiqueta[3] = '\0';
				k++;
			}	
		}

		// Construye todas las 2K2 con los n en 2 segmentos
		for(i = 0, k = 0; i < nsegmentos; i++){
			for(j = i+1; j < nsegmentos; j++){
				if(!comparten_punto(segmentos[i], segmentos[j])){
					a2k2[k].s1 = segmentos[i];
					a2k2[k].s2 = segmentos[j];
					//fprintf(log, "%s%s\n", a2k2[k].s1.etiqueta, a2k2[k].s2.etiqueta);
					k++;
				}
			}
		}

		n2k2 = k;
		//double prom = 0, con = 0;
		crossings = 0;
		for(i = 0; i < n2k2; i++){
			for(j = i+1; j < n2k2; j++){
				//clock_t start = clock();
				if(!comparten_punto(a2k2[i].s1, a2k2[j].s1) && !comparten_punto(a2k2[i].s1, a2k2[j].s2) && !comparten_punto(a2k2[i].s2, a2k2[j].s1) && !comparten_punto(a2k2[i].s2, a2k2[j].s2)){
					if(interseccion(a2k2[i].s1, a2k2[j].s1) || interseccion(a2k2[i].s1, a2k2[j].s2) || interseccion(a2k2[i].s2, a2k2[j].s1) || interseccion(a2k2[i].s2, a2k2[j].s2)){
						crossings++;
						//fprintf(log, "%s%s", a2k2[i].s1.etiqueta, a2k2[i].s2.etiqueta);
						//fprintf(log, "%s%s\n", a2k2[j].s1.etiqueta, a2k2[j].s2.etiqueta);
					}
				}
				/*
				clock_t stop = clock();
				double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    			prom += elapsed;
    			con += 1.0;
    			*/		
			}
		}
		//printf("cont: %f\n", con);
		//printf("tiempo promedio: %.12f s\n", (prom/con)/1000.0); return 0;
		ncrossings += crossings;
		fprintf(log, "%d: %d\n", (l/n)+1, crossings);
		//printf("%d: %d\n", (l/n)+1, crossings);
		//if(((l/n)+1) % 500000 == 0) printf("%d/%d\n", (l/n)+1, otypes);
	}

	printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
	printf("\nTotal de Crossing Families: %d\n", ncrossings);

	return 0;
}