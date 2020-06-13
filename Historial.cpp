#include "Historial.h"


void Historial::insertar(string alfaNumerico,int id, string nombreActivo, NodoTablero* usuario, string fecha, string tiempo) {
	NodoHistorial* nuevo = new NodoHistorial(alfaNumerico,id, nombreActivo, usuario, fecha, tiempo);

	if (this->primero == 0) {
		this->primero = this->ultimo = nuevo;
	}
	else {

		nuevo->anterior = ultimo;
		ultimo->siguiente = nuevo;

		ultimo = nuevo;

		ultimo->siguiente = primero;
		primero->anterior = ultimo;

	}
}

bool Historial::verificarExistencia(int id) {
	if (this->primero != 0) {
		NodoHistorial* auxiliar = this->primero;

		do {
			if (auxiliar->codigo == id) {
				return true;
			}
			auxiliar = auxiliar->siguiente;
		} while (auxiliar != primero);
	}
	else {
		cout << "No existe historial" << endl;
		return false;
	}
}