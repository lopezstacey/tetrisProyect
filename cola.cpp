#include "cola.h"
#include <cstdlib>

void inicializarCola(Cola &cola)
{
	cola.frente = nullptr;
	cola.final = nullptr;
	cola.cantidad = 0;
}

void encolar(Cola &cola, Pieza pieza)
{
	NodoCola *nuevo = new NodoCola;
	
	nuevo->pieza = pieza;
	nuevo->siguiente = nullptr;
	
	if (cola.frente == nullptr)
	{
		cola.frente = nuevo;
		cola.final = nuevo;
	}
	else
	{
		cola.final->siguiente = nuevo;
		cola.final = nuevo;
	}
	
	cola.cantidad++;
}

bool desencolar(Cola &cola, Pieza &pieza)
{
	if (cola.frente == nullptr)
	{
		return false;
	}
	
	NodoCola *auxiliar = cola.frente;
	
	pieza = auxiliar->pieza;
	
	cola.frente = auxiliar->siguiente;
	
	if (cola.frente == nullptr)
	{
		cola.final = nullptr;
	}
	
	delete auxiliar;
	
	cola.cantidad--;
	
	return true;
}

bool frenteCola(Cola &cola, Pieza &pieza)
{
	if (cola.frente == nullptr)
	{
		return false;
	}
	
	pieza = cola.frente->pieza;
	
	return true;
}

void generarBag(Cola &cola)
{
	char tipos[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
	mezclarTipos(tipos);
	for (int i = 0; i < 7; i++)
	{
		Pieza pieza;
		
		inicializarPieza(pieza, tipos[i]);
		
		encolar(cola, pieza);
	}
}

int cantidadCola(Cola &cola)
{
	return cola.cantidad;
}

void mantenerCola(Cola &cola)
{
	if (cantidadCola(cola) <= 3)
	{
		generarBag(cola);
	}
}

void mezclarTipos(char tipos[])
{
	for (int i = 6; i > 0; i--)
	{
		int posicion = rand() % (i + 1);
		
		char temporal = tipos[i];
		tipos[i] = tipos[posicion];
		tipos[posicion] = temporal;
	}
}

bool obtenerPieza(Cola &cola, int posicion, Pieza &pieza)
{
	if (posicion < 0 || posicion >= cola.cantidad)
	{
		return false;
	}
	
	NodoCola *actual = cola.frente;
	
	for (int i = 0; i < posicion; i++)
	{
		actual = actual->siguiente;
	}
	
	pieza = actual->pieza;
	
	return true;
}
