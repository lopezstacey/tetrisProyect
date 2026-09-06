#ifndef COLA_H
#define COLA_H

#include "pieza.h"

struct NodoCola
{
	Pieza pieza;
	NodoCola *siguiente;
};

struct Cola
{
	NodoCola *frente;
	NodoCola *final;
	int cantidad;
};

void inicializarCola(Cola &cola);
void encolar(Cola &cola, Pieza pieza);
bool desencolar(Cola &cola, Pieza &pieza);
bool frenteCola(Cola &cola, Pieza &pieza);
void generarBag(Cola &cola);
int cantidadCola(Cola &cola);
void mantenerCola(Cola &cola);
void mezclarTipos(char tipos[]);
#endif
