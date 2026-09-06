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
	
	if (obtenerPieza(cola, 0, piezaActual))
	{
		colocarPieza(tablero, piezaActual);
	}
	
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
		}
		
		ventana.clear();
		dibujarTablero(ventana, tablero, piezaActual);
		ventana.display();
	}
	
	return 0;
}
