#pragma once
#include <iostream>
#include <string>
#include "Tablero.h"

using namespace std;

class NodoHistorial {
private:
	NodoHistorial* siguiente;
	NodoHistorial* anterior;

	string codigo;
	NodoTablero* usuario;
	string fechaRenta;
	string tiempoRenta;

public:
	NodoHistorial(string codigo, NodoTablero* usuario, string fecha, string tiempo) {
		this->siguiente = 0;
		this->anterior = 0;

		this->codigo = codigo;
		this->usuario = usuario;
		this->fechaRenta = fecha;
		this->tiempoRenta = tiempo;
	}
};

class Historial
{
};

