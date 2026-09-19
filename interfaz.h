#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SFML/Graphics.hpp>

#include "pieza.h"
#include "cola.h"
#include "pila.h"
#include "tablero.h"

using namespace sf;
using namespace std;

const int ANCHO_VENTANA = 1200;
const int ALTO_VENTANA = 900;
const int TAMANO_CELDA = 30;
const int TABLERO_X = 100;
const int TABLERO_Y = 120;
const int PANEL_X = 600;
const int HOLD_Y = 100;
const int SIGUIENTES_Y = 250;
const int PUNTAJE_Y = 610;
const int CONTROLES_Y = 710;

extern Font fuente;
extern Texture texturaFondo;
extern Sprite spriteFondo;
extern int puntaje;
extern bool gameOver;
extern int nivel;

void dibujarPieza(RenderWindow &ventana, Pieza &pieza, int posX, int posY);
void dibujarFondo(RenderWindow &ventana);
void dibujarTexto(RenderWindow &ventana, string texto, int x, int y, int tamano);
void dibujarMarcoTablero(RenderWindow &ventana);
void dibujarPanelHold(RenderWindow &ventana);
void dibujarPanelSiguientes(RenderWindow &ventana);
void dibujarPanelPuntaje(RenderWindow &ventana);
void dibujarPanelControles(RenderWindow &ventana);
void dibujarSiguientes(RenderWindow &ventana, Cola &cola);
void dibujarHold(RenderWindow &ventana, Pila &pilaHold);
void dibujarTablero(RenderWindow &ventana, Tablero &tablero, Pieza &piezaActual);
void dibujarGameOver(RenderWindow &ventana);

#endif
