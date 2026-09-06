#include <iostream>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "pieza.h"
#include "cola.h"
#include "tablero.h"

using namespace std;
using namespace sf;

Color colorPieza(char tipo)
{
	if (tipo == 'I')
		return Color(150, 200, 210);
	
	if (tipo == 'O')
		return Color(210, 190, 150);
	
	if (tipo == 'T')
		return Color(180, 160, 200);
	
	if (tipo == 'S')
		return Color(150, 180, 150);
	
	if (tipo == 'Z')
		return Color(130, 60, 75);
	
	if (tipo == 'J')
		return Color(150, 150, 155);
	
	if (tipo == 'L')
		return Color(225, 210, 175);
	
	return Color(255, 255, 255);
}

void dibujarPieza(RenderWindow &ventana, Pieza &pieza, int posX, int posY)
{
	const int TAMANO_CELDA = 30;
	
	for (int bloque = 0; bloque < 4; bloque++)
	{
		int x = pieza.bloques[pieza.orientacion][bloque][0];
		int y = pieza.bloques[pieza.orientacion][bloque][1];
		
		RectangleShape celda(
							 Vector2f(TAMANO_CELDA - 2, TAMANO_CELDA - 2)
							 );
		
		celda.setPosition(
						  posX + x * TAMANO_CELDA,
						  posY + y * TAMANO_CELDA
						  );
		
		celda.setFillColor(colorPieza(pieza.tipo));
		
		ventana.draw(celda);
	}
}

void dibujarPanelSiguientes(RenderWindow &ventana)
{
	RectangleShape panel(Vector2f(250, 500));
	panel.setPosition(500, 80);
	panel.setFillColor(Color(25, 25, 25));
	ventana.draw(panel);
}

void dibujarSiguientes(RenderWindow &ventana, Cola &cola)
{
	Pieza pieza;
	
	for (int i = 1; i <= 3; i++)
	{
		if (obtenerPieza(cola, i, pieza))
		{
			dibujarPieza(
						 ventana,
						 pieza,
						 550,
						 130 + (i - 1) * 150
						 );
		}
	}
}

void dibujarTablero(RenderWindow &ventana, Tablero &tablero, Pieza &piezaActual)
{
	const int TAMANO_CELDA = 30;
	const int POS_X = 50;
	const int POS_Y = 50;
	
	for (int fila = 0; fila < 20; fila++)
	{
		NodoFila *nodo = obtenerFila(tablero, fila);
		
		for (int columna = 0; columna < 10; columna++)
		{
			RectangleShape celda(
								 Vector2f(TAMANO_CELDA - 1, TAMANO_CELDA - 1)
								 );
			
			celda.setPosition(
							  POS_X + columna * TAMANO_CELDA,
							  POS_Y + fila * TAMANO_CELDA
							  );
			
			if (nodo->celdas[columna] == 0)
			{
				celda.setFillColor(Color(15, 15, 15));
			}
			else
			{
				celda.setFillColor(colorPieza(piezaActual.tipo));
			}
			
			ventana.draw(celda);
		}
	}
}

int main()
{
	srand(time(nullptr));
	
	Cola cola;
	inicializarCola(cola);
	
	generarBag(cola);
	
	Tablero tablero;
	inicializarTablero(tablero);
	Pieza piezaActual;
	obtenerPieza(cola,0, piezaActual);
	
	Clock reloj;
	
	RenderWindow ventana(
						 VideoMode(800, 700),
						 "Tetris"
						 );
	
	while (ventana.isOpen())
	{
		Event evento;
		
		while (ventana.pollEvent(evento))
		{
			if (evento.type == Event::Closed)
			{
				ventana.close();
			}
			if (evento.type == Event::KeyPressed)
			{
				if (evento.key.code == Keyboard::Left)
				{
					moverPiezaHorizontal(tablero, piezaActual, -1);
				}
				
				if (evento.key.code == Keyboard::Right)
				{
					moverPiezaHorizontal(tablero, piezaActual, 1);
				}
				if (evento.key.code == Keyboard::Up)
				{
					if (puedeRotarPieza(tablero, piezaActual))
					{
						rotarPieza(piezaActual);
					}
				}
			}
		}
		
		if (reloj.getElapsedTime().asSeconds() >= 0.5)
		{
			if (!moverPiezaAbajo(tablero, piezaActual))
			{
				fijarPieza(tablero, piezaActual);
				
				eliminarFilasCompletas(tablero);
				
				Pieza piezaFijada;
				desencolar(cola, piezaFijada);
				
				mantenerCola(cola);
				
				obtenerPieza(cola, 0, piezaActual);
			}
			
			reloj.restart();
		}
		
		ventana.clear();
		dibujarTablero(ventana, tablero, piezaActual);
		dibujarPieza(
					 ventana,
					 piezaActual,
					 50 + piezaActual.columna * 30,
					 50 + piezaActual.fila * 30
					 );
		dibujarPanelSiguientes(ventana);
		dibujarSiguientes(ventana, cola);
		
		
		ventana.display();
	}
	
	return 0;
}
