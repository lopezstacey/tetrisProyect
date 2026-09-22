#ifndef REPLAY_H
#define REPLAY_H

#include "pieza.h"

struct EstadoReplay
{
	int celdas[20][10];
	Pieza piezaActual;
	Pieza piezaHold;
	bool tieneHold;
	int puntaje;
	int nivel;
};

struct NodoReplay
{
	EstadoReplay estado;
	NodoReplay *siguiente;
	NodoReplay *anterior;
};

struct ListaReplay
{
	NodoReplay *primera;
	NodoReplay *ultima;
	NodoReplay *actual;
	int posicion;
	int cantidad;
};

void inicializarReplay(ListaReplay &lista);
void guardarEstadoReplay(ListaReplay &lista, EstadoReplay estado);
void iniciarReplay(ListaReplay &lista);
bool avanzarReplay(ListaReplay &lista, EstadoReplay &estado);
bool retrocederReplay(ListaReplay &lista, EstadoReplay &estado);
void limpiarReplay(ListaReplay &lista);

#endif
