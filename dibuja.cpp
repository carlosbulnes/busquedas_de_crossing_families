#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <GL/glut.h>
#include "gl2ps.h"
#include "base_de_datos.h"

typedef struct punto{
	char etiqueta;
	uint16_t x;
	uint16_t y;
}Punto;

typedef struct {
	char etiqueta;
	float x;
	float y;
}Puntof;

Punto *puntos;
Puntof *puntos_otype;
int n, ancho = 1000, alto = 800;
char buffer[20]="", textos[50] = "Otype 1", buffer2[20];
int otype = 1, otypes;


void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void print(int x, int y, char *string){
	glRasterPos2f(x,y);
	
	int len = strlen(string);

	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	}
}

void dibuja() {
	int i;
	glClear(GL_COLOR_BUFFER_BIT);

	print(ancho-200,alto-50,textos);

	glColor3f(0.0, 0.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for(i = 0; i < n; i++){
		glVertex2f(puntos_otype[i].x, puntos_otype[i].y);
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	for(i = 0; i < n; i++){
		glRasterPos2f(puntos_otype[i].x, puntos_otype[i].y);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, puntos_otype[i].etiqueta);
	}
	
	glColor3f(.5,.5,.5);
	glLineWidth(.2);
	for(i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			glBegin(GL_LINE_STRIP);
			glVertex2i(puntos_otype[i].x, puntos_otype[i].y);
			glVertex2i(puntos_otype[j].x, puntos_otype[j].y);
			glEnd();
		}
	}
	glutSwapBuffers();
}

void procesa_puntos(){
	int i, l;
	int xmin, xmax, ymin, ymax, ancho_otype, alto_otype;

	l = (otype - 1) * n;

	for(i = 0; i < n; i++){
		puntos_otype[i].etiqueta = puntos[l+i].etiqueta;
		puntos_otype[i].x = puntos[l+i].x;
		puntos_otype[i].y = puntos[l+i].y;
	}

	xmin = xmax = puntos_otype[0].x;
	ymin = ymax = puntos_otype[0].y;

	for(i = 1; i < n; i++){
		if(puntos_otype[i].x < xmin)
			xmin = puntos_otype[i].x;
		else if(puntos_otype[i].x > xmax)
			xmax = puntos_otype[i].x;

		if(puntos_otype[i].y < ymin)
			ymin = puntos_otype[i].y;
		else if(puntos_otype[i].y > ymax)
			ymax = puntos_otype[i].y;
	}

	ancho_otype = (xmax-xmin);
	alto_otype = (ymax-ymin);

	//printf("%d %d\n", ancho_otype, alto_otype);
	//for(i = 0; i < n; i++)
	//	printf("%c = (%.2f, %.2f)\n", puntos_otype[i].etiqueta, puntos_otype[i].x, puntos_otype[i].y);

	if(alto_otype > ancho_otype){
		for(i = 0; i < n; i++){
			puntos_otype[i].x = (((puntos_otype[i].x - xmin) * (alto-30))/alto_otype) + 10;
			puntos_otype[i].y = (((puntos_otype[i].y - ymin) * (alto-30))/alto_otype) + 10;
		}
	}else{
		for(i = 0; i < n; i++){
			puntos_otype[i].x = (((puntos_otype[i].x - xmin) * (alto-30))/ancho_otype) + 10;
			puntos_otype[i].y = (((puntos_otype[i].y - ymin) * (alto-30))/ancho_otype) + 10;
		}		
	}

	//for(i = 0; i < n; i++)
	//	printf("%c = (%.2f, %.2f)\n", puntos_otype[i].etiqueta, puntos_otype[i].x, puntos_otype[i].y);

	//glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
	if(key == 0x1b)
		exit(0); // terminar programa

	if(key == 13){
		otype = atoi(buffer);
		if(otype > 0 && otype <= otypes)
			procesa_puntos();
		strcpy(buffer, "");
	}

	if(key == 'p'){
		FILE *fp;
 	 	int state = GL2PS_OVERFLOW, buffsize = 0;
 	 	char nombre_archivo[50] = "n", ruta[50] = "pdfs/";
 	 	char temp_char[15];

 	 	sprintf(temp_char, "%d", n);
 	 	strcat(nombre_archivo, temp_char);
 	 	strcat(nombre_archivo, "_otype");
 	 	sprintf(temp_char, "%d", otype);
 	 	strcat(nombre_archivo, temp_char);
 	 	strcat(nombre_archivo, ".pdf");
 	 	strcat(ruta, nombre_archivo);

		fp = fopen(ruta, "wb");
    	printf("Imprimiendo a archivo %s\n", ruta);
    	while(state == GL2PS_OVERFLOW){
      		buffsize += 1024*1024;
      		gl2psBeginPage("pdf", "gl2psTestSimple", NULL, GL2PS_PDF/*GL2PS_EPS*/, GL2PS_SIMPLE_SORT,
                     GL2PS_DRAW_BACKGROUND | GL2PS_USE_CURRENT_VIEWPORT,
                     GL_RGBA, 0, NULL, 0, 0, 0, buffsize, fp, nombre_archivo);
      		dibuja();
      		state = gl2psEndPage();
    	}
    	fclose(fp);
    	printf("PDF generado\n");
	}

	int len = strlen(buffer);
	// Verifica que el string de buffer no esté lleno y que esté ingresando solo numeros
	if(len < 20 && (key >=48 && key <=57)){
		buffer[len] = key;
		buffer[len+1] = '\0';
		strcpy(textos, "Otype: ");
		strcat(textos, buffer);
	}
	
	glutPostRedisplay();
}

void special(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
		if(otype > 1){
			otype--;
			procesa_puntos();
			strcpy(textos, "Otype: ");
			sprintf(buffer2, "%d", otype);
			strcat(textos, buffer2);
		}
	}
	else if(key == GLUT_KEY_RIGHT){
		if(otype < otypes){
			otype++;
			procesa_puntos();
			strcpy(textos, "Otype: ");
			sprintf(buffer2, "%d", otype);
			strcat(textos, buffer2);
		}
	}else if(key == GLUT_KEY_END){
		otype = otypes;
		procesa_puntos();
		strcpy(textos, "Otype: ");
		sprintf(buffer2, "%d", otype);
		strcat(textos, buffer2);		
	}else if(key == GLUT_KEY_HOME){
		otype = 1;
		procesa_puntos();
		strcpy(textos, "Otype: ");
		sprintf(buffer2, "%d", otype);
		strcat(textos, buffer2);		
	}
	glutPostRedisplay();
}


void inicializa_opengl(){
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (ancho,alto);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Order Types");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc (special);	
	glutDisplayFunc (dibuja);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
}

int main(int argc, char *argv[]){
	
	int i, l, bytes, npuntos, inicio, kotypes;
	char order_type[50], etiqueta;
		
	do{
		printf("n: "); scanf("%d", &n);
	}while(n < 3 || n > 10);

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

	verifica_base_datos(n, order_type);
	
	FILE *file = fopen(order_type, "r");
	uint16_t a = 0, b = 0;
	
	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}
	
	npuntos = otypes*n;
	puntos = (Punto*)malloc(sizeof(Punto)*npuntos);
	puntos_otype = (Puntof*)malloc(sizeof(Puntof)*n);

  	// Lectura del archivo de la base de datos
	etiqueta = '1';
	for(i = 0; i < npuntos;){
		fread(&a, bytes, 1, file);
		fread(&b, bytes, 1, file);

		//printf("Leidos %d %d\n", a, b); getchar();
		puntos[i].etiqueta = etiqueta;
		puntos[i].x = a;
		puntos[i].y = b;

		etiqueta += 1;
		i++;
		if(i % n == 0) etiqueta = '1';
	}
	fclose(file);

	procesa_puntos();

	glutInit(&argc, argv);
	inicializa_opengl();
	dibuja();

	glutMainLoop();
	return 0;
}
