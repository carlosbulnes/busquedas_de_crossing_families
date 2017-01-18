#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geom.h"

typedef struct k13{
	Segmento s1;
	Segmento s2;
	Segmento s3;
}K1_3;


int main(int argc, char *argv[]){
	int n, i, j, k, l, m, o, p, npuntos, otypes, bytes, nk1_3;
	char order_type[50], etiqueta;
	Punto apice, apice2;
	K1_3 k1_3;
	Segmento segmento;
	uint16_t a, b;

	if(argc < 2){
		printf("Se necesita el valor de n como argumento\n");
		return -1;
	}
	
	n = atoi(argv[1]);

	switch(n){
		case 3: strcpy(order_type, "order_types/otypes03.b08"); otypes = 1; bytes = 1; break;
		case 4: strcpy(order_type, "order_types/otypes04.b08"); otypes = 2; bytes = 1; break;
		case 5: strcpy(order_type, "order_types/otypes05.b08"); otypes = 3; bytes = 1; break;
		case 6: strcpy(order_type, "order_types/otypes06.b08"); otypes = 16; bytes = 1; break;
		case 7: strcpy(order_type, "order_types/otypes07.b08"); otypes = 135; bytes = 1; break;
		case 8: strcpy(order_type, "order_types/otypes08.b08"); otypes = 3315; bytes = 1; break;
		case 9: strcpy(order_type, "order_types/otypes09.b16"); otypes = 158817; bytes = 2; break;
		case 10: strcpy(order_type, "order_types/otypes10.b16"); otypes = 14309547; bytes = 2; break;
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
		
		// Recorre los n puntos del order type
		for(i = 0, nk1_3 = 0; i < n; i++){
			// Designa al punto i como el apice
			apice = puntos[l+i];

			k1_3.s1.etiqueta[0] = apice.etiqueta;
			k1_3.s1.etiqueta[2] = '\0';
			k1_3.s1.a = apice;
			
			k1_3.s2.etiqueta[0] = apice.etiqueta;
			k1_3.s2.etiqueta[2] = '\0';
			k1_3.s2.a = apice;
			
			k1_3.s3.etiqueta[0] = apice.etiqueta;
			k1_3.s3.etiqueta[2] = '\0';
			k1_3.s3.a = apice;


			// Selecciona el primer segmentos de la k1.3
			for(j = 0; j < n; j++){
				if(puntos_iguales(puntos[l+j], apice)) continue;
				
				k1_3.s1.b = puntos[l+j];
				k1_3.s1.etiqueta[1] = puntos[l+j].etiqueta;

				for(k = j+1; k < n; k++){
					if(puntos_iguales(puntos[l+k], apice)) continue;

					k1_3.s2.b = puntos[l+k];
					k1_3.s2.etiqueta[1] = puntos[l+k].etiqueta;

					for(m = k+1; m < n; m++){
						if(puntos_iguales(puntos[l+m], apice)) continue;

						k1_3.s3.b = puntos[l+m];
						k1_3.s3.etiqueta[1] = puntos[l+m].etiqueta;

						nk1_3++;

						fprintf(log, "k1_3: %s %s %s\n", k1_3.s1.etiqueta, k1_3.s2.etiqueta, k1_3.s3.etiqueta);

						// Selecciona el apice del segundo k1.3
						for(o = 0; o < n; o++){
							if(puntos_iguales(puntos[o], apice) || puntos_iguales(puntos[o], k1_3.s1.b)
								|| puntos_iguales(puntos[o], k1_3.s2.b) || puntos_iguales(puntos[o], k1_3.s3.b))
								continue;

							apice2 = puntos[o];
							segmento.etiqueta[0] = apice2.etiqueta;
							segmento.a = apice2;

							for(p = 0; p < n; p++){
								if(puntos_iguales(puntos[p], apice) || puntos_iguales(puntos[p], k1_3.s1.b)
									|| puntos_iguales(puntos[p], k1_3.s2.b) || puntos_iguales(puntos[p], k1_3.s3.b)
									|| puntos_iguales(puntos[p], apice2))
									continue;

								segmento.etiqueta[1] = puntos[p].etiqueta;
								segmento.etiqueta[2] = '\0';
								segmento.b = puntos[p];

								if(interseccion(k1_3.s1, segmento) || interseccion(k1_3.s2, segmento)
									|| interseccion(k1_3.s3, segmento)){
								

									printf("se encontro una CF con k1_3: %s %s %s y segmento %s en otype %d\n",
										k1_3.s1.etiqueta, k1_3.s2.etiqueta, k1_3.s3.etiqueta, segmento.etiqueta, (l/n)+1);
									printf("%c%c\n", puntos[0].etiqueta, puntos[p].etiqueta);
									if(puntos_iguales(segmento.a, apice) || puntos_iguales(segmento.a, k1_3.s1.b)
										|| puntos_iguales(segmento.a, k1_3.s2.b) || puntos_iguales(segmento.a, k1_3.s3.b)
										|| puntos_iguales(segmento.b, apice) || puntos_iguales(segmento.b, k1_3.s1.b)
										|| puntos_iguales(segmento.b, k1_3.s2.b) || puntos_iguales(segmento.b, k1_3.s3.b))
										return 0;						
								}

							}
							//fprintf(log, "se selecciono %c como apice2\n", apice2.etiqueta);
						}
					}
				}

			}
		}
		fprintf(log, "Total k1_3: %d con n = %d\n", nk1_3, n);
		//return 0;
	}
	return 0;
}