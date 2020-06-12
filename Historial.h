#pragma once
#include <iostream>
#include <string>
#include "Tablero.h"

using namespace std;

class NodoHistorial {
public:
	NodoHistorial* siguiente;
	NodoHistorial* anterior;

	int codigo;
	NodoTablero* usuario;
	string fechaRenta;
	string tiempoRenta;

	NodoHistorial(int codigo, NodoTablero* usuario, string fecha, string tiempo) {
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
private:
	NodoHistorial* primero;
	NodoHistorial* ultimo;
public:
	Historial() {
		this->primero = 0;
		this->ultimo = 0;
	}

	void insertar(int id, NodoTablero* usuario, string fecha, string tiempo);
	void ordenarMayorMenor();
	void ordenarMenorMayor();

};

