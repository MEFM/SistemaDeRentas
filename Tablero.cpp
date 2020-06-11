#include "Tablero.h"

NodoTablero* Tablero::crearEmpresa(string empresa) {
	NodoTablero* empre = new NodoTablero(empresa, new DatosEmpleado("", "", "", ActivosRenta(), "", ""));

	NodoTablero* auxiliar = this->cabecera;

	while (auxiliar->abajo != 0) {
		auxiliar = auxiliar->abajo;
	}

	auxiliar->abajo = empre;
	empre->arriba = auxiliar;

	return empre;
}

NodoTablero* Tablero::crearDepartamento(string departamento) {
	NodoTablero* depa = 
		new NodoTablero(departamento, new DatosEmpleado("", "", "", ActivosRenta(), "", ""));
	NodoTablero* auxiliar = this->cabecera;

	while (auxiliar->siguiente != 0) {
		auxiliar = auxiliar->siguiente;
	}

	auxiliar->siguiente = depa;
	depa->anterior = auxiliar;

	return depa;
}

NodoTablero* Tablero::buscarEmpresa(string empresa, NodoTablero* inicio) {
	NodoTablero* auxiliar = inicio;

	while (auxiliar != 0) {
		if (auxiliar->nombre == empresa) {
			return auxiliar;
		}
		auxiliar = auxiliar->abajo;
	}
	return 0;
}

NodoTablero* Tablero::buscarDepa(string departamento, NodoTablero* inicio) {
	NodoTablero* auxiliar = inicio;

	while (auxiliar != 0) {
		if (auxiliar->nombre == departamento) {
			return auxiliar;
		}
		auxiliar = auxiliar->siguiente;
	}
	return 0;
}

bool Tablero::verificarDepa(string departamento, NodoTablero* inicio, NodoTablero* nodoUsuario) {
	NodoTablero* auxiliar = inicio->arriba;

	while (auxiliar->arriba != 0) {
		auxiliar = auxiliar->arriba;
	}

	if (auxiliar->nombre == departamento) {
		while (inicio->anterior != 0) {
			inicio = inicio->anterior;
		}
		inicio->atras = nodoUsuario;
		nodoUsuario->siguiente = inicio;
		return true;
	}
	return false;
}

bool Tablero::verificarEmpresa(string empresa, NodoTablero* inicio, NodoTablero* nodoUsuario) {
	NodoTablero* auxiliar = inicio->anterior;
	while (auxiliar->anterior != 0) {
		auxiliar = auxiliar->anterior;
	}
	if (auxiliar->nombre == empresa) {
		while (inicio->atras != 0) {
			inicio = inicio->atras;
		}
		inicio->atras = nodoUsuario;
		nodoUsuario->adelante = inicio;
		return true;
	}
	return false;
}

void Tablero::insertarElemento(string usernarme, string contraseña, string nombreCompleto, ActivosRenta rentas, string departamento, string empresa) {

	NodoTablero* nUsuario = new NodoTablero("",
		new DatosEmpleado(usernarme, contraseña, nombreCompleto, rentas, departamento, empresa));
	NodoTablero* nodoDepartamento = this->buscarDepa(departamento, cabecera);
	NodoTablero* nodoEmpresa = this->buscarEmpresa(empresa, cabecera);

	if (nodoDepartamento == 0) {
		nodoDepartamento = crearDepartamento(departamento);
	}
	if (nodoEmpresa == 0) {
		nodoEmpresa = crearEmpresa(empresa);
	}

	if (nodoDepartamento->abajo == 0) {
		nodoDepartamento->abajo = nUsuario;
		nUsuario->arriba = nodoDepartamento;
	}
	else if (nodoEmpresa->abajo == 0) {
		//Insertar hasta el final
		NodoTablero* auxiliar = nodoDepartamento->abajo;
		while (auxiliar->abajo != 0) {
			auxiliar = auxiliar->abajo;
		}
		if (!verificarEmpresa(empresa, auxiliar, nUsuario)) {
			auxiliar->abajo = nUsuario;
			nUsuario->arriba = auxiliar;
		}
	}
	else {
		//Insertar en medio
		NodoTablero* auxiliar = nodoDepartamento;
		do {
			auxiliar = auxiliar->abajo;
			if (!verificarEmpresa(empresa, auxiliar, nUsuario)) {
				NodoTablero* auxEmpresa = auxiliar->anterior;
				while (auxEmpresa->anterior != 0) {
					auxEmpresa = auxEmpresa->anterior;
				}
				while (auxEmpresa->arriba != 0) {
					if (auxEmpresa->nombre == empresa) {
						nUsuario->abajo = auxiliar;
						nUsuario->arriba = auxiliar->arriba;

						auxiliar->arriba->abajo = nUsuario;
						auxiliar->arriba = nUsuario;
						break;
					}
					auxEmpresa = auxEmpresa->arriba;
				}
			}
		} while (auxiliar->abajo != 0 && nUsuario->arriba == 0);

		if (nUsuario->arriba == 0 && nUsuario->adelante == 0) {
			auxiliar->abajo = nUsuario;
			nUsuario->arriba = auxiliar;
		}
	}

	//Asegurarnos que no hemos insertado en Z

	if (nUsuario->adelante != 0) {
		return;
	}

	//Insertar en empresa
		//Insertar al inicio
	if (nodoEmpresa->siguiente == 0) {
		nodoEmpresa->siguiente = nUsuario;
		nUsuario->anterior = nodoEmpresa;
	}
	else if (nodoDepartamento->siguiente == 0) {
		//insertar al final
		NodoTablero* aux = nodoEmpresa->siguiente;
		while (aux->siguiente != 0) {
			aux = aux->siguiente;
		}
		if (!verificarDepa(departamento, aux, nUsuario)) {

			aux->siguiente = nUsuario;
			nUsuario->anterior = aux;
		}
	}
	else {
		//Insertar al medio
		NodoTablero* auxiliar = nodoEmpresa;

		do {
			auxiliar = auxiliar->siguiente;

			if (!verificarDepa(departamento, auxiliar, nUsuario)) {
				NodoTablero* auxiliarDepartamento = auxiliar->arriba;
				while (auxiliarDepartamento->arriba != 0)
				{
					auxiliarDepartamento = auxiliarDepartamento->arriba;
				}
				if (auxiliarDepartamento->nombre == departamento) {
					nUsuario->siguiente = auxiliar;
					nUsuario->anterior = auxiliar->anterior;

					auxiliar->anterior->siguiente = nUsuario;
					auxiliar->anterior = nUsuario;
					break;
				}
				auxiliarDepartamento = auxiliarDepartamento->anterior;
			}

		} while (auxiliar->siguiente != 0 && nUsuario->anterior == 0);

		if (nUsuario->anterior == 0 && nUsuario->adelante == 0) {
			auxiliar->siguiente = nUsuario;
			nUsuario->anterior = auxiliar;
		}

	}

}

NodoTablero* Tablero::buscarNodo(string usuario) {
	NodoTablero* auxiliar = this->cabecera;
	while (auxiliar != 0) {
		NodoTablero* auxiliar1 = auxiliar->abajo;
		while (auxiliar1 != 0) {

			if (auxiliar1->nombre == usuario) {

				return auxiliar1;

			}
			else if (auxiliar1->atras != 0) {
				NodoTablero* auxiliar2 = auxiliar1;

				while (auxiliar2 != 0) {
					if (auxiliar2->nombre == usuario) {
						return auxiliar2;
					}

					auxiliar2 = auxiliar2->atras;
				}
			}

			auxiliar1 = auxiliar1->abajo;
		}

		auxiliar = auxiliar->siguiente;
	}
	return 0;
}

void Tablero::recorrerTablero() {
	NodoTablero* auxiliar = this->cabecera->siguiente;

	while (auxiliar != 0) {
		NodoTablero* auxiliar1 = auxiliar->abajo;
		while (auxiliar1 != 0) {
			NodoTablero* auxiliar2 = auxiliar1;
			if (auxiliar1->atras != 0) {
				while (auxiliar2 != 0) {
					cout << auxiliar2->empleado->getUser() << endl;
					auxiliar2 = auxiliar2->atras;
				}
			}
			else {
				cout << auxiliar1->empleado->getUser() << endl;
			}

			auxiliar1 = auxiliar1->abajo;
		}
		auxiliar = auxiliar->siguiente;
	}
}

void Tablero::graficar() {
	ofstream archivo("Matriz.dot");


	archivo << "digraph a{" << endl;
	archivo << "node[shape=box];" << endl;




	NodoTablero* auxiliar = this->cabecera;
	archivo << auxiliar << "[ label = \"Matrix\", width = 1.5, style = filled, fillcolor = firebrick1, group = 1 ];" << endl;

	//Alineacion en vertical

	auxiliar = this->cabecera->abajo;

	int contador = 0;

	while (auxiliar != 0) {
		archivo << "U" << auxiliar << " [label = \"" << auxiliar->nombre << "\"    pos = \"5.3, 3.5!\" width = 1.5 style = filled, fillcolor = bisque1, group = 1 ];" << endl;
		auxiliar = auxiliar->abajo;
	}

	auxiliar = this->cabecera;
	archivo << auxiliar << "->" << "U" << auxiliar->abajo << endl;

	auxiliar = this->cabecera->abajo;

	int salvad = 0;
	while (auxiliar != 0) {
		if (auxiliar->abajo != 0)
			archivo << "U" << auxiliar << "-> U" << auxiliar->abajo << endl;


		if (auxiliar->arriba != 0) {
			if (salvad != 0)
				archivo << "U" << auxiliar << "-> U" << auxiliar->arriba << endl;
		}

		salvad++;
		auxiliar = auxiliar->abajo;
	}

	//Alineacion en horizontal
	archivo << endl << endl;
	auxiliar = this->cabecera->siguiente;

	contador = 2;

	while (auxiliar != 0) {
		archivo << "A" << auxiliar << " [label = " << auxiliar->nombre << "   width = 1.5 style = filled, fillcolor = lightskyblue, group = " << contador << " ];" << endl;
		auxiliar->grupo_graf = contador;
		contador++;

		auxiliar = auxiliar->siguiente;
	}

	auxiliar = this->cabecera;
	archivo << auxiliar << "->" << "A" << auxiliar->siguiente << endl;

	auxiliar = this->cabecera->siguiente;

	salvad = 0;
	while (auxiliar != 0) {
		if (auxiliar->siguiente != 0)
			archivo << "A" << auxiliar << "-> A" << auxiliar->siguiente << endl;


		if (auxiliar->anterior != 0) {
			if (salvad != 0)
				archivo << "A" << auxiliar << "-> A" << auxiliar->anterior << endl;
		}
		salvad++;
		auxiliar = auxiliar->siguiente;
	}

	archivo << "{rank = same;" << endl;
	auxiliar = this->cabecera;
	archivo << auxiliar << ";" << endl;
	auxiliar = this->cabecera->siguiente;
	while (auxiliar != 0) {
		archivo << "A" << auxiliar << ";" << endl;
		auxiliar = auxiliar->siguiente;
	}
	archivo << "}" << endl;

	archivo << endl << endl;

	auxiliar = this->cabecera->abajo;
	NodoTablero* auxiliar2;

	contador = 2;
	while (auxiliar != 0) {

		auxiliar2 = auxiliar->siguiente;
		while (auxiliar2 != 0) {

			archivo << "N" << auxiliar << "_L" << auxiliar2 << " [label = \"" << auxiliar2->empleado->getUser() << "\" width = 1.5, group = " << auxiliar2->arriba->grupo_graf << " ];" << endl;
			auxiliar2->grupo_graf = auxiliar2->arriba->grupo_graf;
			auxiliar2 = auxiliar2->siguiente;
		}


		auxiliar = auxiliar->abajo;
	}


	auxiliar = this->cabecera->abajo;
	auxiliar2 = 0;

	contador = 2;
	while (auxiliar != 0) {

		auxiliar2 = auxiliar->siguiente;
		while (auxiliar2 != 0) {
			//archivo << "A" << auxiliar << "->" << "N" << auxiliar << "_L" << auxiliar2 << endl;

			archivo << "U" << auxiliar << "->" << "N" << auxiliar << "_L" << auxiliar2 << endl;
			auxiliar2 = auxiliar2->siguiente;
		}


		auxiliar = auxiliar->abajo;
	}

	

	archivo << "}" << endl;
	archivo.close();
}