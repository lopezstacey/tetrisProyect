#include "eventos.h"

void inicializarEventos(ColaEventos &cola)
{
	cola.frente = nullptr;
	cola.cantidad = 0;
}

void insertarEvento(ColaEventos &cola, Evento evento)
{
	NodoEvento *nuevo = new NodoEvento;
	nuevo->evento = evento;
	nuevo->siguiente = nullptr;
	
	if (cola.frente == nullptr || evento.tiempo < cola.frente->evento.tiempo)
	{
		nuevo->siguiente = cola.frente;
		cola.frente = nuevo;
	}
	else
	{
		NodoEvento *actual = cola.frente;
		
		while (actual->siguiente != nullptr &&
			   actual->siguiente->evento.tiempo <= evento.tiempo)
		{
			actual = actual->siguiente;
		}
		
		nuevo->siguiente = actual->siguiente;
		actual->siguiente = nuevo;
	}
	
	cola.cantidad++;
}

bool obtenerEvento(ColaEventos &cola, Evento &evento)
{
	if (cola.frente == nullptr)
	{
		return false;
	}
	
	NodoEvento *auxiliar = cola.frente;
	evento = auxiliar->evento;
	cola.frente = auxiliar->siguiente;
	
	delete auxiliar;
	
	cola.cantidad--;
	
	return true;
}

bool colaEventosVacia(ColaEventos &cola)
{
	return cola.frente == nullptr;
}

int cantidadEventos(ColaEventos &cola)
{
	return cola.cantidad;
}
