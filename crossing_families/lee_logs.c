#include <stdio.h>

int main(int argc, char const *argv[])
{
	FILE *file = fopen("logk1-3-10", "r");
	int a, b;
	char c;

	while(!feof(file)){
		fscanf(file, "%d%c %d", &a, &c, &b);

		printf("%d %c %d\t", a, c, b);
	}




	return 0;
}