2k2:
	clear && gcc crossing_families/2k2.c -o prog -g -O2 && ./prog

k13:
	clear && gcc crossing_families/k1-3.c -o prog -g -O2 && ./prog

thrakles:
	clear && gcc thrakles/thrakles.c -o prog -g -O2 && ./prog

dotypes:
	g++ dibuja.cpp -lglut -lGL -lGLU -o dibuja && ./dibuja

dthrakles:
	g++ thrakles/dibuja_familias.cpp -lglut -lGL -lGLU -o dibuja && ./dibuja

clean:
	rm -f crossing_families/logk1-3-*
	rm -f crossing_families/log2k2-*