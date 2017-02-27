#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]){
	
	int n, otypes, c = 1, i, l, bytes, npuntos, inicio, kotypes;
	char order_type[50], etiqueta;

	if(argc < 3){
		printf("Se necesita el valor de n y otype como argumentos\n");
		return -1;
	}
	
	n = atoi(argv[1]);
	inicio = atoi(argv[2]);

	switch(n){
		case 3: strcpy(order_type, "order_types/otypes03.b08"); otypes = 1; bytes = 1; break;
		case 4: strcpy(order_type, "order_types/otypes04.b08"); otypes = 2; bytes = 1; break;
		case 5: strcpy(order_type, "order_types/otypes05.b08"); otypes = 3; bytes = 1;  break;
		case 6: strcpy(order_type, "order_types/otypes06.b08"); otypes = 16; bytes = 1; break;
		case 7: strcpy(order_type, "order_types/otypes07.b08"); otypes = 135; bytes = 1; break;
		case 8: strcpy(order_type, "order_types/otypes08.b08"); otypes = 3315; bytes = 1; break;
		case 9: strcpy(order_type, "order_types/otypes09.b16"); otypes = 158817; bytes = 2; break;
		case 10: strcpy(order_type, "order_types/otypes10.b16"); otypes = 14309547; bytes = 2; break;
	}

	FILE *file = fopen(order_type, "rb");
	
	uint16_t a, b;
	npuntos = otypes*n;

	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}

	//printf("otype de inicio: "); scanf("%d", &inicio);

	if(inicio > otypes){
		printf("Order Type no existe\n");
		return 0;
	}

	//printf("otypes a procesar: "); scanf("%d", &kotypes);

	l = (inicio - 1) * n;
	//npuntos = (kotypes == 0) ? npuntos : (l + (kotypes * n));
	printf("Order Type: %d\n", (l/n)+1);

	for(i = 0; i < l; i++){
		fread(&a, bytes, 1, file);
		fread(&b, bytes, 1, file);
	}

	// Recorre los order types
	for(i = 0, etiqueta = 'A'; i < n; i++, etiqueta++){

		fread(&a, bytes, 1, file);
		fread(&b, bytes, 1, file);

		printf("%c = (%d, %d)\n", etiqueta, a, b);
	}

	fclose(file);
	return 0;
}