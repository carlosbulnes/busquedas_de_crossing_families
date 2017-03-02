#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "geom.h"

int main(int argc, char *argv[]){
	
	if(argc < 2){
		printf("Se necesita el valor de n como argumento\n");
		return -1;
	}
	
	int n, otypes, bytes, npuntos, i, j, k, l, inicio, kotypes, nsegmentos, cont;
	int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, intersectan;
	char order_type[50], etiqueta;
	uint16_t a, b; 


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

	strcpy(order_type, "intersecting_families/K2/logK2-");
	//strcpy(order_type, "cierres_convexos-");
	strcat(order_type, argv[1]);
	strcat(order_type, "int");

	FILE *log = fopen(order_type, "w");
	
	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}

	npuntos = otypes*n;

	Punto *puntos = (Punto*)malloc(sizeof(Punto)*npuntos);
	Segmento *segmentos = (Segmento*)malloc(sizeof(Segmento)*nsegmentos);
	
	/*
	// Variables para conocer el cierre vonvexo
	point_t puntos_otype[n];
	point_t **hull;
	ssize_t hull_size;

  	hull = (point_t **)malloc(n*sizeof(point_t));

  	for(i = 0; i < n; i++){
    	hull[i] = (point_t *)malloc(sizeof(point_t));
  	}
	*/

  	// Lectura del archivo de la base de datos
	etiqueta = 'a';
	for(i = 0; i < npuntos;){
		fread(&a, bytes, 1, file);
		fread(&b, bytes, 1, file);

		puntos[i].etiqueta = etiqueta;
		puntos[i].x = a;
		puntos[i].y = b;

		etiqueta += 1;
		i++;
		if(i % n == 0) etiqueta = 'a';
	}
	fclose(file);

	printf("otype de inicio: "); scanf("%d", &inicio);
	printf("otypes a procesar: "); scanf("%d", &kotypes);

	l = (inicio - 1) * n;
	npuntos = (kotypes == 0) ? npuntos : (l + (kotypes * n));
	printf("iniciando desde otype: %d\n", (l/n)+1);

	//clock_t start = clock();
	// Recorre los order types
	for(; l < npuntos; l+=n){
		/*
		// Llena un arreglo con los n puntos actuales
		for(i = 0; i < n; i++){
			puntos_otype[i].x = puntos[l+i].x;
			puntos_otype[i].y = puntos[l+i].y;
			//puntos_otype[i].etiqueta = puntos[l+i].etiqueta;
		}

		// Calcula el cierre convexo
		convex_hull(puntos_otype, 8, &hull, &hull_size);

		fprintf(log, "%d\n", (int)(hull_size-1));
		
		continue;
		*/
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

		//printf("%d segmentos\n", k);

		// A partir de n = 8 buscar CF de tamaño 9
		cont = 0;
		
		for(i1 = 0; i1 < nsegmentos; i1++){
			for(i2 = i1+1; i2 < nsegmentos; i2++){
				intersectan = 1;
				intersectan &= interseccion(segmentos[i1], segmentos[i2]) || comparten_punto(segmentos[i1], segmentos[i2]);
				if(!intersectan) continue;
				for(i3 = i2+1; i3 < nsegmentos; i3++){
					intersectan = 1;
					intersectan &= interseccion(segmentos[i1], segmentos[i3]) || comparten_punto(segmentos[i1], segmentos[i3]);
					intersectan &= interseccion(segmentos[i2], segmentos[i3]) || comparten_punto(segmentos[i2], segmentos[i3]);
					if(!intersectan) continue;
					for(i4 = i3+1; i4 < nsegmentos; i4++){
						intersectan = 1;
						intersectan &= interseccion(segmentos[i1], segmentos[i4]) || comparten_punto(segmentos[i1], segmentos[i4]);
						intersectan &= interseccion(segmentos[i2], segmentos[i4]) || comparten_punto(segmentos[i2], segmentos[i4]);
						intersectan &= interseccion(segmentos[i3], segmentos[i4]) || comparten_punto(segmentos[i3], segmentos[i4]);
						if(!intersectan) continue;
						for(i5 = i4+1; i5 < nsegmentos; i5++){
							intersectan = 1;
							intersectan &= interseccion(segmentos[i1], segmentos[i5]) || comparten_punto(segmentos[i1], segmentos[i5]);
							intersectan &= interseccion(segmentos[i2], segmentos[i5]) || comparten_punto(segmentos[i2], segmentos[i5]);
							intersectan &= interseccion(segmentos[i3], segmentos[i5]) || comparten_punto(segmentos[i3], segmentos[i5]);
							intersectan &= interseccion(segmentos[i4], segmentos[i5]) || comparten_punto(segmentos[i4], segmentos[i5]);
							if(!intersectan) continue;
							for(i6 = i5+1; i6 < nsegmentos; i6++){
								intersectan = 1;
								intersectan &= interseccion(segmentos[i1], segmentos[i6]) || comparten_punto(segmentos[i1], segmentos[i6]);
								intersectan &= interseccion(segmentos[i2], segmentos[i6]) || comparten_punto(segmentos[i2], segmentos[i6]);
								intersectan &= interseccion(segmentos[i3], segmentos[i6]) || comparten_punto(segmentos[i3], segmentos[i6]);
								intersectan &= interseccion(segmentos[i4], segmentos[i6]) || comparten_punto(segmentos[i4], segmentos[i6]);
								intersectan &= interseccion(segmentos[i5], segmentos[i6]) || comparten_punto(segmentos[i5], segmentos[i6]);
								if(!intersectan) continue;
								for(i7 = i6+1; i7 < nsegmentos; i7++){
									intersectan = 1;
									intersectan &= interseccion(segmentos[i1], segmentos[i7]) || comparten_punto(segmentos[i1], segmentos[i7]);
									intersectan &= interseccion(segmentos[i2], segmentos[i7]) || comparten_punto(segmentos[i2], segmentos[i7]);
									intersectan &= interseccion(segmentos[i3], segmentos[i7]) || comparten_punto(segmentos[i3], segmentos[i7]);
									intersectan &= interseccion(segmentos[i4], segmentos[i7]) || comparten_punto(segmentos[i4], segmentos[i7]);
									intersectan &= interseccion(segmentos[i5], segmentos[i7]) || comparten_punto(segmentos[i5], segmentos[i7]);
									intersectan &= interseccion(segmentos[i6], segmentos[i7]) || comparten_punto(segmentos[i6], segmentos[i7]);
									if(!intersectan) continue;
									for(i8 = i7+1; i8 < nsegmentos; i8++){
										intersectan = 1;
										intersectan &= interseccion(segmentos[i1], segmentos[i8]) || comparten_punto(segmentos[i1], segmentos[i8]);
										intersectan &= interseccion(segmentos[i2], segmentos[i8]) || comparten_punto(segmentos[i2], segmentos[i8]);
										intersectan &= interseccion(segmentos[i3], segmentos[i8]) || comparten_punto(segmentos[i3], segmentos[i8]);
										intersectan &= interseccion(segmentos[i4], segmentos[i8]) || comparten_punto(segmentos[i4], segmentos[i8]);
										intersectan &= interseccion(segmentos[i5], segmentos[i8]) || comparten_punto(segmentos[i5], segmentos[i8]);
										intersectan &= interseccion(segmentos[i6], segmentos[i8]) || comparten_punto(segmentos[i6], segmentos[i8]);
										intersectan &= interseccion(segmentos[i7], segmentos[i8]) || comparten_punto(segmentos[i7], segmentos[i8]);
										if(!intersectan) continue;
										/*for(i9 = i8+1; i9 < nsegmentos; i9++){
											intersectan = 1;
											intersectan &= interseccion(segmentos[i1], segmentos[i9]) || comparten_punto(segmentos[i1], segmentos[i9]);
											intersectan &= interseccion(segmentos[i2], segmentos[i9]) || comparten_punto(segmentos[i2], segmentos[i9]);
											intersectan &= interseccion(segmentos[i3], segmentos[i9]) || comparten_punto(segmentos[i3], segmentos[i9]);
											intersectan &= interseccion(segmentos[i4], segmentos[i9]) || comparten_punto(segmentos[i4], segmentos[i9]);
											intersectan &= interseccion(segmentos[i5], segmentos[i9]) || comparten_punto(segmentos[i5], segmentos[i9]);
											intersectan &= interseccion(segmentos[i6], segmentos[i9]) || comparten_punto(segmentos[i6], segmentos[i9]);
											intersectan &= interseccion(segmentos[i7], segmentos[i9]) || comparten_punto(segmentos[i7], segmentos[i9]);
											intersectan &= interseccion(segmentos[i8], segmentos[i9]) || comparten_punto(segmentos[i8], segmentos[i9]);
											if(!intersectan) continue;
											for(i10 = i9+1; i10 < nsegmentos; i10++){
												intersectan = 1;
												intersectan &= interseccion(segmentos[i1], segmentos[i10]) || comparten_punto(segmentos[i1], segmentos[i10]);
												intersectan &= interseccion(segmentos[i2], segmentos[i10]) || comparten_punto(segmentos[i2], segmentos[i10]);
												intersectan &= interseccion(segmentos[i3], segmentos[i10]) || comparten_punto(segmentos[i3], segmentos[i10]);
												intersectan &= interseccion(segmentos[i4], segmentos[i10]) || comparten_punto(segmentos[i4], segmentos[i10]);
												intersectan &= interseccion(segmentos[i5], segmentos[i10]) || comparten_punto(segmentos[i5], segmentos[i10]);
												intersectan &= interseccion(segmentos[i6], segmentos[i10]) || comparten_punto(segmentos[i6], segmentos[i10]);
												intersectan &= interseccion(segmentos[i7], segmentos[i10]) || comparten_punto(segmentos[i7], segmentos[i10]);
												intersectan &= interseccion(segmentos[i8], segmentos[i10]) || comparten_punto(segmentos[i8], segmentos[i10]);
												intersectan &= interseccion(segmentos[i9], segmentos[i10]) || comparten_punto(segmentos[i9], segmentos[i10]);
												if(!intersectan) continue;*/
											//clock_t start = clock();
											//if(son_intersecting_familiy(segmentos[i1], segmentos[i2], segmentos[i3], segmentos[i4], 
											//	segmentos[i5], segmentos[i6], segmentos[i7], segmentos[i8], segmentos[i9])){
											//	fprintf(log, "%s%s%s%s%s%s%s%s%s ", 
											//		segmentos[i1].etiqueta, segmentos[i2].etiqueta, segmentos[i3].etiqueta, segmentos[i4].etiqueta, 
											//		segmentos[i5].etiqueta, segmentos[i6].etiqueta, segmentos[i7].etiqueta, segmentos[i8].etiqueta, segmentos[i9].etiqueta);
												cont++;
											//}
											//printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
											//return 0;
											//}
										//}
									}
								}
							}
						}
					}
				}
			}
		}

		fprintf(log, "%d: %d\n", (l/n)+1, cont);
		if(((l/n)+1) % 500000 == 0) printf("%d/%d\n", (l/n)+1, otypes);
		//printf("%d: %d\n", (l/n)+1, cont);
	}
	//printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
	/*
	for(l = (inicio - 1) * n; l < npuntos; l+=n){
		printf("%d: ", (l/n)+1);
		for(i = l; i < (l + n); i++){
			printf("(%d,%d) ", puntos[i].x, puntos[i].y);
		}
		printf("\n");
	}
	*/

	free(puntos);
	free(segmentos);
	fclose(log);
	return 0;
}
