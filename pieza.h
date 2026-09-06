#ifndef PIEZA_H
#define PIEZA_H

struct Pieza
{
	char tipo;
	
	int fila;
	int columna;
	
	int orientacion;
	
	int bloques[4][4][2];
};

void inicializarPieza(Pieza &pieza, char tipo);
void rotarPieza(Pieza &pieza);

#endif
