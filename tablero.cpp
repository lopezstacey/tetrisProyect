#include "tablero.h"

void inicializarTablero(Tablero &tablero)
{
	tablero.primera = nullptr;
	tablero.ultima = nullptr;
	tablero.cantidadFilas = 0;
	
	for (int i = 0; i < 20; i++)
	{
		NodoFila *nueva = new NodoFila;
		
		for (int j = 0; j < 10; j++)
		{
			nueva->celdas[j] = 0;
		}
		
		nueva->siguiente = nullptr;
		nueva->anterior = nullptr;
		
		if (tablero.primera == nullptr)
		{
			tablero.primera = nueva;
			tablero.ultima = nueva;
		}
		else
		{
			nueva->anterior = tablero.ultima;
			tablero.ultima->siguiente = nueva;
			tablero.ultima = nueva;
		}
		
		tablero.cantidadFilas++;
	}
}

NodoFila* obtenerFila(Tablero &tablero, int numeroFila)
{
	if (numeroFila < 0 || numeroFila >= tablero.cantidadFilas)
	{
		return nullptr;
	}
	
	NodoFila *actual = tablero.primera;
	
	for (int i = 0; i < numeroFila; i++)
	{
		actual = actual->siguiente;
	}
	
	return actual;
}


void establecerCelda(Tablero &tablero, int fila, int columna, int valor)
{
	if (fila < 0 || fila >= tablero.cantidadFilas)
	{
		return;
	}
	
	if (columna < 0 || columna >= 10)
	{
		return;
	}
	
	NodoFila *nodo = obtenerFila(tablero, fila);
	
	if (nodo != nullptr)
	{
		nodo->celdas[columna] = valor;
	}
}

void colocarPieza(Tablero &tablero, Pieza &pieza)
{
	for (int bloque = 0; bloque < 4; bloque++)
	{
		int fila = pieza.fila +
			pieza.bloques[pieza.orientacion][bloque][1];
			
			int columna = pieza.columna +
				pieza.bloques[pieza.orientacion][bloque][0];
				
				establecerCelda(tablero, fila, columna, 1);
	}
}

bool puedeColocarPieza(Tablero &tablero, Pieza &pieza)
{
	for (int bloque = 0; bloque < 4; bloque++)
	{
		int fila = pieza.fila +
			pieza.bloques[pieza.orientacion][bloque][1];
			
			int columna = pieza.columna +
				pieza.bloques[pieza.orientacion][bloque][0];
				
				if (fila < 0 || fila >= 20 ||
					columna < 0 || columna >= 10)
				{
					return false;
				}
				
				NodoFila *nodo = obtenerFila(tablero, fila);
				
				if (nodo->celdas[columna] != 0)
				{
					return false;
				}
	}
	
	return true;
}

bool moverPiezaHorizontal(Tablero &tablero, Pieza &pieza, int desplazamiento)
{
	Pieza prueba = pieza;
	
	prueba.columna = prueba.columna + desplazamiento;
	
	if (puedeColocarPieza(tablero, prueba))
	{
		pieza.columna = prueba.columna;
		return true;
	}
	
	return false;
}

bool moverPiezaAbajo(Tablero &tablero, Pieza &pieza)
{
	Pieza prueba = pieza;
	
	prueba.fila = prueba.fila + 1;
	
	if (puedeColocarPieza(tablero, prueba))
	{
		pieza.fila = prueba.fila;
		return true;
	}
	
	return false;
}

void fijarPieza(Tablero &tablero, Pieza &pieza)
{
	colocarPieza(tablero, pieza);
}

bool filaCompleta(NodoFila *fila)
{
	for (int columna = 0; columna < 10; columna++)
	{
		if (fila->celdas[columna] == 0)
		{
			return false;
		}
	}
	
	return true;
}

void eliminarFila(Tablero &tablero, NodoFila *fila)
{
	if (fila == nullptr)
	{
		return;
	}
	
	if (fila->anterior != nullptr)
	{
		fila->anterior->siguiente = fila->siguiente;
	}
	else
	{
		tablero.primera = fila->siguiente;
	}
	
	if (fila->siguiente != nullptr)
	{
		fila->siguiente->anterior = fila->anterior;
	}
	else
	{
		tablero.ultima = fila->anterior;
	}
	
	delete fila;
	tablero.cantidadFilas--;
}

void insertarFilaInicio(Tablero &tablero)
{
	NodoFila *nueva = new NodoFila;
	
	for (int columna = 0; columna < 10; columna++)
	{
		nueva->celdas[columna] = 0;
	}
	
	nueva->anterior = nullptr;
	nueva->siguiente = tablero.primera;
	
	if (tablero.primera != nullptr)
	{
		tablero.primera->anterior = nueva;
	}
	else
	{
		tablero.ultima = nueva;
	}
	
	tablero.primera = nueva;
	tablero.cantidadFilas++;
}

void eliminarFilasCompletas(Tablero &tablero)
{
	NodoFila *actual = tablero.primera;
	
	while (actual != nullptr)
	{
		NodoFila *siguiente = actual->siguiente;
		
		if (filaCompleta(actual))
		{
			eliminarFila(tablero, actual);
			insertarFilaInicio(tablero);
		}
		
		actual = siguiente;
	}
}
