#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Tablero.h"

using namespace std;

class NodoHistorial {
public:
	NodoHistorial* siguiente;
	NodoHistorial* anterior;

	int codigo;
	string nombreActivo;
	NodoTablero* usuario;
	string fechaRenta;
	string tiempoRenta;
	string alfaNumerico;
	bool disponibilidad;

	NodoHistorial(string alfaNumerico,int codigo,string nombreaActivo,NodoTablero* usuario, string fecha, string tiempo) {
		this->siguiente = 0;
		this->anterior = 0;

		this->codigo = codigo;
		this->nombreActivo = nombreaActivo;
		this->usuario = usuario;
		this->fechaRenta = fecha;
		this->tiempoRenta = tiempo;
		this->alfaNumerico = alfaNumerico;

	}
};

class Historial
{
private:
	NodoHistorial* primero;
	NodoHistorial* ultimo;
	int contador;
public:
	Historial() {
		this->primero = 0;
		this->ultimo = 0;
	}

	void insertar(string alfaNumerico,int id,string nombreActivo, NodoTablero* usuario, string fecha, string tiempo);
	void ordenarMayorMenor();
	void ordenarMenorMayor();
	void recorrer();
	bool verificarExistencia(int id);
	void graficar();
	void graficarXusuario(NodoTablero* usuario);

};

