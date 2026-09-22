#ifndef PILA_H
#define PILA_H

#include "pieza.h"

struct NodoPila
{
	Pieza pieza;
	NodoPila *siguiente;
};

struct Pila
{
	NodoPila *tope;
	int cantidad;
};

void inicializarPila(Pila &pila);
void apilar(Pila &pila, Pieza pieza);
bool desapilar(Pila &pila, Pieza &pieza);
bool cimaPila(Pila &pila, Pieza &pieza);
bool pilaVacia(Pila &pila);
void limpiarPila(Pila &pila);
#endif
