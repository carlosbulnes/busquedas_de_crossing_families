#!/usr/bin/python3

import pygame, sys, os
from pygame.locals import *

ncrossings = 0
n = 1

def lee_archivo():
	for it in range(1, ncrossings+1):
		texto.append(archivo.read(17))

	#for it in range(0, ncrossings):
	#	print(it+1, texto[it])

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

	#print(texto[i][0], texto[i][1], texto[i][2], texto[i][3], texto[i][4], texto[i][5], texto[i][6], texto[i][7], texto[i][8], texto[i][9], texto[i][10], texto[i][11], texto[i][12], texto[i][13], texto[i][14], texto[i][15])
	print(i+1, texto[i])

	pygame.draw.circle(ventana, (0,0,0), a, 3)
	pygame.draw.circle(ventana, (0,0,0), b, 3)
	pygame.draw.circle(ventana, (0,0,0), c, 3)
	pygame.draw.circle(ventana, (0,0,0), d, 3)
	pygame.draw.circle(ventana, (0,0,0), e, 3)
	pygame.draw.circle(ventana, (0,0,0), f, 3)
	pygame.draw.circle(ventana, (0,0,0), g, 3)
	pygame.draw.circle(ventana, (0,0,0), h, 3)


	pygame.draw.line(ventana, (255, 0, 0), dic[texto[i][0]], dic[texto[i][1]], 1)
	pygame.draw.line(ventana, (255, 0, 0), dic[texto[i][2]], dic[texto[i][3]], 1)
	pygame.draw.line(ventana, (0, 0, 255), dic[texto[i][4]], dic[texto[i][5]], 1)
	pygame.draw.line(ventana, (0, 0, 255), dic[texto[i][6]], dic[texto[i][7]], 1)
	pygame.draw.line(ventana, (0, 255, 0), dic[texto[i][8]], dic[texto[i][9]], 1)
	pygame.draw.line(ventana, (0, 255, 0), dic[texto[i][10]], dic[texto[i][11]], 1)
	pygame.draw.line(ventana, (0, 0, 0), dic[texto[i][12]], dic[texto[i][13]], 1)
	pygame.draw.line(ventana, (0, 0, 0), dic[texto[i][14]], dic[texto[i][15]], 1)

	#cont = cont + 1


cont = 1
texto = []
i = 0

#while True:
	#op = input("min/max: ")

	#if(op == "max"):
a, b, c, d, e, f, g, h = (218*2, 48*2), (157*2, 54*2), (88*2, 66*2), (76*2, 72*2), (61*2, 90*2), (13*2, 177*2), (55*2, 210*2), (243*2, 53*2)
ncrossings = 120
archivo = open("logK2-8")
#		break
#	elif(op == "min"):
#		a, b, c, d, e, f, g, h = (236, 23), (53, 149), (123, 175), (149, 161), (201, 90), (179, 152), (167, 214), (180, 233)
#		ncrossings = 103
#		archivo = open("crossing_families/resultados/2k2-8min")
#		break

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
ventana = pygame.display.set_mode((600,600))
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
