#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics.hpp>
#include "cola.h"
#include "pila.h"
#include "tablero.h"
#include "eventos.h"
using namespace sf;
using namespace std;

void hacerHold(Cola &cola, Pila &pilaHold, Pieza &piezaActual);
void procesarNivel(ColaEventos &eventos, int lineasTotales, int &proximoNivel);
void procesarEventos(ColaEventos &eventos, int &nivel, float &velocidadCaida, int &puntaje, bool &nuevoRecord);
void procesarLineas(ColaEventos &eventos, int filasEliminadas, int &puntaje, int &lineasTotales);
void procesarBonus(ColaEventos &eventos, int filasEliminadas);
void procesarPiezaTerminada(Tablero &tablero, Cola &cola, Pieza &piezaActual, ColaEventos &eventos, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, 
							float &velocidadCaida, bool &gameOver, bool &nuevoRecord);
void procesarTecla(Keyboard::Key tecla, Tablero &tablero, Cola &cola, Pila &pilaHold, Pieza &piezaActual);
void procesarCaida(Tablero &tablero, Cola &cola, Pieza &piezaActual, ColaEventos &eventos, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, float &velocidadCaida, bool &gameOver,
				   bool &nuevoRecord);
int obtenerRecord();
void procesarRecord(ColaEventos &eventos, int puntaje);
#endif
