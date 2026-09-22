#include "interfaz.h"
#include <ctime>

Color colorPieza(char tipo)
{
	if (tipo == 'I')
		return Color(150, 200, 210);
	
	if (tipo == 'O')
		return Color(210, 190, 150);
	
	if (tipo == 'T')
		return Color(180, 160, 200);
	
	if (tipo == 'S')
		return Color(150, 180, 150);
	
	if (tipo == 'Z')
		return Color(130, 60, 75);
	
	if (tipo == 'J')
		return Color(150, 150, 155);
	
	if (tipo == 'L')
		return Color(225, 210, 175);
	
	return Color(255, 255, 255);
}

void dibujarPieza(RenderWindow &ventana, Pieza &pieza, int posX, int posY)
{
	for (int bloque = 0; bloque < 4; bloque++)
	{
		int x = pieza.bloques[pieza.orientacion][bloque][0];
		int y = pieza.bloques[pieza.orientacion][bloque][1];
		
		RectangleShape celda(Vector2f(TAMANO_CELDA - 2, TAMANO_CELDA - 2));
		
		celda.setPosition(posX + x * TAMANO_CELDA, posY + y * TAMANO_CELDA);
		
		celda.setFillColor(colorPieza(pieza.tipo));
		
		ventana.draw(celda);
	}
}

void dibujarFondo(RenderWindow &ventana)
{
	ventana.draw(spriteFondo);
	
	RectangleShape barraSuperior(Vector2f(ANCHO_VENTANA, 40));
	barraSuperior.setPosition(0, 0);
	barraSuperior.setFillColor(Color(5, 10, 30, 180));
	ventana.draw(barraSuperior);
	
	RectangleShape barraInferior(Vector2f(ANCHO_VENTANA, 40));
	barraInferior.setPosition(0, ALTO_VENTANA - 40);
	barraInferior.setFillColor(Color(5, 10, 30, 180));
	ventana.draw(barraInferior);
}

void dibujarTexto(RenderWindow &ventana, string texto, int x, int y, int tamano)
{
	Text textoDibujado;
	textoDibujado.setFont(fuente);
	textoDibujado.setString(texto);
	textoDibujado.setCharacterSize(tamano);
	textoDibujado.setFillColor(Color(220, 240, 255));
	textoDibujado.setPosition(x, y);
	ventana.draw(textoDibujado);
}

void dibujarMarcoTablero(RenderWindow &ventana)
{
	RectangleShape marco(Vector2f(310, 610));
	marco.setPosition(TABLERO_X - 5, TABLERO_Y - 5);
	marco.setFillColor(Color(10, 20, 45));
	marco.setOutlineColor(Color(0, 150, 255));
	marco.setOutlineThickness(4);
	ventana.draw(marco);
}

void dibujarPanelHold(RenderWindow &ventana)
{
	RectangleShape panel(Vector2f(400, 130));
	panel.setPosition(PANEL_X, HOLD_Y);
	panel.setFillColor(Color(10, 20, 45, 230));
	panel.setOutlineColor(Color(0, 150, 255));
	panel.setOutlineThickness(3);
	ventana.draw(panel);
	dibujarTexto(ventana, "HOLD", PANEL_X + 20, HOLD_Y + 10, 24);
}

void dibujarPanelSiguientes(RenderWindow &ventana)
{
	RectangleShape panel(Vector2f(400, 330));
	panel.setPosition(PANEL_X, SIGUIENTES_Y);
	panel.setFillColor(Color(10, 20, 45, 230));
	panel.setOutlineColor(Color(0, 150, 255));
	panel.setOutlineThickness(3);
	ventana.draw(panel);
	dibujarTexto(ventana, "SIGUIENTES", PANEL_X + 20, SIGUIENTES_Y + 10, 24);
}

void dibujarPanelPuntaje(RenderWindow &ventana)
{
	RectangleShape panel(Vector2f(400, 100));
	panel.setPosition(PANEL_X, PUNTAJE_Y);
	panel.setFillColor(Color(10, 20, 45, 230));
	panel.setOutlineColor(Color(0, 150, 255));
	panel.setOutlineThickness(3);
	ventana.draw(panel);
	dibujarTexto(ventana, "PUNTAJE: " + to_string(puntaje), PANEL_X + 20, PUNTAJE_Y + 10, 22);
	dibujarTexto(ventana, "NIVEL: " + to_string(nivel), PANEL_X + 250, PUNTAJE_Y + 10, 22);
}

void dibujarPanelControles(RenderWindow &ventana, bool modoReplay)
{
	RectangleShape panel(Vector2f(400, 90));
	panel.setPosition(PANEL_X, CONTROLES_Y);
	panel.setFillColor(Color(10, 20, 45, 230));
	panel.setOutlineColor(Color(0, 150, 255));
	panel.setOutlineThickness(3);
	ventana.draw(panel);
	
	if (modoReplay)
	{
		dibujarTexto(ventana, "A  Retroceder     D  Avanzar", PANEL_X + 20, CONTROLES_Y + 12, 18);
		dibujarTexto(ventana, "SPACE  Reproducir / Reiniciar", PANEL_X + 20, CONTROLES_Y + 48, 18);
	}
	else
	{
		dibujarTexto(ventana, " <-  Mover     ->  Mover     ^  Rotar", PANEL_X + 20, CONTROLES_Y + 12, 18);
		dibujarTexto(ventana, "v  Bajar          C  Hold", PANEL_X + 20, CONTROLES_Y + 48, 18);
	}
}

void dibujarSiguientes(RenderWindow &ventana, Cola &cola)
{
	Pieza pieza;
	
	for (int i = 1; i <= 3; i++)
	{
		if (obtenerPieza(cola, i, pieza))
		{
			int posX = PANEL_X + 140;
			int posY = SIGUIENTES_Y + 55 + (i - 1) * 90;
			
			dibujarPieza(ventana, pieza, posX, posY);
		}
	}
}

void dibujarHold(RenderWindow &ventana, Pila &pilaHold)
{
	Pieza piezaHold;
	
	if (cimaPila(pilaHold, piezaHold))
	{
		dibujarPieza(ventana, piezaHold, 680, 145);
	}
}

void dibujarTablero(RenderWindow &ventana, Tablero &tablero, Pieza &piezaActual, bool tableroPeligroActivo)
{
	for (int fila = 0; fila < 20; fila++)
	{
		NodoFila *nodo = obtenerFila(tablero, fila);
		
		for (int columna = 0; columna < 10; columna++)
		{
			RectangleShape celda(Vector2f(TAMANO_CELDA - 1, TAMANO_CELDA - 1));
			
			celda.setPosition(TABLERO_X + columna * TAMANO_CELDA, TABLERO_Y + fila * TAMANO_CELDA);
			
			if (nodo->celdas[columna] == 0)
			{
				if (tableroPeligroActivo && fila < 3)
				{
					celda.setFillColor(Color(70, 15, 15));
				}
				else
				{
					celda.setFillColor(Color(15, 15, 15));
				}
			}
			else
			{
				celda.setFillColor(colorPieza(piezaActual.tipo));
			}
			
			ventana.draw(celda);
		}
	}
	
	dibujarPieza(ventana, piezaActual, TABLERO_X + piezaActual.columna * TAMANO_CELDA, TABLERO_Y + piezaActual.fila * TAMANO_CELDA);
}

void dibujarGameOver(RenderWindow &ventana)
{
	RectangleShape fondo(Vector2f(500, 280));
	
	fondo.setPosition(350, 280);
	fondo.setFillColor(Color(5, 10, 30, 230));
	fondo.setOutlineColor(Color(0, 150, 255));
	fondo.setOutlineThickness(4);
	ventana.draw(fondo);
	
	dibujarTexto(ventana, "GAME OVER", 455, 315, 42);
	dibujarTexto(ventana, "Puntaje: " + to_string(puntaje), 455, 375, 24);
	dibujarTexto(ventana, "Que deseas hacer?", 455, 410, 20);
	
	RectangleShape botonReplay(Vector2f(180, 50));
	botonReplay.setPosition(390, 460);
	botonReplay.setFillColor(Color(10, 80, 130));
	botonReplay.setOutlineColor(Color(0, 200, 255));
	botonReplay.setOutlineThickness(2);
	ventana.draw(botonReplay);
	
	dibujarTexto(ventana, "VER REPLAY", 415, 470, 20);
	
	RectangleShape botonSalir(Vector2f(180, 50));
	botonSalir.setPosition(630, 460);
	botonSalir.setFillColor(Color(80, 30, 40));
	botonSalir.setOutlineColor(Color(255, 100, 100));
	botonSalir.setOutlineThickness(2);
	ventana.draw(botonSalir);
	
	dibujarTexto(ventana, "REGRESAR", 670, 470, 20);
}

bool botonReplayPresionado(int x, int y)
{
	return x >= 390 && x <= 570 && y >= 440 && y <= 490;
}

bool botonRegresarPresionado(int x, int y, int botonX, int botonY)
{
	return x >= botonX && x <= botonX + 200 && y >= botonY && y <= botonY + 55;
}

void dibujarPortada(RenderWindow &ventana)
{
	spriteInicio.setScale(1200.0f / texturaInicio.getSize().x, 900.0f / texturaInicio.getSize().y);
	ventana.draw(spriteInicio);
	
	RectangleShape boton;
	
	boton.setSize(Vector2f(430, 70));
	boton.setOutlineThickness(4);
	
	int x = 385;
	int y = 325;
	int separacion = 90;
	
	boton.setPosition(x, y);
	boton.setFillColor(Color(230, 150, 20));
	boton.setOutlineColor(Color(255, 220, 80));
	ventana.draw(boton);
	dibujarTexto(ventana, "INICIAR PARTIDA", x + 100, y + 17, 28);
	
	y += separacion;
	
	boton.setPosition(x, y);
	boton.setFillColor(Color(20, 100, 220));
	boton.setOutlineColor(Color(80, 200, 255));
	ventana.draw(boton);
	dibujarTexto(ventana, "MEJORES 10 PUNTAJES", x + 70, y + 17, 25);
	
	y += separacion;
	
	boton.setPosition(x, y);
	boton.setFillColor(Color(20, 160, 70));
	boton.setOutlineColor(Color(80, 255, 120));
	ventana.draw(boton);
	dibujarTexto(ventana, "COMO JUGAR", x + 125, y + 17, 28);
	
	y += separacion;
	
	boton.setPosition(x, y);
	boton.setFillColor(Color(100, 30, 190));
	boton.setOutlineColor(Color(190, 100, 255));
	ventana.draw(boton);
	dibujarTexto(ventana, "INFORMACION", x + 125, y + 17, 28);
	
	y += separacion;
	
	boton.setPosition(x, y);
	boton.setFillColor(Color(180, 20, 40));
	boton.setOutlineColor(Color(255, 80, 90));
	ventana.draw(boton);
	dibujarTexto(ventana, "SALIR", x + 175, y + 17, 28);
}

bool botonInicioPresionado(int x, int y)
{
	return x >= 385 && x <= 815 && y >= 325 && y <= 395;
}

bool botonPuntajesPresionado(int x, int y)
{
	return x >= 385 && x <= 815 && y >= 415 && y <= 485;
}

bool botonComoJugarPresionado(int x, int y)
{
	return x >= 385 && x <= 815 && y >= 505 && y <= 575;
}

bool botonInformacionPresionado(int x, int y)
{
	return x >= 385 && x <= 815 && y >= 595 && y <= 665;
}

bool botonSalirPortadaPresionado(int x, int y)
{
	return x >= 385 && x <= 815 && y >= 685 && y <= 755;
}

bool botonRegresarReplayPresionado(int x, int y)
{
	return x >= 500 && x <= 700 && y >= 820 && y <= 875;
}

void dibujarBotonRegresarReplay(RenderWindow &ventana)
{
	RectangleShape boton;
	
	boton.setSize(Vector2f(200, 55));
	boton.setPosition(500, 820);
	boton.setFillColor(Color(180, 20, 40));
	boton.setOutlineThickness(3);
	boton.setOutlineColor(Color(255, 100, 100));
	
	ventana.draw(boton);
	
	dibujarTexto(ventana, "REGRESAR", 535, 830, 24);
}

void dibujarNombreJugador(RenderWindow &ventana, string nombre)
{
	RectangleShape fondo(Vector2f(500, 350));
	fondo.setPosition(350, 250);
	fondo.setFillColor(Color(20, 20, 20, 240));
	fondo.setOutlineThickness(3);
	fondo.setOutlineColor(Color::White);
	ventana.draw(fondo);
	
	dibujarTexto(ventana, "NUEVA PARTIDA", 480, 285, 32);
	dibujarTexto(ventana, "Ingrese su nombre:", 455, 345, 24);
	
	RectangleShape entrada(Vector2f(400, 50));
	entrada.setPosition(400, 395);
	entrada.setFillColor(Color(40, 40, 40));
	entrada.setOutlineThickness(2);
	entrada.setOutlineColor(Color::White);
	ventana.draw(entrada);
	
	Text textoNombre;
	textoNombre.setFont(fuente);
	textoNombre.setString(nombre);
	textoNombre.setCharacterSize(22);
	textoNombre.setFillColor(Color::White);
	textoNombre.setPosition(415, 405);
	ventana.draw(textoNombre);
	
	if ((clock() / (CLOCKS_PER_SEC / 2)) % 2 == 0)
	{
		Text cursor;
		cursor.setFont(fuente);
		cursor.setString("|");
		cursor.setCharacterSize(22);
		cursor.setFillColor(Color::White);
		
		float posicionCursor = textoNombre.findCharacterPos(nombre.length()).x;
		
		cursor.setPosition(posicionCursor, 405);
		
		ventana.draw(cursor);
	}
	
	RectangleShape botonJugar(Vector2f(180, 50));
	botonJugar.setPosition(510, 470);
	botonJugar.setFillColor(Color(50, 120, 70));
	ventana.draw(botonJugar);
	
	dibujarTexto(ventana, "JUGAR", 560, 480, 22);
	
	dibujarBotonRegresar(ventana, 500, 535);
}

bool botonJugarNombrePresionado(int x, int y)
{
	return x >= 510 && x <= 690 && y >= 470 && y <= 520;
}

void dibujarPuntajes(RenderWindow &ventana, string nombres[], int puntajes[], int cantidad)
{
	dibujarFondo(ventana);
	
	dibujarTexto(ventana, "MEJORES 10 PUNTAJES", 400, 100, 35);
	
	int posicionY = 180;
	
	for (int i = 0; i < cantidad; i++)
	{
		string texto = to_string(i + 1) + ".  " + nombres[i] + "    " + to_string(puntajes[i]);
		
		dibujarTexto(ventana, texto, 400, posicionY, 25);
		
		posicionY += 45;
	}
	
	if (cantidad == 0)
	{
		dibujarTexto(ventana, "No hay puntajes registrados", 400, 250, 25);
	}
	
	string tiempo = "Tiempo de ejecucion: " + to_string(tiempoOrdenamiento) + " microsegundos";
	dibujarTexto(ventana, tiempo, 400, 690, 22);
	
	dibujarBotonRegresar(ventana, 500, 750);
}

void dibujarBotonRegresar(RenderWindow &ventana, int x, int y)
{
	RectangleShape boton;
	
	boton.setSize(Vector2f(200, 55));
	boton.setPosition(x, y);
	boton.setFillColor(Color(50, 50, 50, 230));
	boton.setOutlineColor(Color::White);
	boton.setOutlineThickness(2);
	
	ventana.draw(boton);
	
	dibujarTexto(ventana, "REGRESAR", x + 45, y + 15, 22);
}
void dibujarBotonOrdenamiento(RenderWindow &ventana, int x, int y, int ancho, int alto, string texto, Color color, Color borde)
{
	RectangleShape boton;
	boton.setSize(Vector2f(ancho, alto));
	boton.setPosition(x, y);
	boton.setFillColor(color);
	boton.setOutlineColor(borde);
	boton.setOutlineThickness(3);
	ventana.draw(boton);
	dibujarTexto(ventana, texto, x + 40, y + 15, 24);
}

void dibujarSeleccionOrdenamiento(RenderWindow &ventana)
{
	dibujarFondo(ventana);
	
	dibujarTexto(ventana, "MEJORES 10 PUNTAJES", 390, 100, 35);
	dibujarTexto(ventana, "Seleccione el metodo de ordenamiento", 370, 160, 24);
	
	dibujarBotonOrdenamiento(ventana, 320, 270, 250, 50, "INSERTION SORT", Color(20, 100, 220), Color(80, 200, 255));
	dibujarBotonOrdenamiento(ventana, 680, 270, 250, 50, "MERGE SORT", Color(20, 160, 70), Color(80, 255, 120));
	
	dibujarBotonRegresar(ventana, 500, 750);
}

bool botonInsertionSortPresionado(int x, int y)
{
	return x >= 320 && x <= 570 && y >= 270 && y <= 320;
}

bool botonMergeSortPresionado(int x, int y)
{
	return x >= 680 && x <= 930 && y >= 270 && y <= 320;
}
void dibujarBotonPausa(RenderWindow &ventana, bool pausado)
{
	RectangleShape boton(Vector2f(180, 50));
	boton.setPosition(700, 810);
	boton.setFillColor(Color(20, 100, 220));
	boton.setOutlineColor(Color(80, 200, 255));
	boton.setOutlineThickness(3);
	ventana.draw(boton);
	
	if (pausado)
	{
		dibujarTexto(ventana, "Continuar", 730, 822, 22);
	}
	else
	{
		dibujarTexto(ventana, "Pausar", 755, 822, 22);
	}
}

bool botonPausaPresionado(int x, int y)
{
	return x >= 700 && x <= 880 && y >= 810 && y <= 860;
}
void dibujarComoJugar(RenderWindow &ventana)
{
	dibujarFondo(ventana);
	
	dibujarTexto(ventana, "COMO JUGAR", 480, 50, 40);
	
	dibujarTexto(ventana, "CONTROLES", 120, 130, 26);
	dibujarTexto(ventana, "<-  Mover pieza a la izquierda", 120, 175, 19);
	dibujarTexto(ventana, "->  Mover pieza a la derecha", 120, 210, 19);
	dibujarTexto(ventana, "^   Rotar pieza", 120, 245, 19);
	dibujarTexto(ventana, "v   Bajar pieza", 120, 280, 19);
	dibujarTexto(ventana, "SPACE  Bajar rapidamente", 120, 315, 19);
	dibujarTexto(ventana, "C   Guardar pieza en HOLD", 120, 350, 19);
	
	dibujarTexto(ventana, "OBJETIVO", 650, 130, 26);
	dibujarTexto(ventana, "Completa filas para obtener puntos.", 650, 175, 19);
	dibujarTexto(ventana, "Las filas completas desaparecen.", 650, 210, 19);
	dibujarTexto(ventana, "El juego termina si la pieza", 650, 245, 19);
	dibujarTexto(ventana, "no puede colocarse al aparecer.", 650, 280, 19);
	
	dibujarTexto(ventana, "HOLD", 120, 430, 26);
	dibujarTexto(ventana, "Presiona C para guardar la pieza", 120, 470, 19);
	dibujarTexto(ventana, "y utilizarla despues.", 120, 505, 19);
	
	dibujarTexto(ventana, "PUNTOS Y NIVELES", 650, 430, 26);
	dibujarTexto(ventana, "Cada linea completada: 100 puntos.", 650, 470, 19);
	dibujarTexto(ventana, "Cada 5 lineas aumenta el nivel.", 650, 505, 19);
	
	dibujarTexto(ventana, "EVENTOS", 120, 590, 26);
	dibujarTexto(ventana, "5 lineas: activa el aumento de velocidad.",120,630,18);
	dibujarTexto(ventana, "10 lineas: activa el BONUS.", 120, 660, 18);
	dibujarTexto(ventana, "15 lineas: activa el tablero en peligro.", 120, 690, 18);
	
	dibujarTexto(ventana, "BONUS", 650, 590, 26);
	dibujarTexto(ventana, "El bonus agrega puntos al eliminar", 650, 630, 18);
	dibujarTexto(ventana, "2 o mas lineas al mismo tiempo.", 650, 660, 18);
	
	dibujarBotonRegresar(ventana, 500, 750);
}
void dibujarInformacion(RenderWindow &ventana)
{
	dibujarFondo(ventana);
	
	dibujarTexto(ventana, "Universidad Nacional de Costa Rica", 330, 150, 30);
	dibujarTexto(ventana, "Sede Regional Brunca", 450, 205, 24);
	dibujarTexto(ventana, "Campus Perez Zeledon", 450, 245, 24);
	
	dibujarTexto(ventana, "Curso: Estructuras de Datos", 400, 350, 24);
	dibujarTexto(ventana, "Proyecto: Tetris", 470, 395, 24);
	dibujarTexto(ventana, "Estudiante: Stacey Lopez Ceciliano", 360, 440, 24);
	dibujarTexto(ventana, "Profesora: Saray Castro", 425, 485, 24);
	
	dibujarTexto(ventana, "2026", 555, 550, 28);
	
	dibujarBotonRegresar(ventana, 500, 750);
}
