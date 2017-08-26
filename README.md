# Búsqueda de Crossing Families para Gráficas Geométricas

En este repositorio se encuentran todos los programas desarrollados en el trabajo de tesis de Maestría "Crossing Families para Gráficas Geométricas" realizado por Carlos Antonio Bulnes Domínguez (autor del repositorio) asesorado por la Dra. Dolores Lara Cuevas.

Los programas implementados para la realización de dicha tesis se encuentran en:

crossing_families/2k2.c

crossing_families/k13.c

thrackles/thrackles.c

Dichos programas pueden ser ejecutados mediante el comando 

make 2k2

make k13

make thrackle

respectivamente.


Por último se incluyen dos programas en OpenGl 

opengl/dibuja.cpp : para visualizar los tipos de orden de 8, 9 y 10 puntos

opengl/dibuja_thrackles.cpp : para vizualizar los thrackles para cada tipos de orden de 8, 9 y 10 puntos

los cuales se compilan y ejecutan con

make dotypes

make dthrackles


*** Dependencias ***

Para ejecutar los programas en openGL es necesario instalar la biblioteca freeglut y curl

En Ubuntu:

sudo apt-get install libcurl4-openssl-dev

sudo apt-get install freeglut3-dev

En Arch:

sudo pacman -S freeglut

sudo pacman -S curl

