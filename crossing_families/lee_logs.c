#include <stdio.h>

typedef struct cf{
	int otype;
	int ncrossings;
}CrossingFamily;


int main(int argc, char *argv[]){
	if(argc != 2){
		printf("se necesita el nombre del archivo como argumento\n");
		return -1;
	}

	FILE *file;
	int otype, ncrossings;
	CrossingFamily min, max;
	char c;


	/*
	do{
		printf("Nombre del archivo: ");
		scanf("%s", nombre);
	}while((file = fopen(nombre, "r")) == NULL);
	*/

	if((file = fopen(argv[1], "r")) == NULL){
		printf("no se pudo abrir el archivo\n");
		return -1;
	}


	fscanf(file, "%d%c %d", &min.otype, &c, &min.ncrossings);

	max.otype = min.otype;
	max.ncrossings = min.ncrossings;

	while(!feof(file)){
		fscanf(file, "%d%c %d", &otype, &c, &ncrossings);

		if(ncrossings < min.ncrossings){
			min.otype = otype;
			min.ncrossings = ncrossings;
		}

		if(ncrossings > max.ncrossings){
			max.otype = otype;
			max.ncrossings = ncrossings;
		}
	}
	
	printf("Maximo otype %d con %d Crossing Families\n", max.otype, max.ncrossings);
	printf("Minimo otype %d con %d Crossing Families\n", min.otype, min.ncrossings);

	fclose(file);

	return 0;
}