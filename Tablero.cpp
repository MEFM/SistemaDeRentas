#include "Tablero.h"

NodoTablero* Tablero::crearEmpresa(string empresa) {
	NodoTablero* empre = new NodoTablero(empresa, new DatosEmpleado("E", "E", "E", new ActivosRenta(), "E", "E"));

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
		new NodoTablero(departamento, new DatosEmpleado("D", "D", "D", new ActivosRenta(), "D", "D"));
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
		while (inicio->atras != 0) {
			inicio = inicio->atras;
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

void Tablero::insertarElemento(string usernarme, string contraseña, string nombreCompleto, ActivosRenta* rentas, string departamento, string empresa) {

	NodoTablero* nUsuario = new NodoTablero(usernarme,
		new DatosEmpleado(usernarme, contraseña, nombreCompleto, rentas, departamento, empresa));
	NodoTablero* nodoDepartamento = this->buscarDepa(departamento, cabecera);
	NodoTablero* nodoEmpresa = this->buscarEmpresa(empresa, cabecera);
	bool insertado = true;
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
					else if (nUsuario->adelante != 0) {
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
		if (nodo->empleado->getDepartamento() == col->nombre) {
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


int Tablero::node_idgraph(NodoTablero* temp)
{
	NodoTablero* auxiliar = cabecera->abajo;
	int node_id = 0;

	while (auxiliar != 0) {
		NodoTablero* node = auxiliar->siguiente;

		while (node != 0) {
			if (temp->empleado == node->empleado) {
				return node_id;
			}

			node_id++;
			node = node->siguiente;
		}


		auxiliar = auxiliar->abajo;
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
	archivo << "A" << contadorVertical++ << ";" << endl;
	archivo << "}" << endl;

	archivo << endl << endl;

	auxiliar = this->cabecera->abajo;
	int idNodo = 0;


	while (auxiliar != 0) {
		NodoTablero* node = auxiliar->siguiente;

		while (node != 0) {


			if (node->atras != 0) {
				archivo << "N" << idNodo << "[label =" << "\"" << node->nombre << "\" width = 1.5,style = filled, fillcolor = green, group =" << grupoColumna(node) << "];" << endl;
				cout << "Grupo " << grupoColumna(node) << endl;
			}
			else {
				archivo << "N" << idNodo << "[label =" << "\"" << node->nombre << "\" width = 1.5, group =" << grupoColumna(node) << "];" << endl;
				cout << "Grupo " << grupoColumna(node) << endl;
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
			
			//Link a la izquierda

			if (node->anterior->empleado->getNombre() == "E") {
				archivo << "U" << u << "->" << "N" << idNodo << ";" << endl;
				archivo << "N" << idNodo << "->" << "U" << u << ";" << endl;
			}
			else {

				archivo << "N" << idNodo << "->" << "N" << idNodo - 1 << ";" << endl;
				archivo << "N" << idNodo - 1 << "->" << "N" << idNodo << ";" << endl;

			}

			//Link hacia arriba

			if (node->arriba->empleado->getNombre() == "D") {
				archivo << "A" << idGrupoColumna(node->arriba) << "->" << "N" << idNodo << ";" << endl;
				archivo << "N" << idNodo << "->" << "A" << idGrupoColumna(node->arriba) << ";" << endl;
				cout << "Grupo " << idGrupoColumna(node->arriba) << endl;
			}
			else
			{
				archivo << "N" << idNodo << "->" << "N" << node_idgraph(node->arriba) << ";" << endl;
				archivo << "N" << node_idgraph(node->arriba) << "->" << "N" << idNodo << ";" << endl;
				//	cout << "Grupo " << idGrupoColumna(node->arriba) << endl;
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

			idNodo++;
			node = node->siguiente;
		}

		archivo << "}" << endl;
		u++;
		auxiliar = auxiliar->abajo;
	}

	archivo << "}" << endl;
	archivo.close();

	system("dot -Tpng Matriz.dot -o Matriz.png");
	system("Matriz.png");
}

void Tablero::reporteEmpresa(string empresa) {

	NodoTablero* auxiliar = this->cabecera->siguiente;
	ofstream archivo("GraficaEmpresa.dot");

	archivo << "digraph a{" << endl;

	archivo << "node[shape = record, style=filled, fillcolor=seashell2];" << endl;
	archivo << "compound = true" << endl;
	int contadorCluster = 0;

	while (auxiliar != 0) {
		if (auxiliar->nombre == empresa) {
			NodoTablero* auxiliar2 = auxiliar->abajo;

			while (auxiliar2 != 0) {

				if (auxiliar2->atras != 0) {
					NodoTablero* auxiliar3 = auxiliar2;
					while (auxiliar3 != 0) {
						archivo << auxiliar3->empleado->getRentas()->pasarDocumento(auxiliar3->nombre, contadorCluster);

						contadorCluster = contadorCluster + 2;
						auxiliar3 = auxiliar3->atras;
					}
				}
				else {
					cout << auxiliar2->nombre << endl;
					archivo << auxiliar2->empleado->getRentas()->pasarDocumento(auxiliar2->nombre, contadorCluster);
				}

				contadorCluster = contadorCluster + 2;
				auxiliar2 = auxiliar2->abajo;
			}

		}
		auxiliar = auxiliar->siguiente;
	}

	archivo << "}" << endl;
	archivo.close();

	system("dot -Tpng GraficaEmpresa.dot -o GraficaEmpresa.png");
	system("GraficaEmpresa.png");


}

void Tablero::reporteDepartamento(string departamento) {
	NodoTablero* auxiliar = this->cabecera->abajo;

	ofstream archivo("reporteDepartamento.dot");
	archivo << "digraph a{" << endl;

	archivo << "node[shape = record, style=filled, fillcolor=seashell2];" << endl;
	archivo << "compound = true" << endl;
	int contadorCluster = 0;

	while (auxiliar != 0) {

		if (auxiliar->nombre == departamento) {
			NodoTablero* auxiliar2 = auxiliar->siguiente;

			while (auxiliar2 != 0) {
				if (auxiliar2->atras != 0) {
					NodoTablero* auxiliar3 = auxiliar2;

					while (auxiliar3 != 0) {
						archivo << auxiliar3->empleado->getRentas()->pasarDocumento(auxiliar3->nombre, contadorCluster);

						contadorCluster = contadorCluster + 2;
						auxiliar3 = auxiliar3->atras;
					}
				}
				else {
					archivo << auxiliar2->empleado->getRentas()->pasarDocumento(auxiliar2->nombre, contadorCluster);
				}

				contadorCluster = contadorCluster + 2;
				auxiliar2 = auxiliar2->siguiente;
			}

		}


		auxiliar = auxiliar->abajo;
	}
	archivo << "}" << endl;
	archivo.close();

	system("dot -Tpng reporteDepartamento.dot -o reporteDepartamento.png");
	system("reporteDepartamento.png");


}

void Tablero::activosDisponibles() {

	NodoTablero* auxiliar = this->cabecera->siguiente;

	while (auxiliar != 0) {

		NodoTablero* auxiliar1 = auxiliar->abajo;
		while (auxiliar1 != 0) {

			if (auxiliar1->atras != 0) {
				NodoTablero* auxiliar2 = auxiliar1;
				
				while (auxiliar2 != 0) {
					auxiliar2->empleado->getRentas()->libres();

					auxiliar2 = auxiliar2->atras;
				}
			}
			else {
				auxiliar1->empleado->getRentas()->libres();
			}

			auxiliar1 = auxiliar1->abajo;
		}

		auxiliar = auxiliar->siguiente;
	}

}



NodoActivo* Tablero::reservarActivo(int codigo) {

	NodoTablero* auxiliar = this->cabecera->siguiente;
	NodoActivo* retorno = 0;

	while (auxiliar != 0) {

		NodoTablero* auxiliar1 = auxiliar->abajo;
		while (auxiliar1 != 0) {

			if (auxiliar1->atras != 0) {
				NodoTablero* auxiliar2 = auxiliar1->atras;

				while (auxiliar2 != 0) {
					//auxiliar2->empleado->getRentas()->libres();
					retorno = auxiliar2->empleado->getRentas()->buscarActivo(codigo);
					if (retorno != 0) {
						return retorno;
					}
					auxiliar2 = auxiliar2->atras;
				}
			}
			else {
//				auxiliar1->empleado->getRentas()->libres();
				retorno = auxiliar1->empleado->getRentas()->buscarActivo(codigo);
				if (retorno != 0) {
					return retorno;
				}
			}

			auxiliar1 = auxiliar1->abajo;
		}

		auxiliar = auxiliar->siguiente;
	}

	return 0;
}


NodoActivo* Tablero::reservarActivo(string codigoActivo) {

	NodoTablero* auxiliar = this->cabecera->siguiente;
	NodoActivo* retorno = 0;

	while (auxiliar != 0) {

		NodoTablero* auxiliar1 = auxiliar->abajo;
		while (auxiliar1 != 0) {

			if (auxiliar1->atras != 0) {
				NodoTablero* auxiliar2 = auxiliar1;

				while (auxiliar2 != 0) {
					//auxiliar2->empleado->getRentas()->libres();
					retorno = auxiliar2->empleado->getRentas()->buscarActivo(codigoActivo);
					if (retorno != 0) {
						return retorno;
					}
					auxiliar2 = auxiliar2->atras;
				}
			}
			else {
				//				auxiliar1->empleado->getRentas()->libres();
				retorno = auxiliar1->empleado->getRentas()->buscarActivo(codigoActivo);
				if (retorno != 0) {
					return retorno;
				}
			}

			auxiliar1 = auxiliar1->abajo;
		}

		auxiliar = auxiliar->siguiente;
	}

	return 0;
}


NodoTablero* Tablero::nodoObjetivo(string alfanumerico) {
	NodoTablero* auxiliar = this->cabecera->siguiente;
	NodoActivo* retorno = 0;

	while (auxiliar != 0) {

		NodoTablero* auxiliar1 = auxiliar->abajo;
		while (auxiliar1 != 0) {

			if (auxiliar1->atras != 0) {
				NodoTablero* auxiliar2 = auxiliar1;

				while (auxiliar2 != 0) {
					if (auxiliar2->empleado->getRentas()->buscar(alfanumerico) == true) {
						return auxiliar2;
					}
					auxiliar2 = auxiliar2->atras;
				}
			}
			else {
				if (auxiliar1->empleado->getRentas()->buscar(alfanumerico) == true) {
					return auxiliar1;
				}
			}

			auxiliar1 = auxiliar1->abajo;
		}

		auxiliar = auxiliar->siguiente;
	}

	return 0;
}

int generador_id;

string Tablero::Generarid() {

	string id = "";
	char strrnd[15];
	srand(time(NULL));

	for (int i = 0; i < 15; i++) {

		generador_id = 48 + rand() % (123 - 48);
	

		if ((generador_id >= 48 && generador_id <= 57) || (generador_id >= 65 && generador_id <= 90) || (generador_id >= 97 && generador_id <= 122))
		{

			strrnd[i] = generador_id;
			id = id + strrnd[i];

		}
		else {
			i--;
		}

		//cout << strrnd[i];

	}
	//cout << id << endl;

	return id;
}