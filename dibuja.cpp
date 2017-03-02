#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <GL/glut.h>

typedef struct punto{
	char etiqueta;
	uint16_t x;
	uint16_t y;
}Punto;

Punto *puntos;
Punto *puntos_otype;
int n, ancho = 1200, alto = 700;
char buffer[20]="";//bufers para escribir en la pantalla
int otype = 0;

void procesa_puntos(){
	int inicio, i, l;

	//printf("otype de inicio: "); scanf("%d", &inicio);
	l = (otype - 1) * n;

	for(i = 0; i < n; i++){
		puntos_otype[i].etiqueta = puntos[l+i].etiqueta;
		puntos_otype[i].x = puntos[l+i].x;
		puntos_otype[i].y = puntos[l+i].y;
	}

	for(i = 0; i < n; i++)
		printf("%c = (%d, %d)\n", puntos_otype[i].etiqueta, puntos_otype[i].x, puntos_otype[i].y);

}

void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void keyboard(unsigned char key, int x, int y){
	if(key == 0x1b)
		exit(0); // terminar program

	if(key == 13){
		procesa_puntos();
		strcpy(buffer, "");
	}

	if((key>=97&&key<=122)||(key>=65&&key<=90)||key==32||(key>=48&&key<=57)){//si es letra min, may, espacio,numeros
		int len = strlen(buffer);

		if(len < 20){//si se puede escribir en el buffer se escribe
			buffer[len] = key;
			buffer[len+1] = '\0';
			otype = atoi(buffer);
		}
	}
	
	printf("%d\n", otype);
	glutPostRedisplay();
}

/*
void special(int key, int x, int y){

	if(key==GLUT_KEY_END){
		strcpy(buffer,"");
	}
	glutPostRedisplay();
}
*/

void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,1,0); glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glVertex2i(130,060); glVertex2i( 50,060);
	glVertex2i(130,150); glVertex2i( 50,150);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i( 70,100); glVertex2i(110,100);
	glVertex2i(150,100); glVertex2i(230,100);
	glVertex2i(190,140); glVertex2i(190,070);
	glVertex2i(250,100); glVertex2i(330,100);
	glVertex2i(290,140); glVertex2i(290,070);
	glEnd();
	
	glutSwapBuffers();
}

void inicializa_opengl(){
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (ancho,alto);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Ventana OpenGL");
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc (special);	
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
}


int main(int argc, char *argv[]){
	
	int otypes, c = 1, i, l, bytes, npuntos, inicio, kotypes;
	char order_type[50], etiqueta;
	
	if(argc < 1){
		printf("Se necesita el valor de n y otype como argumentos\n");
		return -1;
	}
	
	n = atoi(argv[1]);
	//inicio = atoi(argv[2]);
	
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
	
	FILE *file = fopen(order_type, "r");
	uint16_t a, b;
	
	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}
	
	npuntos = otypes*n;
	puntos = (Punto*)malloc(sizeof(Punto)*npuntos);
	puntos_otype = (Punto*)malloc(sizeof(Punto)*n);

  	// Lectura del archivo de la base de datos
	etiqueta = 'A';
	for(i = 0; i < npuntos;){
		fread(&a, bytes, 1, file);
		fread(&b, bytes, 1, file);

		puntos[i].etiqueta = etiqueta;
		puntos[i].x = a;
		puntos[i].y = b;

		etiqueta += 1;
		i++;
		if(i % n == 0) etiqueta = 'A';
	}
	fclose(file);

	glutInit(&argc, argv);
	inicializa_opengl();
	//glutIdleFunc(procesa_puntos);
/*
	for(i = 0;i < n; i++){
		printf("%c = (%d, %d)\n", puntos_otype[i].etiqueta, puntos_otype[i].x, puntos_otype[i].y);
	}
*/
	//npuntos = otypes*n;
	//lee_otype();


	//lee_otype();
	//glutDisplayFunc(lee_otype);
	//glutIdleFunc(lee_otype);
	//glutReshapeFunc (reshape_cb);

	glutMainLoop();
	return 0;
}
