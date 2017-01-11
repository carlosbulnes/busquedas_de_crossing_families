#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct punto{
	char etiqueta;
	uint16_t x;
	uint16_t y;
}Punto;

typedef struct segmento{
	char etiqueta[3];
	struct punto a;
	struct punto b;
}Segmento;

int puntos_iguales(Punto a, Punto b){
	return a.x == b.x && a.y == b.y;
}

int comparten_punto(Segmento s1, Segmento s2){
	return puntos_iguales(s1.a, s2.a) || puntos_iguales(s1.a, s2.b) || puntos_iguales(s1.b, s2.a) || puntos_iguales(s1.b, s2.b);
}

int area(Punto a, Punto b, Punto c){
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int izquierda(Punto a, Punto b, Punto c){
	return area(a, b, c) > 0;
}

int Xor(int x, int y){
	return !x ^ !y;
}

int interseccion(Segmento s1, Segmento s2){
	Punto a = s1.a, b = s1.b, c = s2.a, d = s2.b;
	
	return Xor(izquierda(a, b, c), izquierda(a, b, d)) && Xor(izquierda(c,d,a), izquierda(c,d,b));
}

int main(int argc, char *argv[]){
	
	int n, otypes, c = 1, i, j, k, l, m, bytes, nsegmentos, npuntos;
	int ncrossings = 0, siempre_existe = 1, bandera;
	char order_type[50], etiqueta;

	//system("clear");
	//printf("Selecciona el valor de n entre 3 y 10: ");
	//scanf("%d", &n);
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

	// Recorre los order types
	for(l = 0; l < npuntos; l+=n){
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

		bandera = 0;

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
					for(k = 0; k < nsegmentos; k++){
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

								if(interseccion(srojos[0], sazules[0]) || interseccion(srojos[0], sazules[1])
									|| interseccion(srojos[1], sazules[0]) || interseccion(srojos[1], sazules[1])){
									
									ncrossings++;
									bandera = 1;
									//printf("Se encontro una crossing family\n");

									//printf("Rojos: %s y %s, ", srojos[0].etiqueta, srojos[1].etiqueta);
									
									//printf("Azules: %s y %s\n", sazules[0].etiqueta, sazules[1].etiqueta);
									//break;
								}
								/*else{
									printf("Rojos: %s y %s, ", srojos[0].etiqueta, srojos[1].etiqueta);
									
									printf("Azules: %s y %s no son CF\n", sazules[0].etiqueta, sazules[1].etiqueta);
									break;
								}*/
							}
						}
					}
				}
			}
		}

		if(bandera == 0)
			siempre_existe = 0;
		//siempre_existe = siempre_existe && bandera;
		//printf("----------------------------------------------------\n");
		
		/*			
		printf("Los n en 2 segmentos del order type %d son: \n", (inicio/n)+1);
		for(i = 0; i < nsegmentos; i++){
			printf("|(%d, %d), (%d, %d)|, ", segmentos[i].a.x, segmentos[i].a.y, segmentos[i].b.x, segmentos[i].b.y);
		}
		printf("\n\n");
		*/
	}

	/*
	// Imprime los order types
	for(i = 0, c = 1; i < npuntos; i++, c++){
		printf("%c: (%d, %d), ", puntos[i].etiqueta, puntos[i].x, puntos[i].y);

		if(c % n == 0) printf("\n");
	}
	printf("\n");
	*/

	printf("\nTotal de Crossing Families: %d\n", ncrossings);
	if(siempre_existe)
		printf("Siempre existe una Crossing Families con n = %d\n", n);
	else
		printf("no existe siempre una Crossing Families con n = %d\n", n);

	return 0;
}