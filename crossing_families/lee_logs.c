#include <stdio.h>

typedef struct cf{
	int otype;
	int ncrossings;
}CrossingFamily;


int main(int argc, char *argv[]){
	FILE *file;
	int otype, ncrossings;
	CrossingFamily min, max;
	char c, nombre[50];

	do{
		printf("Nombre del archivo: ");
		scanf("%s", nombre);
	}while((file = fopen(nombre, "r")) == NULL);



	fscanf(file, "%d%c %d", &min.otype, &c, &min.ncrossings);

	max.otype = min.otype;
	max.ncrossings = min.ncrossings;

	while(!feof(file)){
		//printf("%d %c %d\t", otype, c, ncrossings);
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

	printf("Minimo otype %d con %d Crossing Families\n", min.otype, min.ncrossings);
	printf("Maximo otype %d con %d Crossing Families\n", max.otype, max.ncrossings);

	fclose(file);

	return 0;
}