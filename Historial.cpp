#include "Historial.h"


void Historial::insertar(string alfaNumerico, int id, string nombreActivo, NodoTablero* usuario, string fecha, string tiempo, bool a) {
	NodoHistorial* nuevo = new NodoHistorial(alfaNumerico, id, nombreActivo, usuario, fecha, tiempo,a);

	if (this->primero == 0) {
		this->primero = this->ultimo = nuevo;
		primero->anterior = ultimo;
		ultimo->siguiente = primero;
	}
	else {
		//Insertar ordenado
		NodoHistorial* auxiliar = this->primero;

		if (nuevo->alfaNumerico < this->primero->alfaNumerico) {
			nuevo->siguiente = primero;
			primero->anterior = nuevo;

			primero = nuevo;

			primero->anterior = ultimo;
			ultimo->siguiente = primero;
		}
		else if (nuevo->alfaNumerico > this->ultimo->alfaNumerico) {
			nuevo->anterior = ultimo;
			ultimo->siguiente = nuevo;

			ultimo = nuevo;

			ultimo->siguiente = primero;
			primero->anterior = ultimo;
		}
		else {
			//Insertar al medio de 
			NodoHistorial* auxiliar = this->primero;

			do {
				if (auxiliar->alfaNumerico < nuevo->alfaNumerico && auxiliar->siguiente->alfaNumerico > nuevo->alfaNumerico) {
					auxiliar->siguiente->anterior = nuevo;
					nuevo->siguiente = auxiliar->siguiente;
					nuevo->anterior = auxiliar;
					auxiliar->siguiente = nuevo;


				}
				auxiliar = auxiliar->siguiente;
			} while (auxiliar != primero);
		}



	}
}


void Historial::insertar(string alfaNumerico, string id, string nombreActivo, NodoTablero* usuario, string fecha, string tiempo, bool a) {
	NodoHistorial* nuevo = new NodoHistorial(alfaNumerico, id, nombreActivo, usuario, fecha, tiempo,a);

	if (this->primero == 0) {
		this->primero = this->ultimo = nuevo;
		primero->anterior = ultimo;
		ultimo->siguiente = primero;
	}
	else {
		//Insertar ordenado
		NodoHistorial* auxiliar = this->primero;

		if (nuevo->alfaNumerico < this->primero->alfaNumerico) {
			nuevo->siguiente = primero;
			primero->anterior = nuevo;

			primero = nuevo;

			primero->anterior = ultimo;
			ultimo->siguiente = primero;
		}
		else if (nuevo->alfaNumerico > this->ultimo->alfaNumerico) {
			nuevo->anterior = ultimo;
			ultimo->siguiente = nuevo;

			ultimo = nuevo;

			ultimo->siguiente = primero;
			primero->anterior = ultimo;
		}
		else {
			//Insertar al medio de 
			NodoHistorial* auxiliar = this->primero;

			do {
				if (auxiliar->alfaNumerico < nuevo->alfaNumerico && auxiliar->siguiente->alfaNumerico > nuevo->alfaNumerico) {
					auxiliar->siguiente->anterior = nuevo;
					nuevo->siguiente = auxiliar->siguiente;
					nuevo->anterior = auxiliar;
					auxiliar->siguiente = nuevo;


				}
				auxiliar = auxiliar->siguiente;
			} while (auxiliar != primero);
		}



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

void Historial::recorrer() {
	if (this->primero != 0) {
		NodoHistorial* auxiliar = this->primero;

		do {
			cout << auxiliar->nombreActivo << endl;
			auxiliar = auxiliar->siguiente;
		} while (auxiliar != primero);
	}
}

void Historial::ordenarMayorMenor() {
	if (this->primero != 0) {
		cout << "-------------------Transacciones de Maynor a Menor-------------------" << endl;
		NodoHistorial* auxiliar = this->ultimo;
		do {
			cout << "----------------------------------------------------------" << endl;
			cout << "Codigo transaccion: " << auxiliar->alfaNumerico << endl;
			cout << "Id de activo: " << auxiliar->codigo << endl;
			cout << "Nombre activo: " << auxiliar->nombreActivo << endl;
			cout << "Nombre de usuario: " << auxiliar->usuario->empleado->getNombre() << endl;
			cout << "Fecha de renta: " << auxiliar->fechaRenta << endl;
			cout << "Tiempo de renta: " << auxiliar->tiempoRenta << endl;
			cout << "----------------------------------------------------------" << endl;
			auxiliar = auxiliar->anterior;
		} while (auxiliar != ultimo);
	}
}

void Historial::ordenarMenorMayor() {
	if (this->primero != 0) {
		cout << "-------------------Transacciones de Menor a Mayor-------------------" << endl;
		NodoHistorial* auxiliar = this->primero;

		do {
			cout << "----------------------------------------------------------" << endl;
			cout << "Codigo transaccion: " << auxiliar->alfaNumerico << endl;
			cout << "Id de activo: " << auxiliar->codigo << endl;
			cout << "Nombre activo: " << auxiliar->nombreActivo << endl;
			cout << "Nombre de usuario: " << auxiliar->usuario->empleado->getNombre() << endl;
			cout << "Fecha de renta: " << auxiliar->fechaRenta << endl;
			cout << "Tiempo de renta: " << auxiliar->tiempoRenta << endl;
			cout << "----------------------------------------------------------" << endl;

			auxiliar = auxiliar->siguiente;
		} while (auxiliar != primero);
	}
}

void Historial::graficar() {
	if (this->primero == 0) {
		cout << "No se han realizado transacciones " << endl;
	}
	else {
		ofstream archivo("Transacciones.dot");
		archivo << "digraph a{" << endl;
		archivo << "rankdir = LR" << endl;
		archivo << "node[shape = rectangle]" << endl;

		NodoHistorial* auxiliar = this->primero;

		do {
			if (auxiliar->disponibilidad == true) {
				archivo << "X" << auxiliar << "[label = \"Id_Transaccion: " << auxiliar->alfaNumerico << "\nNombre Activo: " << auxiliar->nombreActivo << "\nUsuario: " << auxiliar->usuario->empleado->getNombre() << "\nFecha: " << auxiliar->fechaRenta << "\nRentado\"]" << endl;
			}
			else {
				archivo << "X" << auxiliar << "[label = \"Id_Transaccion: " << auxiliar->alfaNumerico << "\nNombre Activo: " << auxiliar->nombreActivo << "\nUsuario: " << auxiliar->usuario->empleado->getNombre() << "\nFecha: " << auxiliar->fechaRenta << "\Renta cancelada\"]" << endl;
			}
			auxiliar = auxiliar->siguiente;
		} while (auxiliar != this->primero);

		auxiliar = this->primero;

		do {
			if (auxiliar->siguiente != 0) {
				archivo << "X" << auxiliar << "-> X" << auxiliar->siguiente << endl;
			}
			if (auxiliar->anterior != 0) {
				archivo << "X" << auxiliar << "-> X" << auxiliar->anterior << endl;
			}
			auxiliar = auxiliar->siguiente;
		} while (auxiliar != primero);
		archivo << "}" << endl;
		archivo.close();

		system("dot -Tpng Transacciones.dot -o Transacciones.png");
		system("Transacciones.png");

	}
}

void Historial::graficarAlReves() {
	if (this->primero == 0) {
		cout << "No se han realizado transacciones " << endl;
	}
	else {
		ofstream archivo("TransaccionesR.dot");
		archivo << "digraph a{" << endl;
		archivo << "rankdir = LR" << endl;
		archivo << "node[shape = rectangle]" << endl;

		NodoHistorial* auxiliar = this->ultimo;

		do {
		
			if (auxiliar->disponibilidad == true) {
				archivo << "X" << auxiliar << "[label = \"Id_Transaccion: " << auxiliar->alfaNumerico << "\nNombre Activo: " << auxiliar->nombreActivo << "\nUsuario: " << auxiliar->usuario->empleado->getNombre() << "\nFecha: " << auxiliar->fechaRenta << "\nRentado\"]" << endl;
			}
			else {
				archivo << "X" << auxiliar << "[label = \"Id_Transaccion: " << auxiliar->alfaNumerico << "\nNombre Activo: " << auxiliar->nombreActivo << "\nUsuario: " << auxiliar->usuario->empleado->getNombre() << "\nFecha: " << auxiliar->fechaRenta << "\Renta cancelada\"]" << endl;
			}
			auxiliar = auxiliar->anterior;
		} while (auxiliar != this->ultimo);

		auxiliar = this->ultimo;

		do {
			if (auxiliar->siguiente != 0) {
				archivo << "X" << auxiliar << "-> X" << auxiliar->siguiente << endl;
			}
			if (auxiliar->anterior != 0) {
				archivo << "X" << auxiliar << "-> X" << auxiliar->anterior << endl;
			}
			auxiliar = auxiliar->anterior;
		} while (auxiliar != ultimo);
		archivo << "}" << endl;
		archivo.close();

		system("dot -Tpng TransaccionesR.dot -o TransaccionesR.png");
		system("TransaccionesR.png");

	}
}

void Historial::graficarXusuario(NodoTablero* usuario) {
	if (this->primero == 0) {
		cout << "No se han realizado transacciones " << endl;
	}
	else {
		ofstream archivo("TransaccionesXusuario.dot");
		archivo << "digraph a{" << endl;
		archivo << "rankdir = LR" << endl;
		archivo << "node[shape = rectangle]" << endl;

		archivo << "compound = true;" << endl;

		NodoHistorial* auxiliar = this->primero;

		archivo << "subgraph cluster0{" << endl;

		archivo << "Titular[label = \"" << usuario->empleado->getUser() << "\"]" << endl;
		archivo << "label = \"Usuario\"" << endl;
		archivo << "}" << endl;

		archivo << endl << endl;
		archivo << "subgraph cluster1{" << endl;
		NodoHistorial* primer = 0;
		archivo << "label = \"Transacciones\"" << endl;
		do {
			if (auxiliar->usuario == usuario) {
				primer = auxiliar;
				cout << "Si entroa" << endl;
				if (auxiliar->disponibilidad == true) {
					archivo << "X" << auxiliar << "[label = \"Id_Transaccion: " << auxiliar->alfaNumerico << "\nNombre Activo: " << auxiliar->nombreActivo << "\nUsuario: " << auxiliar->usuario->empleado->getNombre() << "\nFecha: " << auxiliar->fechaRenta << "\nRentado\"]" << endl;
				}
				else {
					archivo << "X" << auxiliar << "[label = \"Id_Transaccion: " << auxiliar->alfaNumerico << "\nNombre Activo: " << auxiliar->nombreActivo << "\nUsuario: " << auxiliar->usuario->empleado->getNombre() << "\nFecha: " << auxiliar->fechaRenta << "\Renta cancelada\"]" << endl;
				}

			}

			auxiliar = auxiliar->siguiente;
		} while (auxiliar != this->primero);

		archivo << "}" << endl;


		archivo << endl;
		archivo << "Titular -> X" << primer << "[ltail=cluster0 lhead=cluster1]" << endl;


		/*
		do {
			if (auxiliar->siguiente != 0) {
				archivo << "X" << auxiliar << "-> X" << auxiliar->siguiente << endl;
			}
			if (auxiliar->anterior != 0) {
				archivo << "X" << auxiliar << "-> X" << auxiliar->anterior << endl;
			}
			auxiliar = auxiliar->siguiente;
		} while (auxiliar != primero);
		*/
		archivo << "}" << endl;
		archivo.close();

		system("dot -Tpng TransaccionesXusuario.dot -o TransaccionesXusuario.png");
		system("TransaccionesXusuario.png");

	}
}

void Historial::devolucion(NodoTablero* usuario, string idActivo) {
	NodoHistorial* auxiliar = this->primero;

	do {

		if (auxiliar->usuario == usuario && auxiliar->codigoActivo == idActivo) {
			auxiliar->disponibilidad = false;
			return;
		}

		auxiliar = auxiliar->siguiente;
	} while (auxiliar != primero);
}