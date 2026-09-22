#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "pieza.h"
#include "cola.h"
#include "pila.h"
#include "tablero.h"
#include "interfaz.h"
#include "eventos.h"
#include "juego.h"
#include "replay.h"

using namespace std;
using namespace sf;

Font fuente;
Texture texturaFondo;
Sprite spriteFondo;
Texture texturaInicio;
Sprite spriteInicio;

bool gameOver = false;
bool modoReplay = false;
bool nuevoRecord = false;
bool reproduciendoReplay = false;
bool portada = true;
bool bonusActivo = false;
bool tableroPeligroActivo = false;
bool pantallaNombre = false;
bool pantallaPuntajes = false;
bool pantallaSeleccionOrdenamiento = false;
bool pantallaComoJugar = false;
bool pantallaInformacion = false;
bool pausado = false;

string nombreJugador = "";
string nombresPuntajes[10];
int puntajes[10];
int cantidadPuntajes = 0;
int lineasTotales = 0;
int puntaje = 0;
int nivel = 1;
int proximoNivel = 5;
float velocidadCaida = 0.5f;
double tiempoOrdenamiento = 0.0;

int main()
{
	srand(time(0));
	
	if (!fuente.loadFromFile("assets/times.ttf")) return 1;
	if (!texturaFondo.loadFromFile("assets/fondo.png")) return 1;
	if (!texturaInicio.loadFromFile("assets/inicio.png")) return 1;
	
	spriteFondo.setTexture(texturaFondo);
	spriteInicio.setTexture(texturaInicio);
	
	Cola cola;
	Pila pilaHold;
	Tablero tablero;
	ColaEventos eventos;
	ListaReplay replay;
	Pieza piezaActual;
	
	inicializarCola(cola);
	inicializarPila(pilaHold);
	inicializarTablero(tablero);
	inicializarEventos(eventos);
	inicializarReplay(replay);
	
	cargarPuntajes(nombresPuntajes, puntajes, cantidadPuntajes);
	reiniciarPartida(tablero, cola, pilaHold, eventos, replay, piezaActual, puntaje, lineasTotales, nivel, proximoNivel, velocidadCaida, gameOver, nuevoRecord, bonusActivo, tableroPeligroActivo);
	
	RenderWindow ventana(VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "Tetris");
	ventana.setFramerateLimit(60);
	
	Clock relojCaida;
	Clock relojReplay;
	
	while (ventana.isOpen())
	{
		Event evento;
		
		while (ventana.pollEvent(evento))
		{
			if (evento.type == Event::Closed)
			{
				ventana.close();
			}
			
			if (evento.type == Event::TextEntered && pantallaNombre)
			{
				if (evento.text.unicode == 8 && !nombreJugador.empty())
				{
					nombreJugador.pop_back();
				}
				else if (evento.text.unicode >= 32 && evento.text.unicode <= 126 && nombreJugador.length() < 15)
				{
					nombreJugador += static_cast<char>(evento.text.unicode);
				}
			}
			
			if (evento.type == Event::KeyPressed)
			{
				if (portada)
				{
					if (evento.key.code == Keyboard::Escape)
					{
						ventana.close();
					}
				}
				else if (pantallaNombre)
				{
					if (evento.key.code == Keyboard::Escape)
					{
						pantallaNombre = false;
						portada = true;
						nombreJugador = "";
					}
				}
				else if (pantallaSeleccionOrdenamiento || pantallaPuntajes || pantallaComoJugar || pantallaInformacion)
				{
					if (evento.key.code == Keyboard::Escape)
					{
						pantallaSeleccionOrdenamiento = false;
						pantallaPuntajes = false;
						portada = true;
					}
				}
				else if (gameOver)
				{
					if (evento.key.code == Keyboard::Escape)
					{
						gameOver = false;
						modoReplay = false;
						reproduciendoReplay = false;
						pausado = false;
						pantallaNombre = false;
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
						portada = true;
					}
				}
				else if (modoReplay)
				{
					if (evento.key.code == Keyboard::A)
					{
						retrocederReplayVisual(replay, tablero, piezaActual, pilaHold, puntaje, nivel);
						reproduciendoReplay = false;
					}
					
					if (evento.key.code == Keyboard::D)
					{
						avanzarReplayVisual(replay, tablero, piezaActual, pilaHold, puntaje, nivel);
						reproduciendoReplay = false;
					}
					
					if (evento.key.code == Keyboard::Space)
					{
						if (!reproduciendoReplay && replay.actual == replay.ultima)
						{
							prepararReplay(replay, tablero, piezaActual, pilaHold, puntaje, nivel);
						}
						
						reproduciendoReplay = !reproduciendoReplay;
						relojReplay.restart();
					}
				}
				else if (!pausado)
				{
					procesarTecla(evento.key.code, tablero, cola, pilaHold, piezaActual, replay, puntaje, nivel);
					
					if (evento.key.code == Keyboard::Space)
					{
						while (moverPiezaAbajo(tablero, piezaActual)) {}
						
						procesarPiezaTerminada(tablero, cola, pilaHold, piezaActual, eventos, replay, puntaje, lineasTotales, proximoNivel, nivel, velocidadCaida, gameOver, nuevoRecord, bonusActivo, tableroPeligroActivo, nombreJugador);
						
						relojCaida.restart();
					}
				}
			}
			
			if (evento.type == Event::MouseButtonPressed && evento.mouseButton.button == Mouse::Left)
			{
				int x = evento.mouseButton.x;
				int y = evento.mouseButton.y;
				
				if (portada)
				{
					if (botonInicioPresionado(x, y))
					{
						portada = false;
						pantallaNombre = true;
						pantallaPuntajes = false;
						pantallaComoJugar = false;
						pantallaSeleccionOrdenamiento = false;
						nombreJugador = "";
					}
					else if (botonPuntajesPresionado(x, y))
					{
						cargarPuntajes(nombresPuntajes, puntajes, cantidadPuntajes);
						portada = false;
						pantallaNombre = false;
						pantallaPuntajes = false;
						pantallaComoJugar = false;
						pantallaSeleccionOrdenamiento = true;
					}
					else if (botonComoJugarPresionado(x, y))
					{
						portada = false;
						pantallaComoJugar = true;
						pantallaNombre = false;
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
					}
					else if (botonInformacionPresionado(x, y))
					{
						portada = false;
						pantallaInformacion = true;
						pantallaComoJugar = false;
						pantallaNombre = false;
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
					}
					else if (botonSalirPortadaPresionado(x, y))
					{
						ventana.close();
					}
				}
				else if (pantallaNombre)
				{
					if (botonJugarNombrePresionado(x, y))
					{
						if (nombreJugador.empty())
						{
							nombreJugador = "Jugador";
						}
						
						reiniciarPartida(tablero, cola, pilaHold, eventos, replay, piezaActual, puntaje, lineasTotales, nivel, proximoNivel, velocidadCaida, gameOver, nuevoRecord, bonusActivo, tableroPeligroActivo);
						
						pantallaNombre = false;
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
						portada = false;
						modoReplay = false;
						reproduciendoReplay = false;
						pausado = false;
						
						relojCaida.restart();
					}
					else if (botonRegresarPresionado(x, y, 500, 535))
					{
						pantallaNombre = false;
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
						portada = true;
						nombreJugador = "";
						pausado = false;
					}
				}
				else if (pantallaComoJugar)
				{
					if (botonRegresarPresionado(x, y, 500, 750))
					{
						pantallaComoJugar = false;
						portada = true;
					}
				}
				else if (pantallaInformacion)
				{
					if (botonRegresarPresionado(x, y, 500, 750))
					{
						pantallaInformacion = false;
						portada = true;
					}
				}
				else if (pantallaSeleccionOrdenamiento)
				{
					if (botonInsertionSortPresionado(x, y))
					{
						cargarPuntajes(nombresPuntajes, puntajes, cantidadPuntajes);
						auto inicioOrdenamiento = chrono::high_resolution_clock::now();
						ordenarPuntajes(nombresPuntajes, puntajes, cantidadPuntajes);
						auto finOrdenamiento = chrono::high_resolution_clock::now();
						tiempoOrdenamiento = chrono::duration<double, micro>(finOrdenamiento - inicioOrdenamiento).count();
						pantallaSeleccionOrdenamiento = false;
						pantallaPuntajes = true;
					}
					else if (botonMergeSortPresionado(x, y))
					{
						cargarPuntajes(nombresPuntajes, puntajes, cantidadPuntajes);
						auto inicioOrdenamiento = chrono::high_resolution_clock::now();
						ordenarPuntajesMerge(nombresPuntajes, puntajes, cantidadPuntajes);
						auto finOrdenamiento = chrono::high_resolution_clock::now();
						tiempoOrdenamiento = chrono::duration<double, micro>(finOrdenamiento - inicioOrdenamiento).count();
						pantallaSeleccionOrdenamiento = false;
						pantallaPuntajes = true;
					}
					else if (botonRegresarPresionado(x, y, 500, 750))
					{
						pantallaSeleccionOrdenamiento = false;
						pantallaPuntajes = false;
						portada = true;
					}
				}
				else if (pantallaPuntajes)
				{
					if (botonRegresarPresionado(x, y, 500, 750))
					{
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
						portada = true;
					}
				}
				else if (gameOver)
				{
					if (botonReplayPresionado(x, y))
					{
						cargarPuntajes(nombresPuntajes, puntajes, cantidadPuntajes);
						prepararReplay(replay, tablero, piezaActual, pilaHold, puntaje, nivel);
						gameOver = false;
						modoReplay = true;
						reproduciendoReplay = false;
						pausado = false;
						pantallaNombre = false;
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
						portada = false;
					}
					else if (botonRegresarPresionado(x, y, 630, 460))
					{
						cargarPuntajes(nombresPuntajes, puntajes, cantidadPuntajes);
						gameOver = false;
						modoReplay = false;
						reproduciendoReplay = false;
						pausado = false;
						pantallaNombre = false;
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
						portada = true;
					}
				}
				else if (modoReplay)
				{
					if (botonRegresarReplayPresionado(x, y))
					{
						modoReplay = false;
						reproduciendoReplay = false;
						gameOver = false;
						pausado = false;
						pantallaPuntajes = false;
						pantallaSeleccionOrdenamiento = false;
						portada = true;
					}
				}
				else if (!modoReplay && !gameOver)
				{
					if (botonPausaPresionado(x, y))
					{
						pausado = !pausado;
						relojCaida.restart();
					}
				}
			}
		}
		
		if (!portada && !pantallaNombre && !pantallaSeleccionOrdenamiento && !pantallaPuntajes && !gameOver && !modoReplay && !pausado)
		{
			if (relojCaida.getElapsedTime().asSeconds() >= velocidadCaida)
			{
				procesarCaida(tablero, cola, piezaActual, eventos, pilaHold, replay, puntaje, lineasTotales, proximoNivel, nivel, velocidadCaida, gameOver, nuevoRecord, bonusActivo, tableroPeligroActivo, nombreJugador);
				relojCaida.restart();
				
				if (gameOver)
				{
					cargarPuntajes(nombresPuntajes, puntajes, cantidadPuntajes);
				}
			}
		}
		
		if (modoReplay && reproduciendoReplay)
		{
			if (relojReplay.getElapsedTime().asSeconds() >= 0.15f)
			{
				if (!avanzarReplayVisual(replay, tablero, piezaActual, pilaHold, puntaje, nivel))
				{
					reproduciendoReplay = false;
				}
				
				relojReplay.restart();
			}
		}
		
		ventana.clear();
		
		if (portada)
		{
			dibujarPortada(ventana);
		}
		else if (pantallaNombre)
		{
			dibujarNombreJugador(ventana, nombreJugador);
		}
		else if (pantallaComoJugar)
		{
			dibujarComoJugar(ventana);
		}
		else if (pantallaInformacion)
		{
			dibujarInformacion(ventana);
		}
		else if (pantallaSeleccionOrdenamiento)
		{
			dibujarSeleccionOrdenamiento(ventana);
		}
		else if (pantallaPuntajes)
		{
			dibujarPuntajes(ventana, nombresPuntajes, puntajes, cantidadPuntajes);
		}
		else
		{
			dibujarFondo(ventana);
			dibujarMarcoTablero(ventana);
			dibujarTablero(ventana, tablero, piezaActual, tableroPeligroActivo);
			dibujarPanelHold(ventana);
			dibujarPanelSiguientes(ventana);
			dibujarPanelPuntaje(ventana);
			dibujarPanelControles(ventana, modoReplay);
			
			if (!modoReplay && !gameOver)
			{
				dibujarBotonPausa(ventana, pausado);
			}
			
			dibujarHold(ventana, pilaHold);
			dibujarSiguientes(ventana, cola);
			
			if (gameOver)
			{
				dibujarGameOver(ventana);
			}
			
			if (modoReplay)
			{
				dibujarBotonRegresarReplay(ventana);
			}
		}
		
		ventana.display();
	}
	
	limpiarTablero(tablero);
	limpiarReplay(replay);
	
	return 0;
}
