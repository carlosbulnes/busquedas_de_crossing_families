#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct punto{
	uint16_t x;
	uint16_t y;
}Punto;

typedef struct segmento{
	struct punto a;
	struct punto b;
}Segmento;

int puntos_iguales(Punto a, Punto b){
	return a.x == b.x && a.y == b.y;
}

int es_colineal(Segmento s1, Segmento s2){
	return puntos_iguales(s1.a, s2.a) || puntos_iguales(s1.a, s2.b) || puntos_iguales(s1.b, s2.a) || puntos_iguales(s1.b, s2.b);
}


int vertices_iguales(Punto p1, Punto p2){
	if(p1.x == p2.x && p1.y == p2.y)
		return 1;

	return 0;
}

int main(int argc, char *argv[]){
	
	int n, otypes, c = 1, i, j, k, bytes, nsegmentos, bandera = 0;
	int inicio, final, npuntos;
	char order_type[50];

	printf("Selecciona el valor de n entre 3 y 10: ");
	scanf("%d", &n);

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
	Segmento segmentos_rojos[2], segmentos_azules[2];


	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}

	i = 0;
	while(!feof(file)){

		fread(&a, bytes, 1, file);
		fread(&b, bytes, 1, file);

		puntos[i].x = a;
		puntos[i].y = b;

		i++;
	}

	// Recorre los order types
	for(inicio = 0; inicio < npuntos; inicio+=n){
		// Construye los n en 2 segmentos
		for(i = inicio, k = 0; i < (inicio+n); i++){
			for(j = i+1; j < (inicio+n); j++){
				segmentos[k].a = puntos[i];
				segmentos[k].b = puntos[j];
				k++;
			}	
		}

		for(i = 0; i < nsegmentos; i++){
			segmentos_rojos[0] = segmentos[i];

			// Busca la pareja del segmento rojo
			bandera = 0;
			for(j = 0; j < nsegmentos; j++){
				if(!es_colineal(segmentos_rojos[0],segmentos[j])){
					segmentos_rojos[1] = segmentos[j];
					bandera = 1;
					break;
				}
			}

			if(bandera)
				printf("|(%d, %d), (%d, %d)| y |(%d, %d), (%d, %d)| elegidos\n", segmentos_rojos[0].a.x, segmentos_rojos[0].a.y, segmentos_rojos[0].b.x, segmentos_rojos[0].b.y, segmentos_rojos[1].a.x, segmentos_rojos[1].a.y, segmentos_rojos[1].b.x, segmentos_rojos[1].b.y);
			else
				printf("No se encontro pareja\n");
		}


		/*
		// Verifica si los segmentos son o no colineales
		for(i = 0; i < nsegmentos-1; i++){
			if(es_colineal(segmentos[i], segmentos[i+1])){
				printf("|(%d, %d), (%d, %d)| y |(%d, %d), (%d, %d)| son colineales\n", segmentos[i].a.x, segmentos[i].a.y, segmentos[i].b.x, segmentos[i].b.y, segmentos[i+1].a.x, segmentos[i+1].a.y, segmentos[i+1].b.x, segmentos[i+1].b.y);
			}else{
				printf("|(%d, %d), (%d, %d)| y |(%d, %d), (%d, %d)| no son colineales\n", segmentos[i].a.x, segmentos[i].a.y, segmentos[i].b.x, segmentos[i].b.y, segmentos[i+1].a.x, segmentos[i+1].a.y, segmentos[i+1].b.x, segmentos[i+1].b.y);
			}
		}			
		
		printf("Los n en 2 segmentos del order type %d son: \n", (inicio/n)+1);
		for(i = 0; i < nsegmentos; i++){
			printf("|(%d, %d), (%d, %d)|, ", segmentos[i].a.x, segmentos[i].a.y, segmentos[i].b.x, segmentos[i].b.y);
		}
		printf("\n\n");
		*/
	}

	//if(n > 8) return 0;

	/*
	// Imprime los order types
	for(i = 0, c = 1; i < npuntos; i++, c++){
		printf("(%d, %d), ", puntos[i].x, puntos[i].y);

		if(c % n == 0) printf("\n");
	}
	printf("\n");
	*/
	return 0;
}