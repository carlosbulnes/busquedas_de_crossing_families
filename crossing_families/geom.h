#include <stdint.h>

typedef struct punto{
	char etiqueta;
	uint16_t x;
	uint16_t y;
}Punto;

typedef struct segmento{
	char etiqueta[3];
	struct punto a;
	struct punto b;
}Segmento;

int puntos_iguales(Punto a, Punto b){
	return a.x == b.x && a.y == b.y;
}

int comparten_punto(Segmento s1, Segmento s2){
	return puntos_iguales(s1.a, s2.a) || puntos_iguales(s1.a, s2.b) || puntos_iguales(s1.b, s2.a) || puntos_iguales(s1.b, s2.b);
}

int area(Punto a, Punto b, Punto c){
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int izquierda(Punto a, Punto b, Punto c){
	return area(a, b, c) > 0;
}

int Xor(int x, int y){
	return !x ^ !y;
}

int interseccion(Segmento s1, Segmento s2){
	Punto a = s1.a, b = s1.b, c = s2.a, d = s2.b;
	
	return Xor(izquierda(a, b, c), izquierda(a, b, d)) && Xor(izquierda(c,d,a), izquierda(c,d,b));
}