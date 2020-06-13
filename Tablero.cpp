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
	NodoTablero* depart =
		new NodoTablero(departamento, new DatosEmpleado("", "", "", ActivosRenta(), "", ""));
	NodoTablero* auxiliar = this->cabecera;

	while (auxiliar->siguiente != 0) {
		auxiliar = auxiliar->siguiente;
	}

	auxiliar->siguiente = depart;
	depart->anterior = auxiliar;

	return depart;
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

	NodoTablero* nUsuario = new NodoTablero(usernarme,
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
				while (auxiliarDepartamento->anterior != 0) {
					if (auxiliarDepartamento->nombre == departamento) {
						nUsuario->siguiente = auxiliar;
						nUsuario->anterior = auxiliar->anterior;

						auxiliar->anterior->siguiente = nUsuario;
						auxiliar->anterior = nUsuario;
						break;
					}
					auxiliarDepartamento = auxiliarDepartamento->anterior;
				}

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

NodoTablero* Tablero::buscarNodo(string usuario, string departamento, string empresa) {
	NodoTablero* auxiliar = this->cabecera;
	while (auxiliar != 0) {
		NodoTablero* auxiliar1 = auxiliar->abajo;
		while (auxiliar1 != 0) {

			if (auxiliar1->nombre == usuario && auxiliar1->empleado->getDepartamento() == departamento && auxiliar1->empleado->getEmpresa() == empresa) {

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

int Tablero::grupoColumna(NodoTablero* nodo) {
	NodoTablero* col = cabecera->siguiente;

	int group = 2;

	while (col != 0) {
		if (nodo->nombre == col->nombre) {
			return group;
		}
		group++;
		col = col->siguiente;
	}
	return 0;
}

int Tablero::idGrupoColumna(NodoTablero* nodo) {
	NodoTablero* col = cabecera->siguiente;
	int id = 0;

	while (col != 0) {
		if (col->nombre == nodo->nombre) {
			return id;
		}
		id++;
		col = col->siguiente;
	}
	return 0;
}

void Tablero::graficar() {
	ofstream archivo("Matriz.dot");


	archivo << "digraph a{" << endl;
	archivo << "node[shape=box];" << endl;




	NodoTablero* auxiliar = this->cabecera;
	archivo << "C" << cabecera << "[ label = \"Matrix\", width = 1.5, style = filled, fillcolor = firebrick1, group = 1 ];" << endl;

	//Alineacion en vertical

	auxiliar = this->cabecera->abajo;

	int contador = 0;
	int contadorAbajo = 0;
	while (auxiliar != 0) {
		archivo << "U" << contadorAbajo << " [label = \"" << auxiliar->nombre << "\"    pos = \"5.3, 3.5!\" width = 1.5 style = filled, fillcolor = bisque1, group = 1 ];" << endl;
		contadorAbajo++;
		auxiliar = auxiliar->abajo;
	}

	auxiliar = this->cabecera;
	archivo << "C" << cabecera << "->" << "U" << 0 << endl;

	auxiliar = this->cabecera->abajo;

	contadorAbajo = 0;
	int salvad = 0;
	while (auxiliar != 0) {
		archivo << "U" << contadorAbajo << "-> U" << contadorAbajo + 1 << endl;
		archivo << "U" << contadorAbajo + 1 << "-> U" << contadorAbajo << endl;
		contadorAbajo++;
		auxiliar = auxiliar->abajo;
	}

	//Alineacion en horizontal
	archivo << endl << endl;
	auxiliar = this->cabecera->siguiente;

	contador = 2;
	int contadorVertical = 0;

	while (auxiliar != 0) {
		archivo << "A" << contadorVertical << " [label = " << auxiliar->nombre << "   width = 1.5 style = filled, fillcolor = lightskyblue, group = " << contador << " ];" << endl;
		auxiliar->grupo_graf = contador;
		contador++;
		contadorVertical++;
		auxiliar = auxiliar->siguiente;
	}

	auxiliar = this->cabecera;
	archivo << "C" << auxiliar << "->" << "A" << 0 << endl;

	auxiliar = this->cabecera->siguiente;
	int contenedor = contadorVertical;
	contadorVertical = 0;

	salvad = 0;
	while (auxiliar != 0) {
		if (contenedor != contadorVertical) {

			archivo << "A" << contadorVertical << "-> A" << contadorVertical + 1 << endl;
			archivo << "A" << contadorVertical + 1 << "-> A" << contadorVertical << endl;
		}
		contadorVertical++;

		auxiliar = auxiliar->abajo;
	}

	archivo << "{rank = same;" << endl;
	auxiliar = this->cabecera;
	archivo << "C" << auxiliar << ";" << endl;
	auxiliar = this->cabecera->siguiente;
	contadorVertical = 0;
	while (auxiliar != 0) {
		archivo << "A" << contadorVertical << ";" << endl;
		contadorVertical++;
		auxiliar = auxiliar->siguiente;
	}
	archivo << "}" << endl;

	archivo << endl << endl;

	auxiliar = this->cabecera->abajo;
	int idNodo = 0;


	while (auxiliar != 0) {
		NodoTablero* node = auxiliar->siguiente;

		while (node != 0) {
			archivo << "N" << idNodo << "[label =" << "\"" << node->nombre << "\" width = 1.5, group =" << grupoColumna(node) << "];" << endl;
			NodoTablero* nodo3D = node->atras;

			while (nodo3D != 0) {
				idNodo++;
				archivo << "N" << idNodo << "[label =" << "\"" << nodo3D->nombre << "\" width = 1.5, group =" << grupoColumna(nodo3D) << "];" << endl;
				nodo3D = nodo3D->atras;
			}
			idNodo++;
			node = node->siguiente;
		}

		auxiliar = auxiliar->abajo;
	}

	archivo << endl;

	auxiliar = cabecera->abajo;
	idNodo = 0;
	int u = 0;

	while (auxiliar != 0) {
		NodoTablero* node = auxiliar->siguiente;

		while (node != 0) {
			if (node->anterior->empleado->getUser() == "") {
				archivo << "U" << u << "-> N" << idNodo << endl;
				archivo << "N" << idNodo << "->U" << u << endl;
			}
			else {
				if (node->anterior->atras == 0) {
					archivo << "N" << idNodo << "-> N" << idNodo - 1 << endl;
					archivo << "N" << idNodo - 1 << "-> N" << idNodo << endl;
				}
				else {
					archivo << "N" << idNodo << "->" << "N" << idNodo - 2 << ";" << endl;
					archivo << "N" << idNodo - 2 << "->" << "N" << idNodo << ";" << endl;
				}
			}

			if (node->arriba->empleado->getUser() == "") {
				archivo << "A" << idGrupoColumna(node->arriba) << "->" << "N" << idNodo << ";" << endl;
				archivo << "N" << idNodo << "->" << "A" << idGrupoColumna(node->arriba) << ";" << endl;
			}
			else {
				archivo << "N" << idNodo << "->" << "N" << idGrupoColumna(node->arriba) << ";" << endl;
				archivo << "N" << idGrupoColumna(node->arriba) << "->" << "N" << idNodo << ";" << endl;
			}

			NodoTablero* node3D = node->atras;
			while (node3D != 0) //----- VERIFICAR 3D ----
			{
				idNodo++;
				archivo << "N" << idNodo << "->" << "N" << idNodo - 1 << ";" << endl;
				archivo << "N" << idNodo - 1 << "->" << "N" << idNodo << ";" << endl;
				node3D = node3D->adelante;
			}

			idNodo++;
			node = node->siguiente;
		}
		u++;
		auxiliar = auxiliar->abajo;

	}


	archivo << endl;

	auxiliar = cabecera->abajo;
	idNodo = 0;
	u = 0;

	while (auxiliar != 0) {
		archivo << "{rank = same;U" << u << ";";
		NodoTablero* node = auxiliar->siguiente;
		while (node != 0)
		{
			archivo << "N" << idNodo << ";";

			NodoTablero* node3D = node->adelante;
			while (node3D != 0) //----- VERIFICAR 3D ----
			{
				idNodo++;
				node3D = node3D->adelante;
			}

			idNodo++;
			node = node->siguiente;
		}

		archivo << "}" << endl;
		u++;
		auxiliar = auxiliar->abajo;
	}

	archivo << "}" << endl;
	archivo.close();
}
