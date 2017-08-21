2k2:
	clear && gcc crossing_families/2k2.c -o prog -lcurl -O2 && ./prog

k13:
	clear && gcc crossing_families/k1-3.c -o prog -lcurl -O2 && ./prog

thrackle:
	clear && gcc thrackles/thrackles.c -o prog -lcurl -O2 && ./prog

dotypes:
	g++ dibuja.cpp gl2ps.c -lglut -lGL -lGLU -lcurl -lm -o dibuja && ./dibuja

dthrackles:
	g++ thrackles/dibuja_thrackles.cpp gl2ps.c -lglut -lGL -lGLU -lcurl -lm -o dibuja && ./dibuja

clean:
	rm -f crossing_families/logk1-3-*
	rm -f crossing_families/log2k2-*
	rm -f thrackles/logthrackle-*
	rm -f dibuja
	rm -f prog