#ifndef JUEGO_H
#define JUEGO_H
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "cola.h"
#include "pila.h"
#include "tablero.h"
#include "eventos.h"
#include "replay.h"

using namespace sf;
using namespace std;

void hacerHold(Cola &cola, Pila &pilaHold, Pieza &piezaActual);
void procesarNivel(ColaEventos &eventos, int lineasTotales, int &proximoNivel);
void procesarEventos(ColaEventos &eventos, int &nivel, float &velocidadCaida, int &puntaje, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo);
void procesarLineas(ColaEventos &eventos, int filasEliminadas, int &puntaje, int &lineasTotales);
void procesarBonus(ColaEventos &eventos, int filasEliminadas, int &puntaje, bool bonusActivo);
void procesarTableroPeligro(ColaEventos &eventos, int lineasTotales, bool &tableroPeligroActivo);
void procesarPiezaTerminada(Tablero &tablero, Cola &cola, Pila &pilaHold, Pieza &piezaActual, ColaEventos &eventos, ListaReplay &replay, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, float &velocidadCaida, bool &gameOver, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo, string nombreJugador);
void procesarTecla(Keyboard::Key tecla, Tablero &tablero, Cola &cola, Pila &pilaHold, Pieza &piezaActual, ListaReplay &replay, int &puntaje, int &nivel);
void procesarCaida(Tablero &tablero, Cola &cola, Pieza &piezaActual, ColaEventos &eventos, Pila &pilaHold, ListaReplay &replay, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, float &velocidadCaida, bool &gameOver, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo, string nombreJugador);
void cargarPuntajes(string nombres[], int puntajes[], int &cantidad);
void guardarPuntajes(string nombres[], int puntajes[], int cantidad);
void insertarPuntaje(string nombre, int puntaje, string nombres[], int puntajes[], int &cantidad);
void ordenarPuntajes(string nombres[], int puntajes[], int cantidad);
void ordenarPuntajesMerge(string nombres[], int puntajes[], int cantidad);
void procesarRecord(ColaEventos &eventos, string nombre, int puntaje);
void guardarEstadoActualReplay(ListaReplay &replay, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int puntaje, int nivel);
void restaurarEstadoReplay(EstadoReplay estado, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int &puntaje, int &nivel);
void prepararReplay(ListaReplay &replay, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int &puntaje, int &nivel);
bool avanzarReplayVisual(ListaReplay &replay, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int &puntaje, int &nivel);
bool retrocederReplayVisual(ListaReplay &replay, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int &puntaje, int &nivel);
void reiniciarPartida(Tablero &tablero, Cola &cola, Pila &pilaHold, ColaEventos &eventos, ListaReplay &replay, Pieza &piezaActual, int &puntaje, int &lineasTotales, int &nivel, int &proximoNivel, float &velocidadCaida, bool &gameOver, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo);
#endif
