#include <iostream>
#include "pieza.h"

using namespace std;

int main()
{
	Pieza pieza;
	
	inicializarPieza(pieza, 'T');
	
	cout << "Pieza: " << pieza.tipo << endl;
	
	for (int orientacion = 0; orientacion < 4; orientacion++)
	{
		cout << endl;
		cout << "Orientacion " << orientacion << ":" << endl;
		
		for (int bloque = 0; bloque < 4; bloque++)
		{
			cout << "("
				<< pieza.bloques[orientacion][bloque][0]
					<< ", "
					<< pieza.bloques[orientacion][bloque][1]
						<< ")" << endl;
		}
	}
	
	return 0;
}
