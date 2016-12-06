#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct punto{
	uint16_t x;
	uint16_t y;
}Punto;


int main(int argc, char *argv[]){
	
	int n, types, c = 1, i, bytes;
	char order_type[50];


	printf("Selecciona el valor de n entre 3 y 10: ");
	scanf("%d", &n);

	switch(n){
		case 3: strcpy(order_type, "order_types/otypes03.b08"); types = 1; bytes = 1; break;
		case 4: strcpy(order_type, "order_types/otypes04.b08"); types = 2; bytes = 1; break;
		case 5: strcpy(order_type, "order_types/otypes05.b08"); types = 3; bytes = 1; break;
		case 6: strcpy(order_type, "order_types/otypes06.b08"); types = 16; bytes = 1; break;
		case 7: strcpy(order_type, "order_types/otypes07.b08"); types = 135; bytes = 1; break;
		case 8: strcpy(order_type, "order_types/otypes08.b08"); types = 3315; bytes = 1; break;
		case 9: strcpy(order_type, "order_types/otypes09.b16"); types = 158817; bytes = 2; break;
		case 10: strcpy(order_type, "order_types/otypes10.b16"); types = 14309547; bytes = 2; break;
	}

	FILE *file = fopen(order_type, "rb");
	uint16_t a, b;

	Punto *order_types = (Punto*)malloc(sizeof(Punto)*types*n);


	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}


	i = 0;
	while(!feof(file)){

		//fscanf(file, "%d", &a);
		//fscanf(file, "%d", &b);
		fread(&a, bytes, 1, file);
		fread(&b, bytes, 1, file);

		//printf("(%d, %d)\n", a, b);

		order_types[i].x = (uint16_t)a;
		order_types[i].y = (uint16_t)b;

		i++;

		//if(i == types*n) break;

	}
//return 0;
	for(i = 0, c = 1; i < types*n; i++, c++){
		printf("(%d, %d), ", order_types[i].x, order_types[i].y);

		if(c % n == 0) printf("\n");
	}


	printf("\n");

	return 0;
}