#include "interfaz.h"

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
		
		RectangleShape celda(
							 Vector2f(
									  TAMANO_CELDA - 2,
									  TAMANO_CELDA - 2
									  )
							 );
		
		celda.setPosition(
						  posX + x * TAMANO_CELDA,
						  posY + y * TAMANO_CELDA
						  );
		
		celda.setFillColor(
						   colorPieza(pieza.tipo)
						   );
		
		ventana.draw(celda);
	}
}

void dibujarFondo(RenderWindow &ventana)
{
	ventana.draw(spriteFondo);
	
	RectangleShape barraSuperior(Vector2f(ANCHO_VENTANA,40));
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
	RectangleShape marco(Vector2f(310,610));
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

void dibujarPanelControles(RenderWindow &ventana)
{
	RectangleShape panel(Vector2f(400, 90));
	panel.setPosition(PANEL_X, CONTROLES_Y);
	panel.setFillColor(Color(10, 20, 45, 230));
	panel.setOutlineColor(Color(0, 150, 255));
	panel.setOutlineThickness(3);
	ventana.draw(panel);
	dibujarTexto(ventana," <-  Mover     ->  Mover     ^  Rotar", PANEL_X + 20, CONTROLES_Y + 12, 18);
	dibujarTexto(ventana, "v  Bajar          C  Hold", PANEL_X + 20, CONTROLES_Y + 48, 18);
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

void dibujarTablero(RenderWindow &ventana, Tablero &tablero, Pieza &piezaActual)
{
	for (int fila = 0; fila < 20; fila++)
	{
		NodoFila *nodo = obtenerFila(tablero, fila);
		
		for (int columna = 0; columna < 10; columna++)
		{
			RectangleShape celda(Vector2f(TAMANO_CELDA - 1, TAMANO_CELDA - 1));
			celda.setPosition(TABLERO_X + columna * TAMANO_CELDA,
							  TABLERO_Y + fila * TAMANO_CELDA);
			
			if (nodo->celdas[columna] == 0)
			{
				celda.setFillColor(Color(15, 15, 15));
			}
			else
			{
				celda.setFillColor(colorPieza(piezaActual.tipo));
			}
			
			ventana.draw(celda);
		}
	}
}

void dibujarGameOver(RenderWindow &ventana)
{
	RectangleShape fondo(Vector2f(500, 220));
	
	fondo.setPosition(350, 300);
	fondo.setFillColor(Color(5, 10, 30, 230));
	fondo.setOutlineColor(Color(0, 150, 255));
	fondo.setOutlineThickness(4);
	ventana.draw(fondo);
	dibujarTexto(ventana, "GAME OVER", 455, 340, 42);
	dibujarTexto(ventana, "Puntaje: " + to_string(puntaje), 455, 400, 24);
	dibujarTexto(ventana, "ESC para salir", 455, 450, 20);
}
