#ifndef TABLERO_H
#define TABLERO_H
#include "pieza.h"

struct NodoFila
{
	int celdas[10];
	NodoFila *siguiente;
	NodoFila *anterior;
};

struct Tablero
{
	NodoFila *primera;
	NodoFila *ultima;
	int cantidadFilas;
};

void inicializarTablero(Tablero &tablero);
NodoFila* obtenerFila(Tablero &tablero, int numeroFila);
void establecerCelda(Tablero &tablero, int fila, int columna, int valor);
void colocarPieza(Tablero &tablero, Pieza &pieza);
bool puedeColocarPieza(Tablero &tablero, Pieza &pieza);
bool moverPiezaHorizontal(Tablero &tablero, Pieza &pieza, int desplazamiento);
bool moverPiezaAbajo(Tablero &tablero, Pieza &pieza);
void fijarPieza(Tablero &tablero, Pieza &pieza);
bool filaCompleta(NodoFila *fila);
void eliminarFila(Tablero &tablero, NodoFila *fila);
void insertarFilaInicio(Tablero &tablero);
void eliminarFilasCompletas(Tablero &tablero);
bool puedeRotarPieza(Tablero &tablero, Pieza &pieza);

#endif
