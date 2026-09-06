#include "pieza.h"

void inicializarPieza(Pieza &pieza, char tipo)
{
	pieza.tipo = tipo;
	pieza.fila = 0;
	pieza.columna = 3;
	pieza.orientacion = 0;
	
	for (int o = 0; o < 4; o++)
	{
		for (int b = 0; b < 4; b++)
		{
			pieza.bloques[o][b][0] = 0;
			pieza.bloques[o][b][1] = 0;
		}
	}
	
	// Pieza I
	if (tipo == 'I')
	{
		// Orientacion 0
		pieza.bloques[0][0][0] = 0;
		pieza.bloques[0][0][1] = 1;
		pieza.bloques[0][1][0] = 1;
		pieza.bloques[0][1][1] = 1;
		pieza.bloques[0][2][0] = 2;
		pieza.bloques[0][2][1] = 1;
		pieza.bloques[0][3][0] = 3;
		pieza.bloques[0][3][1] = 1;
		
		// Orientacion 1
		pieza.bloques[1][0][0] = 2;
		pieza.bloques[1][0][1] = 0;
		pieza.bloques[1][1][0] = 2;
		pieza.bloques[1][1][1] = 1;
		pieza.bloques[1][2][0] = 2;
		pieza.bloques[1][2][1] = 2;
		pieza.bloques[1][3][0] = 2;
		pieza.bloques[1][3][1] = 3;
		
		// Orientacion 2
		pieza.bloques[2][0][0] = 0;
		pieza.bloques[2][0][1] = 2;
		pieza.bloques[2][1][0] = 1;
		pieza.bloques[2][1][1] = 2;
		pieza.bloques[2][2][0] = 2;
		pieza.bloques[2][2][1] = 2;
		pieza.bloques[2][3][0] = 3;
		pieza.bloques[2][3][1] = 2;
		
		// Orientacion 3
		pieza.bloques[3][0][0] = 1;
		pieza.bloques[3][0][1] = 0;
		pieza.bloques[3][1][0] = 1;
		pieza.bloques[3][1][1] = 1;
		pieza.bloques[3][2][0] = 1;
		pieza.bloques[3][2][1] = 2;
		pieza.bloques[3][3][0] = 1;
		pieza.bloques[3][3][1] = 3;
	}
	
	// Pieza O
	else if (tipo == 'O')
	{
		for (int o = 0; o < 4; o++)
		{
			pieza.bloques[o][0][0] = 1;
			pieza.bloques[o][0][1] = 0;
			pieza.bloques[o][1][0] = 2;
			pieza.bloques[o][1][1] = 0;
			pieza.bloques[o][2][0] = 1;
			pieza.bloques[o][2][1] = 1;
			pieza.bloques[o][3][0] = 2;
			pieza.bloques[o][3][1] = 1;
		}
	}
	
	// Pieza T
	else if (tipo == 'T')
	{
		// Orientacion 0
		pieza.bloques[0][0][0] = 1;
		pieza.bloques[0][0][1] = 0;
		pieza.bloques[0][1][0] = 0;
		pieza.bloques[0][1][1] = 1;
		pieza.bloques[0][2][0] = 1;
		pieza.bloques[0][2][1] = 1;
		pieza.bloques[0][3][0] = 2;
		pieza.bloques[0][3][1] = 1;
		
		// Orientacion 1
		pieza.bloques[1][0][0] = 1;
		pieza.bloques[1][0][1] = 0;
		pieza.bloques[1][1][0] = 1;
		pieza.bloques[1][1][1] = 1;
		pieza.bloques[1][2][0] = 2;
		pieza.bloques[1][2][1] = 1;
		pieza.bloques[1][3][0] = 1;
		pieza.bloques[1][3][1] = 2;
		
		// Orientacion 2
		pieza.bloques[2][0][0] = 0;
		pieza.bloques[2][0][1] = 1;
		pieza.bloques[2][1][0] = 1;
		pieza.bloques[2][1][1] = 1;
		pieza.bloques[2][2][0] = 2;
		pieza.bloques[2][2][1] = 1;
		pieza.bloques[2][3][0] = 1;
		pieza.bloques[2][3][1] = 2;
		
		// Orientacion 3
		pieza.bloques[3][0][0] = 1;
		pieza.bloques[3][0][1] = 0;
		pieza.bloques[3][1][0] = 0;
		pieza.bloques[3][1][1] = 1;
		pieza.bloques[3][2][0] = 1;
		pieza.bloques[3][2][1] = 1;
		pieza.bloques[3][3][0] = 1;
		pieza.bloques[3][3][1] = 2;
	}
	
	// Pieza S
	else if (tipo == 'S')
	{
		// Orientacion 0
		pieza.bloques[0][0][0] = 1;
		pieza.bloques[0][0][1] = 0;
		pieza.bloques[0][1][0] = 2;
		pieza.bloques[0][1][1] = 0;
		pieza.bloques[0][2][0] = 0;
		pieza.bloques[0][2][1] = 1;
		pieza.bloques[0][3][0] = 1;
		pieza.bloques[0][3][1] = 1;
		
		// Orientacion 1
		pieza.bloques[1][0][0] = 0;
		pieza.bloques[1][0][1] = 0;
		pieza.bloques[1][1][0] = 0;
		pieza.bloques[1][1][1] = 1;
		pieza.bloques[1][2][0] = 1;
		pieza.bloques[1][2][1] = 1;
		pieza.bloques[1][3][0] = 1;
		pieza.bloques[1][3][1] = 2;
		
		// Orientacion 2 = igual a 0
		pieza.bloques[2][0][0] = 1;
		pieza.bloques[2][0][1] = 0;
		pieza.bloques[2][1][0] = 2;
		pieza.bloques[2][1][1] = 0;
		pieza.bloques[2][2][0] = 0;
		pieza.bloques[2][2][1] = 1;
		pieza.bloques[2][3][0] = 1;
		pieza.bloques[2][3][1] = 1;
		
		// Orientacion 3 = igual a 1
		pieza.bloques[3][0][0] = 0;
		pieza.bloques[3][0][1] = 0;
		pieza.bloques[3][1][0] = 0;
		pieza.bloques[3][1][1] = 1;
		pieza.bloques[3][2][0] = 1;
		pieza.bloques[3][2][1] = 1;
		pieza.bloques[3][3][0] = 1;
		pieza.bloques[3][3][1] = 2;
	}
	
	// Pieza Z
	else if (tipo == 'Z')
	{
		// Orientacion 0
		pieza.bloques[0][0][0] = 0;
		pieza.bloques[0][0][1] = 0;
		pieza.bloques[0][1][0] = 1;
		pieza.bloques[0][1][1] = 0;
		pieza.bloques[0][2][0] = 1;
		pieza.bloques[0][2][1] = 1;
		pieza.bloques[0][3][0] = 2;
		pieza.bloques[0][3][1] = 1;
		
		// Orientacion 1
		pieza.bloques[1][0][0] = 1;
		pieza.bloques[1][0][1] = 0;
		pieza.bloques[1][1][0] = 0;
		pieza.bloques[1][1][1] = 1;
		pieza.bloques[1][2][0] = 1;
		pieza.bloques[1][2][1] = 1;
		pieza.bloques[1][3][0] = 0;
		pieza.bloques[1][3][1] = 2;
		
		// Orientacion 2 = igual a 0
		pieza.bloques[2][0][0] = 0;
		pieza.bloques[2][0][1] = 0;
		pieza.bloques[2][1][0] = 1;
		pieza.bloques[2][1][1] = 0;
		pieza.bloques[2][2][0] = 1;
		pieza.bloques[2][2][1] = 1;
		pieza.bloques[2][3][0] = 2;
		pieza.bloques[2][3][1] = 1;
		
		// Orientacion 3 = igual a 1
		pieza.bloques[3][0][0] = 1;
		pieza.bloques[3][0][1] = 0;
		pieza.bloques[3][1][0] = 0;
		pieza.bloques[3][1][1] = 1;
		pieza.bloques[3][2][0] = 1;
		pieza.bloques[3][2][1] = 1;
		pieza.bloques[3][3][0] = 0;
		pieza.bloques[3][3][1] = 2;
	}
	
	// Pieza J
	else if (tipo == 'J')
	{
		// Orientacion 0
		pieza.bloques[0][0][0] = 0;
		pieza.bloques[0][0][1] = 0;
		pieza.bloques[0][1][0] = 0;
		pieza.bloques[0][1][1] = 1;
		pieza.bloques[0][2][0] = 1;
		pieza.bloques[0][2][1] = 1;
		pieza.bloques[0][3][0] = 2;
		pieza.bloques[0][3][1] = 1;
		
		// Orientacion 1
		pieza.bloques[1][0][0] = 0;
		pieza.bloques[1][0][1] = 0;
		pieza.bloques[1][1][0] = 1;
		pieza.bloques[1][1][1] = 0;
		pieza.bloques[1][2][0] = 0;
		pieza.bloques[1][2][1] = 1;
		pieza.bloques[1][3][0] = 0;
		pieza.bloques[1][3][1] = 2;
		
		// Orientacion 2
		pieza.bloques[2][0][0] = 0;
		pieza.bloques[2][0][1] = 0;
		pieza.bloques[2][1][0] = 1;
		pieza.bloques[2][1][1] = 0;
		pieza.bloques[2][2][0] = 2;
		pieza.bloques[2][2][1] = 0;
		pieza.bloques[2][3][0] = 2;
		pieza.bloques[2][3][1] = 1;
		
		// Orientacion 3
		pieza.bloques[3][0][0] = 1;
		pieza.bloques[3][0][1] = 0;
		pieza.bloques[3][1][0] = 1;
		pieza.bloques[3][1][1] = 1;
		pieza.bloques[3][2][0] = 0;
		pieza.bloques[3][2][1] = 2;
		pieza.bloques[3][3][0] = 1;
		pieza.bloques[3][3][1] = 2;
	}
	
	// Pieza L
	else if (tipo == 'L')
	{
		// Orientacion 0
		pieza.bloques[0][0][0] = 2;
		pieza.bloques[0][0][1] = 0;
		pieza.bloques[0][1][0] = 0;
		pieza.bloques[0][1][1] = 1;
		pieza.bloques[0][2][0] = 1;
		pieza.bloques[0][2][1] = 1;
		pieza.bloques[0][3][0] = 2;
		pieza.bloques[0][3][1] = 1;
		
		// Orientacion 1
		pieza.bloques[1][0][0] = 0;
		pieza.bloques[1][0][1] = 0;
		pieza.bloques[1][1][0] = 0;
		pieza.bloques[1][1][1] = 1;
		pieza.bloques[1][2][0] = 0;
		pieza.bloques[1][2][1] = 2;
		pieza.bloques[1][3][0] = 1;
		pieza.bloques[1][3][1] = 2;
		
		// Orientacion 2
		pieza.bloques[2][0][0] = 0;
		pieza.bloques[2][0][1] = 0;
		pieza.bloques[2][1][0] = 1;
		pieza.bloques[2][1][1] = 0;
		pieza.bloques[2][2][0] = 2;
		pieza.bloques[2][2][1] = 0;
		pieza.bloques[2][3][0] = 0;
		pieza.bloques[2][3][1] = 1;
		
		// Orientacion 3
		pieza.bloques[3][0][0] = 0;
		pieza.bloques[3][0][1] = 0;
		pieza.bloques[3][1][0] = 1;
		pieza.bloques[3][1][1] = 0;
		pieza.bloques[3][2][0] = 1;
		pieza.bloques[3][2][1] = 1;
		pieza.bloques[3][3][0] = 1;
		pieza.bloques[3][3][1] = 2;
	}
}
