#!/usr/bin/python3

import pygame, sys, os
from pygame.locals import *

ncrossings = 0
n = 9

def lee_archivo():
	for i in range(1, ncrossings+1):
		texto.append(archivo.read(1))
		texto.append(archivo.read(1))
		texto.append(archivo.read(1))
		texto.append(archivo.read(1))
		texto.append(archivo.read(1))
		texto.append(archivo.read(1))
		texto.append(archivo.read(1))
		texto.append(archivo.read(1))
		#archivo.read(1)

	archivo.close()


def dibuja(cont):

	ventana.fill((255, 255, 255))

	mensaje = fuente.render(str(cont), 1, (0, 0, 0))	
	mensajea = fuente.render('a', 1, (0, 0, 0))
	mensajeb = fuente.render('b', 1, (0, 0, 0))
	mensajec = fuente.render('c', 1, (0, 0, 0))
	mensajed = fuente.render('d', 1, (0, 0, 0))
	mensajee = fuente.render('e', 1, (0, 0, 0))
	mensajef = fuente.render('f', 1, (0, 0, 0))
	mensajeg = fuente.render('g', 1, (0, 0, 0))
	mensajeh = fuente.render('h', 1, (0, 0, 0))
	mensajei = fuente.render('i', 1, (0, 0, 0))
	ventana.blit(mensajea, a)
	ventana.blit(mensajeb, b)
	ventana.blit(mensajec, c)
	ventana.blit(mensajed, d)
	ventana.blit(mensajee, e)
	ventana.blit(mensajef, f)
	ventana.blit(mensajeg, g)
	ventana.blit(mensajeh, h)
	ventana.blit(mensajei, i)
	ventana.blit(mensaje, (15, 5))			
	
	pygame.display.flip()

	print(texto[k], texto[k+1], texto[k+2], texto[k+3], texto[k+4], texto[k+5], texto[k+6], texto[k+7])

	'''
	pygame.draw.circle(ventana, (0,0,0), a, 3)
	pygame.draw.circle(ventana, (0,0,0), b, 3)
	pygame.draw.circle(ventana, (0,0,0), c, 3)
	pygame.draw.circle(ventana, (0,0,0), d, 3)
	pygame.draw.circle(ventana, (0,0,0), e, 3)
	pygame.draw.circle(ventana, (0,0,0), f, 3)
	pygame.draw.circle(ventana, (0,0,0), g, 3)
	pygame.draw.circle(ventana, (0,0,0), h, 3)
	pygame.draw.circle(ventana, (0,0,0), i, 3)
	'''
	pygame.draw.line(ventana, (255, 0, 0), dic[texto[k]], dic[texto[k+1]], 2)
	pygame.draw.line(ventana, (255, 0, 0), dic[texto[k+2]], dic[texto[k+3]], 2)
	pygame.draw.line(ventana, (0, 0, 255), dic[texto[k+4]], dic[texto[k+5]], 2)
	pygame.draw.line(ventana, (0, 0, 255), dic[texto[k+6]], dic[texto[k+7]], 2)

	#cont = cont + 1


cont = 1
texto = []
k = 0

while True:
	op = input("min/max: ")

	if(op == "max"):
		a, b, c, d, e, f, g, h, i = (21.49, 283.89), (30.00, 315.62), (49.34, 313.68), (63.61, 269.56), (64.59, 248.12), (54.28, 237.53), (33.80, 233.30), (25.76, 250.42), (20.55, 278.58) 
		ncrossings = 2169
		archivo = open("crossing_families/resultados/2k2-9max")
		break
	elif(op == "min"):
		a, b, c, d, e, f, g, h, i = (22.81, 69.02), (367.50, 556.10), (392.61, 456.74), (430.95, 295.28), (276.51, 199.70), (249.51, 163.52), (466.05, 195.65), (549.48, 185.93), (646.95, 99.26)
		ncrossings = 961
		archivo = open("crossing_families/resultados/2k2-9min")
		break

lee_archivo()

dic = {}

dic['a'] = a
dic['b'] = b
dic['c'] = c
dic['d'] = d
dic['e'] = e
dic['f'] = f
dic['g'] = g
dic['h'] = h
dic['i'] = i

pygame.init()
ventana = pygame.display.set_mode((700,700))
pygame.display.set_caption("2k2")

fuente = pygame.font.Font(None, 20)

mensaje = fuente.render(' ', 1, (0, 0, 0))

ventana.fill((255, 255, 255))
mensaje = fuente.render(str(cont), 1, (0, 0, 0))
dibuja(cont)
ventana.blit(mensaje, (15, 5))
pygame.display.flip()

while True:
	for event in pygame.event.get():
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_RIGHT and cont < ncrossings:
				cont += 1
				k += n
				dibuja(cont)
			elif event.key == pygame.K_LEFT and cont > 1:
				cont -= 1
				k -= n			
				dibuja(cont)
			elif event.key == K_ESCAPE:
				sys.exit(0)
		elif event.type == QUIT:
			pygame.quit()
			sys.exit()
		

	pygame.display.update()
