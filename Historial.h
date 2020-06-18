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

	string codigoActivo;

	NodoHistorial(string alfaNumerico,int codigo,string nombreaActivo,NodoTablero* usuario, string fecha, string tiempo, bool disponibilidad) {
		this->siguiente = 0;
		this->anterior = 0;

		this->codigo = codigo;
		this->nombreActivo = nombreaActivo;
		this->usuario = usuario;
		this->fechaRenta = fecha;
		this->tiempoRenta = tiempo;
		this->alfaNumerico = alfaNumerico;

	}

	NodoHistorial(string alfaNumerico, string codigoActivo, string nombreaActivo, NodoTablero* usuario, string fecha, string tiempo, bool disponibilidad) {
		this->siguiente = 0;
		this->anterior = 0;

		this->codigoActivo = codigoActivo;
		this->nombreActivo = nombreaActivo;
		this->usuario = usuario;
		this->fechaRenta = fecha;
		this->tiempoRenta = tiempo;
		this->alfaNumerico = alfaNumerico;
		this->disponibilidad = disponibilidad;
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

	//Alfa numerico de historia y de activo, nombre activo, usuario, fecha, tiempo
	void insertar(string alfaNumerico,int id,string nombreActivo, NodoTablero* usuario, string fecha, string tiempo, bool disponibilidad = true);

	void insertar(string alfaNumerico, string idActivo, string nombreActivo, NodoTablero* usuario, string fecha, string tiempo, bool disponibilidad = true);

	void ordenarMayorMenor();
	void ordenarMenorMayor();
	void recorrer();
	bool verificarExistencia(int id);
	void graficar();
	void graficarAlReves();

	void graficarXusuario(NodoTablero* usuario);

	void devolucion(NodoTablero* usuario, string idActivo);

};

