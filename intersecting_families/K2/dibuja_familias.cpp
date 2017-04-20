#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <GL/glut.h>
#include "k2.h"

typedef struct {
	char etiqueta;
	float x;
	float y;
}Puntof;

Punto *puntos;
Puntof *puntos_otype;
Segmento *segmentos;
FILE *log;
char **ifamilies;
int n, ancho = 1000, alto = 800;
char buffer[20]="", textos[50] = "Otype: 1", textos2[50] = "Int. Family 1", buffer2[20];
int otype = 1, otypes, nsegmentos, kint_fam = 1, nintersecting_families = 0;

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
	if(nintersecting_families > 0){
		for(i = 0; i < n*2; i+=2){
			glBegin(GL_LINE_STRIP);
			glVertex2i(puntos_otype[(int)(ifamilies[kint_fam-1][i]) - 49].x, puntos_otype[(int)(ifamilies[kint_fam-1][i]) - 49].y);
			glVertex2i(puntos_otype[(int)(ifamilies[kint_fam-1][i+1]) - 49].x, puntos_otype[(int)(ifamilies[kint_fam-1][i+1]) - 49].y);
			glEnd();
		}
	}else{
		for(i = 0; i < n; i++){
			strcpy(textos2, "Int. Family 0");
			for(int j = i+1; j < n; j++){
				glBegin(GL_LINE_STRIP);
				glVertex2i(puntos_otype[i].x, puntos_otype[i].y);
				glVertex2i(puntos_otype[j].x, puntos_otype[j].y);
				glEnd();
			}
		}
	}
	
	glColor3f(.5,.5,.5);
	print(ancho-200,alto-50,textos);
	print(ancho-200,alto-80,textos2);
	
	glutSwapBuffers();
}

int cantidad_intersecting_families(){
	FILE *file;// = fopen("intersecting_families/K2/logK2-8lista", "r");
	int id, cantidad;
	char ch;

	switch(n){
		case 6: file = fopen("intersecting_families/K2/logK2-6lista", "r"); break;
		case 8: file = fopen("intersecting_families/K2/logK2-8lista", "r"); break;
		case 9: file = fopen("intersecting_families/K2/logK2-9lista", "r"); break;
		case 10: file = fopen("intersecting_families/K2/logK2-10lista", "r"); break;
	}

	if(file == NULL) return -1;

	for(int i = 0; i < otype; i++){
		fscanf(file, "%d%c %d", &id, &ch, &cantidad);
	}

	fclose(file);
	return cantidad;
}


void genera_arreglo_de_if(int nif){
	FILE *log = fopen("intersecting_families/K2/ifn", "r");
	ifamilies = (char **)malloc(sizeof(char*)*nif);

	for(int i = 0; i < nif; i++){
		ifamilies[i] = (char*)malloc(sizeof(char)*20);
	}

	for(int i = 0; i < nif; i++){
		fscanf(log, "%s", ifamilies[i]);
	}

	fclose(log);
	//printf("%s\n", ifamilies[0]);
}

void procesa_puntos(){
	int i, k, l;
	int xmin, xmax, ymin, ymax, ancho_otype, alto_otype;

	l = (otype - 1) * n;

	for(i = 0; i < n; i++){
		puntos_otype[i].etiqueta = puntos[l+i].etiqueta;
		puntos_otype[i].x = puntos[l+i].x;
		puntos_otype[i].y = puntos[l+i].y;
	}

	nintersecting_families = cantidad_intersecting_families();
	//printf("numero de IF: %d\n", nintersecting_families);

	for(i = l, k = 0; i < (l+n); i++){
		for(int j = i+1; j < (l+n); j++){
			segmentos[k].a = puntos[i];
			segmentos[k].b = puntos[j];
			segmentos[k].etiqueta[0] = puntos[i].etiqueta;
			segmentos[k].etiqueta[1] = puntos[j].etiqueta;
			segmentos[k].etiqueta[2] = '\0';
			k++;
		}	
	}

	log = fopen("intersecting_families/K2/ifn", "w");
	
	switch(n){
		case 6: n6(segmentos, nsegmentos, log); break;
		case 8: n8(segmentos, nsegmentos, log); break;
		case 9: n9(segmentos, nsegmentos, log); break;
		case 10: n10(segmentos, nsegmentos, log); break;
	}

	fclose(log);
	genera_arreglo_de_if(nintersecting_families);

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

}

void keyboard(unsigned char key, int x, int y){
	if(key == 0x1b)
		exit(0); // terminar programa

	if(key == 13){
		otype = atoi(buffer);
		if(otype > 0 && otype <= otypes){
			kint_fam = 1;
			procesa_puntos();
			strcpy(textos2, "Int. Family ");
			sprintf(buffer2, "%d", kint_fam);
			strcat(textos2, buffer2);
			strcat(textos2, "/");
			sprintf(buffer2, "%d", nintersecting_families);
			strcat(textos2, buffer2);
		}
		strcpy(buffer, "");
	}else if(key == 32){
		int k;
		k = atoi(buffer);
		if(k > 0 && k <= nintersecting_families){
			kint_fam = k;
			procesa_puntos();
			strcpy(textos2, "Int. Family ");
			sprintf(buffer2, "%d", kint_fam);
			strcat(textos2, buffer2);
			strcat(textos2, "/");
			sprintf(buffer2, "%d", nintersecting_families);
			strcat(textos2, buffer2);			
		}

		strcpy(textos, "Otype: ");
		sprintf(buffer2, "%d", otype);
		strcat(textos, buffer2);
		strcpy(buffer, "");
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
			kint_fam = 1;
			procesa_puntos();
		}
	}else if(key == GLUT_KEY_RIGHT){
		if(otype < otypes){
			otype++;
			kint_fam = 1;
			procesa_puntos();
		}
	}else if(key == GLUT_KEY_DOWN){
		if(kint_fam < nintersecting_families){
			kint_fam++;
			procesa_puntos();

		}
	}else if(key == GLUT_KEY_UP){
		if(kint_fam > 1){
			kint_fam--;
			procesa_puntos();			
		}
	}else if(key == GLUT_KEY_END){
		otype = otypes;
		kint_fam = 1;
		procesa_puntos();
	}else if(key == GLUT_KEY_HOME){
		otype = 1;
		kint_fam = 1;
		procesa_puntos();		
	}else if(key == GLUT_KEY_PAGE_DOWN){
		kint_fam = nintersecting_families;
	}else if(key == GLUT_KEY_PAGE_UP){
		kint_fam = 1;
	}

	// Actualizacion de los textos
	strcpy(textos, "Otype: ");
	sprintf(buffer2, "%d", otype);
	strcat(textos, buffer2);	
	strcpy(textos2, "Int. Family ");
	sprintf(buffer2, "%d", kint_fam);
	strcat(textos2, buffer2);	
	strcat(textos2, "/");
	sprintf(buffer2, "%d", nintersecting_families);
	strcat(textos2, buffer2);

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
	
	//if(argc < 1){
	//	printf("Se necesita el valor de n y otype como argumentos\n");
	//	return -1;
	//}
	
	//n = atoi(argv[1]);
	
	printf("n: "); scanf("%d", &n);

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
	
	FILE *file = fopen(order_type, "r");
	uint16_t a = 0, b = 0;
	
	if(file == NULL){
		printf("No se puede abrir archivo\n");
		return 0;
	}
	
	npuntos = otypes*n;
	puntos = (Punto*)malloc(sizeof(Punto)*npuntos);
	puntos_otype = (Puntof*)malloc(sizeof(Puntof)*n);
	segmentos = (Segmento*)malloc(sizeof(Segmento)*nsegmentos);

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
	strcat(textos2, "/");
	sprintf(buffer2, "%d", nintersecting_families);
	strcat(textos2, buffer2);

	glutInit(&argc, argv);
	inicializa_opengl();
	dibuja();

	glutMainLoop();
	return 0;
}
