#!/usr/bin/python3

import pygame, sys, os
from pygame.locals import *

ncrossings = 0
n = 8

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
		archivo.read(1)

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
	ventana.blit(mensajea, a)
	ventana.blit(mensajeb, b)
	ventana.blit(mensajec, c)
	ventana.blit(mensajed, d)
	ventana.blit(mensajee, e)
	ventana.blit(mensajef, f)
	ventana.blit(mensajeg, g)
	ventana.blit(mensajeh, h)
	ventana.blit(mensaje, (15, 5))			
	
	pygame.display.flip()

	print(texto[i], texto[i+1], texto[i+2], texto[i+3], texto[i+4], texto[i+5], texto[i+6], texto[i+7])

	pygame.draw.circle(ventana, (0,0,0), a, 3)
	pygame.draw.circle(ventana, (0,0,0), b, 3)
	pygame.draw.circle(ventana, (0,0,0), c, 3)
	pygame.draw.circle(ventana, (0,0,0), d, 3)
	pygame.draw.circle(ventana, (0,0,0), e, 3)
	pygame.draw.circle(ventana, (0,0,0), f, 3)
	pygame.draw.circle(ventana, (0,0,0), g, 3)
	pygame.draw.circle(ventana, (0,0,0), h, 3)

	pygame.draw.line(ventana, (255, 0, 0), dic[texto[i]], dic[texto[i+1]], 2)
	pygame.draw.line(ventana, (255, 0, 0), dic[texto[i+2]], dic[texto[i+3]], 2)
	pygame.draw.line(ventana, (0, 0, 255), dic[texto[i+4]], dic[texto[i+5]], 2)
	pygame.draw.line(ventana, (0, 0, 255), dic[texto[i+6]], dic[texto[i+7]], 2)

	#cont = cont + 1


cont = 1
texto = []
i = 0

while True:
	op = input("min/max: ")

	if(op == "max"):
		a, b, c, d, e, f, g, h = (218, 48), (157, 54), (88, 66), (76, 72), (61, 90), (13, 177), (55, 210), (243, 53)
		ncrossings = 241
		archivo = open("crossing_families/resultados/2k2-8max")
		break
	elif(op == "min"):
		a, b, c, d, e, f, g, h = (236, 23), (53, 149), (123, 175), (149, 161), (201, 90), (179, 152), (167, 214), (180, 233)
		ncrossings = 103
		archivo = open("crossing_families/resultados/2k2-8min")
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

pygame.init()
ventana = pygame.display.set_mode((300,300))
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
				i += n
				dibuja(cont)
			elif event.key == pygame.K_LEFT and cont > 1:
				cont -= 1
				i -= n			
				dibuja(cont)
			elif event.key == K_ESCAPE:
				sys.exit(0)
		elif event.type == QUIT:
			pygame.quit()
			sys.exit()
		

	pygame.display.update()
