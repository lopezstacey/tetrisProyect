#include "replay.h"

void inicializarReplay(ListaReplay &lista)
{
	lista.primera = nullptr;
	lista.ultima = nullptr;
	lista.actual = nullptr;
	lista.posicion = -1;
	lista.cantidad = 0;
}

void guardarEstadoReplay(ListaReplay &lista, EstadoReplay estado)
{
	NodoReplay *nuevo = new NodoReplay;
	
	nuevo->estado = estado;
	nuevo->siguiente = nullptr;
	nuevo->anterior = lista.ultima;
	
	if (lista.ultima == nullptr)
	{
		lista.primera = nuevo;
		lista.ultima = nuevo;
	}
	else
	{
		lista.ultima->siguiente = nuevo;
		lista.ultima = nuevo;
	}
	
	lista.cantidad++;
}

void iniciarReplay(ListaReplay &lista)
{
	lista.posicion = -1;
	lista.actual = nullptr;
}

bool avanzarReplay(ListaReplay &lista, EstadoReplay &estado)
{
	if (lista.primera == nullptr)
	{
		return false;
	}
	
	if (lista.actual == nullptr)
	{
		lista.actual = lista.primera;
		lista.posicion = 0;
		estado = lista.actual->estado;
		return true;
	}
	
	if (lista.actual->siguiente == nullptr)
	{
		return false;
	}
	
	lista.actual = lista.actual->siguiente;
	lista.posicion++;
	estado = lista.actual->estado;
	
	return true;
}

bool retrocederReplay(ListaReplay &lista, EstadoReplay &estado)
{
	if (lista.actual == nullptr)
	{
		return false;
	}
	
	if (lista.actual->anterior == nullptr)
	{
		return false;
	}
	
	lista.actual = lista.actual->anterior;
	lista.posicion--;
	estado = lista.actual->estado;
	
	return true;
}

void limpiarReplay(ListaReplay &lista)
{
	NodoReplay *actual = lista.primera;
	
	while (actual != nullptr)
	{
		NodoReplay *siguiente = actual->siguiente;
		delete actual;
		actual = siguiente;
	}
	
	lista.primera = nullptr;
	lista.ultima = nullptr;
	lista.actual = nullptr;
	lista.posicion = -1;
	lista.cantidad = 0;
}
