#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct punto{
	uint16_t x;
	uint16_t y;
}Punto;


int main(int argc, char *argv[]){
	
	int n, types, c = 1, i = 0;
	char order_type[50];

	printf("Selecciona el valor de n entre 3 y 10: ");
	scanf("%d", &n);

	switch(n){
		case 3: strcpy(order_type, "order_types/otypes03.b08"); types = 1; break;
		case 4: strcpy(order_type, "order_types/otypes04.b08"); types = 2; break;
		case 5: strcpy(order_type, "order_types/otypes05.b08"); types = 3; break;
		case 6: strcpy(order_type, "order_types/otypes06.b08"); types = 16; break;
		case 7: strcpy(order_type, "order_types/otypes07.b08"); types = 135; break;
		case 8: strcpy(order_type, "order_types/otypes08.b08"); types = 3315; break;
		case 9: strcpy(order_type, "order_types/otypes09.b16"); types = 158817; break;
		case 10: strcpy(order_type, "order_types/otypes10.b16"); types = 14309547; break;
	}

	FILE *file = fopen(order_type, "r");
	unsigned char a, b;

	Punto *order_types = (Punto*)malloc(sizeof(Punto)*types*n);


	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}

	i = 0;
	while(!feof(file)){

		fscanf(file, "%c", &a);
		fscanf(file, "%c", &b);

		order_types[i].x = (uint16_t)a;
		order_types[i].y = (uint16_t)b;

		i++;

		if(i == types*n) break;

	}

	for(i = 0, c = 1; i < types*n; i++, c++){
		printf("(%d, %d), ", order_types[i].x, order_types[i].y);

		if(c % n == 0) printf("\n");
	}


	printf("\n");

	return 0;
}