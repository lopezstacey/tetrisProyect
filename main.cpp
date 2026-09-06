#include <iostream>
#include <cstdlib>
#include <ctime>

#include "pieza.h"
#include "cola.h"

using namespace std;

int main()
{
	srand(time(nullptr));
	
	Cola cola;
	inicializarCola(cola);
	
	generarBag(cola);
	
	cout << "Tetris iniciado" << endl;
	cout << "Piezas disponibles: " << cantidadCola(cola) << endl;
	
	return 0;
}
