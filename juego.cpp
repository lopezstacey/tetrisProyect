#include "juego.h"


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
	while (lineasTotales >= proximoNivel)
	{
		Evento evento;
		evento.tipo = EVENTO_SUBIR_NIVEL;
		evento.valor = lineasTotales;
		
		insertarEvento(eventos, evento);
		
		proximoNivel += 5;
	}
}

void procesarEventos(ColaEventos &eventos, int &nivel, float &velocidadCaida, int &puntaje, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo)
{
	while (!colaEventosVacia(eventos))
	{
		Evento eventoActual;
		obtenerEvento(eventos, eventoActual);
		
		if (eventoActual.tipo == EVENTO_SUBIR_NIVEL)
		{
			nivel++;
			
			if (velocidadCaida > 0.10)
			{
				velocidadCaida -= 0.08;
			}
			
			if (velocidadCaida < 0.10)
			{
				velocidadCaida = 0.10;
			}
		}
		
		if (eventoActual.tipo == EVENTO_BONUS_LINEAS)
		{
			bonusActivo = true;
		}
		
		if (eventoActual.tipo == EVENTO_TABLERO_PELIGRO)
		{
			tableroPeligroActivo = true;
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

void procesarBonus(ColaEventos &eventos, int filasEliminadas, int &puntaje, bool bonusActivo)
{
	if (bonusActivo && filasEliminadas >= 2)
	{
		puntaje += filasEliminadas * 50;
	}
}

void procesarTableroPeligro(ColaEventos &eventos, int lineasTotales, bool &tableroPeligroActivo)
{
	if (lineasTotales >= 15 && !tableroPeligroActivo)
	{
		Evento evento;
		evento.tipo = EVENTO_TABLERO_PELIGRO;
		evento.valor = lineasTotales;
		
		insertarEvento(eventos, evento);
	}
}

void finalizarPiezaTerminada(Tablero &tablero, Cola &cola, Pila &pilaHold, Pieza &piezaActual, ColaEventos &eventos, ListaReplay &replay, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, float &velocidadCaida, bool &gameOver, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo, string nombreJugador)
{
	int filasEliminadas = eliminarFilasCompletas(tablero);
	
	procesarLineas(eventos, filasEliminadas, puntaje, lineasTotales);
	
	if (lineasTotales >= 10 && !bonusActivo)
	{
		Evento evento;
		evento.tipo = EVENTO_BONUS_LINEAS;
		evento.valor = lineasTotales;
		insertarEvento(eventos, evento);
	}
	
	procesarBonus(eventos, filasEliminadas, puntaje, bonusActivo);
	procesarNivel(eventos, lineasTotales, proximoNivel);
	procesarTableroPeligro(eventos, lineasTotales, tableroPeligroActivo);
	
	procesarEventos(eventos, nivel, velocidadCaida, puntaje, nuevoRecord, bonusActivo, tableroPeligroActivo);
	
	Pieza piezaTerminada;
	
	desencolar(cola, piezaTerminada);
	mantenerCola(cola);
	obtenerPieza(cola, 0, piezaActual);
	
	piezaActual.fila = 0;
	piezaActual.columna = 3;
	piezaActual.orientacion = 0;
	
	if (!puedeColocarPieza(tablero, piezaActual))
	{
		gameOver = true;
		
		procesarRecord(eventos, nombreJugador, puntaje);
		
		procesarEventos(eventos, nivel, velocidadCaida, puntaje, nuevoRecord, bonusActivo, tableroPeligroActivo);
	}
	
	guardarEstadoActualReplay(replay, tablero, piezaActual, pilaHold, puntaje, nivel);
}

void procesarPiezaTerminada(Tablero &tablero, Cola &cola, Pila &pilaHold, Pieza &piezaActual, ColaEventos &eventos, ListaReplay &replay, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, float &velocidadCaida, bool &gameOver, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo, string nombreJugador, AnimacionLineas &animacion)
{
	fijarPieza(tablero, piezaActual);
	
	iniciarAnimacionLineas(tablero, animacion);
	
	if (animacion.activa)
	{
		return;
	}
	
	finalizarPiezaTerminada(tablero, cola, pilaHold, piezaActual, eventos, replay, puntaje, lineasTotales, proximoNivel, nivel, velocidadCaida, gameOver, nuevoRecord, bonusActivo, tableroPeligroActivo, nombreJugador);
}

void procesarTecla(Keyboard::Key tecla, Tablero &tablero, Cola &cola, Pila &pilaHold, Pieza &piezaActual, ListaReplay &replay, int &puntaje, int &nivel)
{
	bool cambio = false;
	
	if (tecla == Keyboard::Left)
	{
		if (moverPiezaHorizontal(tablero, piezaActual, -1))
		{
			cambio = true;
		}
	}
	
	if (tecla == Keyboard::Right)
	{
		if (moverPiezaHorizontal(tablero, piezaActual, 1))
		{
			cambio = true;
		}
	}
	
	if (tecla == Keyboard::Down)
	{
		if (moverPiezaAbajo(tablero, piezaActual))
		{
			cambio = true;
		}
	}
	
	if (tecla == Keyboard::Up)
	{
		if (puedeRotarPieza(tablero, piezaActual))
		{
			rotarPieza(piezaActual);
			cambio = true;
		}
	}
	
	if (tecla == Keyboard::C)
	{
		hacerHold(cola, pilaHold, piezaActual);
		cambio = true;
	}
	
	if (cambio)
	{
		guardarEstadoActualReplay(replay, tablero, piezaActual, pilaHold, puntaje, nivel);
	}
}

void procesarCaida(Tablero &tablero, Cola &cola, Pieza &piezaActual, ColaEventos &eventos, Pila &pilaHold, ListaReplay &replay, int &puntaje, int &lineasTotales, int &proximoNivel, int &nivel, float &velocidadCaida, bool &gameOver, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo, string nombreJugador, AnimacionLineas &animacion)
{
	bool pudoBajar = moverPiezaAbajo(tablero, piezaActual);
	
	if (pudoBajar)
	{
		guardarEstadoActualReplay(replay, tablero, piezaActual, pilaHold, puntaje, nivel);
	}
	else
	{
		procesarPiezaTerminada(tablero, cola, pilaHold, piezaActual, eventos, replay, puntaje, lineasTotales, proximoNivel, nivel, velocidadCaida, gameOver, nuevoRecord, bonusActivo, tableroPeligroActivo, nombreJugador, animacion);
	}
}

void cargarPuntajes(string nombres[], int puntajes[], int &cantidad)
{
	ifstream archivo("records.txt");
	
	cantidad = 0;
	
	string linea;
	
	while (cantidad < 10 && getline(archivo, linea))
	{
		stringstream datos(linea);
		string nombre;
		int puntaje;
		
		if (getline(datos, nombre, '|') && datos >> puntaje)
		{
			nombres[cantidad] = nombre;
			puntajes[cantidad] = puntaje;
			cantidad++;
		}
	}
	
	archivo.close();
}

void guardarPuntajes(string nombres[], int puntajes[], int cantidad)
{
	ofstream archivo("records.txt");
	
	for (int i = 0; i < cantidad; i++)
	{
		archivo << nombres[i] << " | " << puntajes[i] << endl;
	}
	
	archivo.close();
}

void ordenarPuntajes(string nombres[], int puntajes[], int cantidad)
{
	for (int i = 1; i < cantidad; i++)
	{
		string nombreActual = nombres[i];
		int puntajeActual = puntajes[i];
		int j = i - 1;
		
		while (j >= 0 && puntajes[j] < puntajeActual)
		{
			nombres[j + 1] = nombres[j];
			puntajes[j + 1] = puntajes[j];
			j--;
		}
		
		nombres[j + 1] = nombreActual;
		puntajes[j + 1] = puntajeActual;
	}
}

void mezclarPuntajes(string nombres[], int puntajes[], int inicio, int medio, int fin)
{
	int cantidad = fin - inicio + 1;
	string *nombresTemp = new string[cantidad];
	int *puntajesTemp = new int[cantidad];
	
	int i = inicio;
	int j = medio + 1;
	int k = 0;
	
	while (i <= medio && j <= fin)
	{
		if (puntajes[i] >= puntajes[j])
		{
			nombresTemp[k] = nombres[i];
			puntajesTemp[k] = puntajes[i];
			i++;
		}
		else
		{
			nombresTemp[k] = nombres[j];
			puntajesTemp[k] = puntajes[j];
			j++;
		}
		
		k++;
	}
	
	while (i <= medio)
	{
		nombresTemp[k] = nombres[i];
		puntajesTemp[k] = puntajes[i];
		i++;
		k++;
	}
	
	while (j <= fin)
	{
		nombresTemp[k] = nombres[j];
		puntajesTemp[k] = puntajes[j];
		j++;
		k++;
	}
	
	for (int posicion = 0; posicion < cantidad; posicion++)
	{
		nombres[inicio + posicion] = nombresTemp[posicion];
		puntajes[inicio + posicion] = puntajesTemp[posicion];
	}
	
	delete[] nombresTemp;
	delete[] puntajesTemp;
}

void ordenarPuntajesMergeRecursivo(string nombres[], int puntajes[], int inicio, int fin)
{
	if (inicio >= fin)
	{
		return;
	}
	
	int medio = (inicio + fin) / 2;
	
	ordenarPuntajesMergeRecursivo(nombres, puntajes, inicio, medio);
	ordenarPuntajesMergeRecursivo(nombres, puntajes, medio + 1, fin);
	mezclarPuntajes(nombres, puntajes, inicio, medio, fin);
}

void ordenarPuntajesMerge(string nombres[], int puntajes[], int cantidad)
{
	if (cantidad > 1)
	{
		ordenarPuntajesMergeRecursivo(nombres, puntajes, 0, cantidad - 1);
	}
}

void insertarPuntaje(string nombre, int puntaje, string nombres[], int puntajes[], int &cantidad)
{
	if (cantidad < 10)
	{
		nombres[cantidad] = nombre;
		puntajes[cantidad] = puntaje;
		cantidad++;
	}
	else if (puntaje > puntajes[cantidad - 1])
	{
		nombres[cantidad - 1] = nombre;
		puntajes[cantidad - 1] = puntaje;
	}
	
	ordenarPuntajes(nombres, puntajes, cantidad);
	guardarPuntajes(nombres, puntajes, cantidad);
}

void procesarRecord(ColaEventos &eventos, string nombre, int puntaje)
{
	int puntajes[10];
	string nombres[10];
	int cantidad = 0;
	
	cargarPuntajes(nombres, puntajes, cantidad);
	
	if (cantidad < 10 || puntaje > puntajes[cantidad - 1])
	{
		Evento evento;
		evento.tipo = EVENTO_NUEVO_RECORD;
		evento.valor = puntaje;
		
		insertarEvento(eventos, evento);
		insertarPuntaje(nombre, puntaje, nombres, puntajes, cantidad);
	}
}

void guardarEstadoActualReplay(ListaReplay &replay, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int puntaje, int nivel)
{
	EstadoReplay estado;
	
	NodoFila *fila = tablero.primera;
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			estado.celdas[i][j] = fila->celdas[j];
		}
		
		fila = fila->siguiente;
	}
	
	estado.piezaActual = piezaActual;
	estado.puntaje = puntaje;
	estado.nivel = nivel;
	
	Pieza piezaHold;
	
	if (cimaPila(pilaHold, piezaHold))
	{
		estado.piezaHold = piezaHold;
		estado.tieneHold = true;
	}
	else
	{
		estado.tieneHold = false;
	}
	if (replay.actual != nullptr && replay.actual != replay.ultima)
	{
		eliminarEstadosSiguientes(replay);
	}
	
	guardarEstadoReplay(replay, estado);
	
	replay.actual = replay.ultima;
	replay.posicion = replay.cantidad - 1;

}

void restaurarEstadoReplay(EstadoReplay estado, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int &puntaje, int &nivel)
{
	NodoFila *fila = tablero.primera;
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fila->celdas[j] = estado.celdas[i][j];
		}
		
		fila = fila->siguiente;
	}
	
	piezaActual = estado.piezaActual;
	puntaje = estado.puntaje;
	nivel = estado.nivel;
	
	limpiarPila(pilaHold);
	
	if (estado.tieneHold)
	{
		apilar(pilaHold, estado.piezaHold);
	}
	else
	{
	}
}

void prepararReplay(ListaReplay &replay, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int &puntaje, int &nivel)
{
	limpiarTablero(tablero);
	limpiarPila(pilaHold);
	
	puntaje = 0;
	nivel = 1;
	
	iniciarReplay(replay);
	
	if (replay.primera != nullptr)
	{
		replay.actual = replay.primera;
		replay.posicion = 0;
		restaurarEstadoReplay(replay.primera->estado, tablero, piezaActual, pilaHold, puntaje, nivel);
	}
}

bool avanzarReplayVisual(ListaReplay &replay, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int &puntaje, int &nivel)
{
	EstadoReplay estado;
	
	if (!avanzarReplay(replay, estado))
	{
		return false;
	}
	
	restaurarEstadoReplay(estado, tablero, piezaActual, pilaHold, puntaje, nivel);
	
	return true;
}

bool retrocederReplayVisual(ListaReplay &replay, Tablero &tablero, Pieza &piezaActual, Pila &pilaHold, int &puntaje, int &nivel)
{
	EstadoReplay estado;
	
	if (!retrocederReplay(replay, estado))
	{
		return false;
	}
	
	restaurarEstadoReplay(estado, tablero, piezaActual, pilaHold, puntaje, nivel);
	
	return true;
}

void reiniciarPartida(Tablero &tablero, Cola &cola, Pila &pilaHold, ColaEventos &eventos, ListaReplay &replay, Pieza &piezaActual, int &puntaje, int &lineasTotales, int &nivel, int &proximoNivel, float &velocidadCaida, bool &gameOver, bool &nuevoRecord, bool &bonusActivo, bool &tableroPeligroActivo)
{
	limpiarTablero(tablero);
	limpiarCola(cola);
	limpiarPila(pilaHold);
	limpiarEventos(eventos);
	limpiarReplay(replay);
	
	puntaje = 0;
	lineasTotales = 0;
	nivel = 1;
	proximoNivel = 5;
	velocidadCaida = 0.5;
	gameOver = false;
	nuevoRecord = false;
	bonusActivo = false;
	tableroPeligroActivo = false;
	
	generarBag(cola);
	generarBag(cola);
	
	obtenerPieza(cola, 0, piezaActual);
	
	guardarEstadoActualReplay(replay, tablero, piezaActual, pilaHold, puntaje, nivel);
}

void iniciarAnimacionLineas(Tablero &tablero, AnimacionLineas &animacion)
{
	int filas[20];
	int cantidad = obtenerFilasCompletas(tablero, filas);
	
	animacion.activa = false;
	animacion.cantidadFilas = cantidad;
	animacion.tiempo = 0;
	animacion.parpadeo = 0;
	animacion.visible = true;
	
	for (int i = 0; i < 20; i++)
	{
		animacion.filas[i] = false;
	}
	
	if (cantidad == 0)
	{
		return;
	}
	
	for (int i = 0; i < cantidad; i++)
	{
		animacion.filas[filas[i]] = true;
	}
	
	animacion.activa = true;
}

bool actualizarAnimacionLineas(AnimacionLineas &animacion, float tiempoTranscurrido)
{
	if (!animacion.activa)
	{
		return false;
	}
	
	animacion.tiempo += tiempoTranscurrido;
	
	while (animacion.tiempo >= 0.15 && animacion.parpadeo < 4)
	{
		animacion.tiempo -= 0.15;
		animacion.visible = !animacion.visible;
		animacion.parpadeo++;
	}
	
	if (animacion.parpadeo >= 4)
	{
		animacion.activa = false;
		animacion.visible = true;
		animacion.tiempo = 0;
		animacion.parpadeo = 0;
		animacion.cantidadFilas = 0;
		
		for (int i = 0; i < 20; i++)
		{
			animacion.filas[i] = false;
		}
		return true;
	}
	
	return false;
}
