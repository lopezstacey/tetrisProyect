#include "juego.h"
#include <fstream>

void hacerHold(Cola &cola, Pila &pilaHold, Pieza &piezaActual)
{
	Pieza piezaGuardada;
	
	if (pilaVacia(pilaHold))
	{
		apilar(pilaHold, piezaActual);
		desencolar(cola, piezaGuardada);
		mantenerCola(cola);
		obtenerPieza(cola, 0, piezaActual);
		piezaActual.fila = 0;
		piezaActual.columna = 3;
		piezaActual.orientacion = 0;
	}
	else
	{
		desapilar(pilaHold, piezaGuardada);
		apilar(pilaHold, piezaActual);
		piezaActual = piezaGuardada;
		piezaActual.fila = 0;
		piezaActual.columna = 3;
		piezaActual.orientacion = 0;
	}
}

void procesarNivel(ColaEventos &eventos, int lineasTotales, int &proximoNivel)
{
	if (lineasTotales >= proximoNivel)
	{
		Evento evento;
		evento.tipo = EVENTO_SUBIR_NIVEL;
		evento.tiempo = lineasTotales;
		insertarEvento(eventos, evento);
		proximoNivel += 5;
	}
}

void procesarEventos(ColaEventos &eventos, int &nivel, float &velocidadCaida, int &puntaje,  bool &nuevoRecord)
{
	while (!colaEventosVacia(eventos))
	{
		Evento eventoActual;
		obtenerEvento(eventos, eventoActual);
		
		if (eventoActual.tipo == EVENTO_SUBIR_NIVEL)
		{
			nivel++;
			
			if (nivel == 2)
			{
				velocidadCaida = 0.4;
			}
			
			if (nivel == 3)
			{
				velocidadCaida = 0.3;
			}
			
			if (nivel == 4)
			{
				velocidadCaida = 0.2;
			}
			
			if (nivel >= 5)
			{
				velocidadCaida = 0.15;
			}
		}
		if (eventoActual.tipo == EVENTO_BONUS_LINEAS)
		{
			puntaje += eventoActual.tiempo * 50;
		}
		
		if (eventoActual.tipo == EVENTO_NUEVO_RECORD)
		{
			nuevoRecord = true;
		}
	}
	
}

void procesarLineas(ColaEventos &eventos, int filasEliminadas, int &puntaje, int &lineasTotales)
{
	if (filasEliminadas > 0)
	{
		puntaje += filasEliminadas * 100;
		lineasTotales += filasEliminadas;
	}
}

void procesarBonus(ColaEventos &eventos, int filasEliminadas)
{
	if (filasEliminadas >= 2)
	{
		Evento evento;
		evento.tipo = EVENTO_BONUS_LINEAS;
		evento.tiempo = filasEliminadas;
		insertarEvento(eventos, evento);
	}
}

void procesarPiezaTerminada(Tablero &tablero, Cola &cola, Pieza &piezaActual, ColaEventos &eventos, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, float &velocidadCaida, 
							bool &gameOver,  bool &nuevoRecord)
{
	fijarPieza(tablero, piezaActual);
	
	int filasEliminadas = eliminarFilasCompletas(tablero);
	
	procesarLineas(eventos, filasEliminadas, puntaje, lineasTotales);
	procesarBonus(eventos, filasEliminadas);
	procesarNivel(eventos, lineasTotales, proximoNivel);
	procesarRecord(eventos, puntaje);
	procesarEventos(eventos, nivel, velocidadCaida, puntaje,nuevoRecord);
	
	Pieza piezaTerminada;
	desencolar(cola, piezaTerminada);
	mantenerCola(cola);
	obtenerPieza(cola, 0, piezaActual);
	
	if (!puedeColocarPieza(tablero, piezaActual))
	{
		gameOver = true;
	}
}

void procesarTecla(Keyboard::Key tecla, Tablero &tablero, Cola &cola, Pila &pilaHold, Pieza &piezaActual)
{
	if (tecla == Keyboard::Left)
	{
		moverPiezaHorizontal(tablero, piezaActual, -1);
	}
	
	if (tecla == Keyboard::Right)
	{
		moverPiezaHorizontal(tablero, piezaActual, 1);
	}
	
	if (tecla == Keyboard::Down)
	{
		moverPiezaAbajo(tablero, piezaActual);
	}
	
	if (tecla == Keyboard::Up)
	{
		if (puedeRotarPieza(tablero, piezaActual))
		{
			rotarPieza(piezaActual);
		}
	}
	
	if (tecla == Keyboard::C)
	{
		hacerHold(cola, pilaHold, piezaActual);
	}
}

void procesarCaida(Tablero &tablero, Cola &cola, Pieza &piezaActual, ColaEventos &eventos, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, float &velocidadCaida, bool &gameOver,  bool &nuevoRecord)
{
	bool pudoBajar = moverPiezaAbajo(tablero, piezaActual);
	
	if (!pudoBajar)
	{
		procesarPiezaTerminada(tablero, cola, piezaActual, eventos, puntaje, lineasTotales, proximoNivel, nivel, velocidadCaida, gameOver, nuevoRecord);
	}
}

int obtenerRecord()
{
	ifstream archivo("records.txt");
	int record = 0;
	
	if (archivo)
	{
		archivo >> record;
	}
	
	archivo.close();
	
	return record;
}

void procesarRecord(ColaEventos &eventos, int puntaje)
{
	int record = obtenerRecord();
	
	if (puntaje > record)
	{
		Evento evento;
		evento.tipo = EVENTO_NUEVO_RECORD;
		evento.tiempo = puntaje;
		insertarEvento(eventos, evento);
	}
}
