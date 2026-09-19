#ifndef EVENTOS_H
#define EVENTOS_H

struct Evento
{
	int tipo;
	float tiempo;
};

const int EVENTO_SUBIR_NIVEL = 1;
const int EVENTO_BONUS_LINEAS = 2;
const int EVENTO_NUEVO_RECORD = 3;
const int EVENTO_TABLERO_PELIGRO = 4;

struct NodoEvento
{
	Evento evento;
	NodoEvento *siguiente;
};

struct ColaEventos
{
	NodoEvento *frente;
	int cantidad;
};

void inicializarEventos(ColaEventos &cola);
void insertarEvento(ColaEventos &cola, Evento evento);
bool obtenerEvento(ColaEventos &cola, Evento &evento);
bool colaEventosVacia(ColaEventos &cola);
int cantidadEventos(ColaEventos &cola);

#endif
