#include "pila.h"

void inicializarPila(Pila &pila)
{
	pila.tope = nullptr;
	pila.cantidad = 0;
}

void apilar(Pila &pila, Pieza pieza)
{
	NodoPila *nuevo = new NodoPila;
	
	nuevo->pieza = pieza;
	nuevo->siguiente = pila.tope;
	
	pila.tope = nuevo;
	pila.cantidad++;
}

bool desapilar(Pila &pila, Pieza &pieza)
{
	if (pila.tope == nullptr)
	{
		return false;
	}
	
	NodoPila *auxiliar = pila.tope;
	
	pieza = auxiliar->pieza;
	
	pila.tope = auxiliar->siguiente;
	
	delete auxiliar;
	
	pila.cantidad--;
	
	return true;
}

bool cimaPila(Pila &pila, Pieza &pieza)
{
	if (pila.tope == nullptr)
	{
		return false;
	}
	
	pieza = pila.tope->pieza;
	
	return true;
}

bool pilaVacia(Pila &pila)
{
	return pila.tope == nullptr;
}
