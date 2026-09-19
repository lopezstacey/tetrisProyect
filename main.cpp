#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "pieza.h"
#include "cola.h"
#include "pila.h"
#include "tablero.h"
#include "interfaz.h"
#include "eventos.h"
#include "juego.h"

using namespace std;
using namespace sf;

Font fuente;
Texture texturaFondo;
Sprite spriteFondo;

int puntaje = 0;
bool gameOver = false;
int lineasTotales = 0;
float velocidadCaida = 0.5;
int nivel = 1;
int proximoNivel = 5;
bool nuevoRecord = false;

int main()
{
	srand(time(0));
	
	if (!fuente.loadFromFile("assets/times.ttf"))
	{
		return 1;
	}
	
	if (!texturaFondo.loadFromFile("assets/fondo.png"))
	{
		return 1;
	}
	
	spriteFondo.setTexture(texturaFondo);
	float escalaX = (float)ANCHO_VENTANA / texturaFondo.getSize().x;
	float escalaY = (float)ALTO_VENTANA / texturaFondo.getSize().y;
	spriteFondo.setScale(escalaX, escalaY);
	
	Tablero tablero;
	Cola cola;
	Pila pilaHold;
	ColaEventos eventos;
	
	inicializarTablero(tablero);
	inicializarCola(cola);
	inicializarPila(pilaHold);
	inicializarEventos(eventos);
	
	generarBag(cola);
	generarBag(cola);
	
	Pieza piezaActual;
	obtenerPieza(cola, 0, piezaActual);
	
	if (!puedeColocarPieza(tablero, piezaActual))
	{
		gameOver = true;
	}
	
	RenderWindow ventana(VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "Tetris");
	ventana.setFramerateLimit(60);
	Clock reloj;
	
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
				if (evento.key.code == Keyboard::Escape)
				{
					ventana.close();
				}
				
				if (!gameOver)
				{
					procesarTecla(evento.key.code, tablero, cola, pilaHold, piezaActual);
				}
			}
		}
		
		if (!gameOver && reloj.getElapsedTime().asSeconds() >= velocidadCaida)
		{
			procesarCaida(tablero, cola, piezaActual, eventos, puntaje, lineasTotales, proximoNivel, nivel, velocidadCaida, gameOver,nuevoRecord);
			reloj.restart();
		}
		
		ventana.clear();
		dibujarFondo(ventana);
		dibujarMarcoTablero(ventana);
		dibujarTablero(ventana, tablero, piezaActual);
		dibujarPieza(ventana, piezaActual, TABLERO_X + piezaActual.columna * TAMANO_CELDA, TABLERO_Y + piezaActual.fila * TAMANO_CELDA);
		dibujarPanelHold(ventana);
		dibujarPanelSiguientes(ventana);
		dibujarPanelPuntaje(ventana);
		dibujarPanelControles(ventana);
		dibujarHold(ventana, pilaHold);
		dibujarSiguientes(ventana, cola);
		
		if (gameOver)
		{
			dibujarGameOver(ventana);
		}
		
		ventana.display();
	}
	
	return 0;
}
