#!/usr/bin/python3

import pygame, sys, os
from pygame.locals import *

ncrossings = 0
n = 10

def lee_archivo():
	for i in range(1, ncrossings+1):
		texto.append(archivo.read(9))

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
	mensajej = fuente.render('j', 1, (0, 0, 0))
	ventana.blit(mensajea, a)
	ventana.blit(mensajeb, b)
	ventana.blit(mensajec, c)
	ventana.blit(mensajed, d)
	ventana.blit(mensajee, e)
	ventana.blit(mensajef, f)
	ventana.blit(mensajeg, g)
	ventana.blit(mensajeh, h)
	ventana.blit(mensajei, i)
	ventana.blit(mensajej, j)
	ventana.blit(mensaje, (15, 5))			
	
	pygame.display.flip()

	print(texto[k][0], texto[k][1], texto[k][2], texto[k][3], texto[k][4], texto[k][5], texto[k][6], texto[k][7])

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
	pygame.draw.line(ventana, (255, 0, 0), dic[texto[k][0]], dic[texto[k][1]], 2)
	pygame.draw.line(ventana, (255, 0, 0), dic[texto[k][2]], dic[texto[k][3]], 2)
	pygame.draw.line(ventana, (0, 0, 255), dic[texto[k][4]], dic[texto[k][5]], 2)
	pygame.draw.line(ventana, (0, 0, 255), dic[texto[k][6]], dic[texto[k][7]], 2)

	#cont = cont + 1


cont = 1
texto = []
k = 0

while True:
	op = input("min/max: ")

	if(op == "max"):
		a, b, c, d, e, f, g, h, i, j = (5.26, 335.69), (13.16, 354.13), (132.30, 576.24), (403.06, 562.66), (602.84, 253.82), (616.56, 103.74), (472.22, 29.61), (185.50, 0), (72.94, 119.84), (0, 316.96)
		ncrossings = 10845
		archivo = open("crossing_families/resultados/2k2-10max")
		break
	elif(op == "min"):
		a, b, c, d, e, f, g, h, i, j = (0, 0), (154.08, 622.20), (177.39, 509.90), (175.68, 492.66), (105.48, 207.06), (77.58, 111.18), (220.86, 196.86), (377.46, 287.30), (501.66, 168.30), (632.52, 151.64)
		ncrossings = 4905
		archivo = open("crossing_families/resultados/2k2-10min")
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
dic['j'] = j

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
