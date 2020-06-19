#include "ActivoRenta.h"





void ActivosRenta::insertar(string nombreActivo, const int dat, string descripcion, bool disponibilidad)
{
	NodoActivo* padre = 0;


	actual = raiz;

	while (!(actual == 0) && dat != actual->dato) {
		padre = actual;
		if (dat > actual->dato) {
			actual = actual->derecho;
		}
		else if (dat < actual->dato) {
			actual = actual->izquierdo;
		}
	}


	if (!(actual == 0)) {
		return;
	}
	if ((padre == 0)) {
		raiz = new NodoActivo(nombreActivo, dat, descripcion, disponibilidad);
	}

	else if (dat < padre->dato) {
		padre->izquierdo = new NodoActivo(nombreActivo, dat, descripcion, disponibilidad, padre);
		equilibrar(padre, IZQUIERDO, true);
	}

	else if (dat > padre->dato) {
		padre->derecho = new NodoActivo(nombreActivo, dat, descripcion, disponibilidad, padre);
		equilibrar(padre, DERECHO, true);
	}
}


void ActivosRenta::insertar(string nombreActivo, string dat, string descripcion, bool disponibilidad)
{
	NodoActivo* padre = 0;


	actual = raiz;

	while (!(actual == 0) && dat != actual->codAlfanum) {
		padre = actual;
		if (dat > actual->codAlfanum) {
			actual = actual->derecho;
		}
		else if (dat < actual->codAlfanum) {
			actual = actual->izquierdo;
		}
	}


	if (!(actual == 0)) {
		return;
	}
	if ((padre == 0)) {
		raiz = new NodoActivo(nombreActivo, dat, descripcion, disponibilidad);
	}

	else if (dat < padre->codAlfanum) {
		padre->izquierdo = new NodoActivo(nombreActivo, dat, descripcion, disponibilidad, padre);
		equilibrar(padre, IZQUIERDO, true);
	}

	else if (dat > padre->codAlfanum) {
		padre->derecho = new NodoActivo(nombreActivo, dat, descripcion, disponibilidad, padre);
		equilibrar(padre, DERECHO, true);
	}
}


void ActivosRenta::equilibrar(NodoActivo* nodo, int rama, bool nuevo)
{
	bool salir = false;


	while (nodo && !salir) {
		if (nuevo)
			if (rama == IZQUIERDO) {
				nodo->factorEquilibrio--;
			}
			else {
				nodo->factorEquilibrio++;
			}
		else {
			if (rama == IZQUIERDO) {
				nodo->factorEquilibrio++;
			}
			else {
				nodo->factorEquilibrio--;
			}
		}
		if (nodo->factorEquilibrio == 0) {
			salir = true;
		}
		else if (nodo->factorEquilibrio == -2) {
			if (nodo->izquierdo->factorEquilibrio == 1) {
				rotacionDobleDerecha(nodo);
			}
			else rotacionSimpleDerecha(nodo);
			salir = true;
		}
		else if (nodo->factorEquilibrio == 2) {
			if (nodo->derecho->factorEquilibrio == -1) {
				rotacionDobleIzquierda(nodo);
			}
			else {
				rotacionSimpleIzquierda(nodo);
			}
			salir = true;
		}
		if (nodo->padre)
			if (nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
		nodo = nodo->padre;
	}
}

void ActivosRenta::rotacionDobleDerecha(NodoActivo* nodo)
{

	NodoActivo* Padre = nodo->padre;
	NodoActivo* P = nodo;
	NodoActivo* Q = P->izquierdo;
	NodoActivo* R = Q->derecho;
	NodoActivo* B = R->izquierdo;
	NodoActivo* C = R->derecho;

	if (Padre) {
		if (Padre->derecho == nodo) {
			Padre->derecho = R;
		}
		else {
			Padre->izquierdo = R;
		}
	}
	else {
		raiz = R;
	}
	Q->derecho = B;
	P->izquierdo = C;
	R->izquierdo = Q;
	R->derecho = P;


	R->padre = Padre;
	P->padre = Q->padre = R;
	if (B) {
		B->padre = Q;
	}
	if (C) {
		C->padre = P;
	}


	switch (R->factorEquilibrio) {
	case -1:
		Q->factorEquilibrio = 0;
		P->factorEquilibrio = 1;
		break;
	case 0:
		Q->factorEquilibrio = 0;
		P->factorEquilibrio = 0;
		break;
	case 1:
		Q->factorEquilibrio = -1;
		P->factorEquilibrio = 0;
		break;
	}
	R->factorEquilibrio = 0;
}

void ActivosRenta::rotacionDobleIzquierda(NodoActivo* nodo)
{



	NodoActivo* Padre = nodo->padre;
	NodoActivo* P = nodo;
	NodoActivo* Q = P->derecho;
	NodoActivo* R = Q->izquierdo;
	NodoActivo* B = R->izquierdo;
	NodoActivo* C = R->derecho;

	if (Padre) {
		if (Padre->derecho == nodo) {
			Padre->derecho = R;
		}
		else {
			Padre->izquierdo = R;
		}
	}
	else {
		raiz = R;
	}

	P->derecho = B;
	Q->izquierdo = C;
	R->izquierdo = P;
	R->derecho = Q;


	R->padre = Padre;
	P->padre = Q->padre = R;
	if (B) {
		B->padre = P;
	}
	if (C) {
		C->padre = Q;
	}

	switch (R->factorEquilibrio) {
	case -1:
		P->factorEquilibrio = 0;
		Q->factorEquilibrio = 1;
		break;
	case 0:
		P->factorEquilibrio = 0;
		Q->factorEquilibrio = 0;
		break;
	case 1:
		P->factorEquilibrio = -1;
		Q->factorEquilibrio = 0;
		break;
	}
	R->factorEquilibrio = 0;
}

void ActivosRenta::rotacionSimpleDerecha(NodoActivo* nodo)
{

	NodoActivo* Padre = nodo->padre;
	NodoActivo* P = nodo;
	NodoActivo* Q = P->izquierdo;
	NodoActivo* B = Q->derecho;

	if (Padre) {
		if (Padre->derecho == P) {
			Padre->derecho = Q;
		}
		else {
			Padre->izquierdo = Q;
		}
	}
	else {
		raiz = Q;
	}

	P->izquierdo = B;
	Q->derecho = P;


	P->padre = Q;
	if (B) B->padre = P;
	Q->padre = Padre;


	P->factorEquilibrio = 0;
	Q->factorEquilibrio = 0;
}

void ActivosRenta::rotacionSimpleIzquierda(NodoActivo* nodo)
{


	NodoActivo* Padre = nodo->padre;
	NodoActivo* p;

	p = nodo;
	NodoActivo* Q = p->derecho;
	NodoActivo* B = Q->izquierdo;

	if (Padre) {
		if (Padre->derecho == p) {
			Padre->derecho = Q;
		}
		else {
			Padre->izquierdo = Q;
		}
	}
	else {
		raiz = Q;
	}

	p->derecho = B;
	Q->izquierdo = p;


	p->padre = Q;
	if (B) B->padre = p;
	Q->padre = Padre;


	p->factorEquilibrio = 0;
	Q->factorEquilibrio = 0;
}

void ActivosRenta::eliminar(string dat)
{
	NodoActivo* padre = 0;
	NodoActivo* nodo;
	int aux;

	actual = raiz;
	while (!(actual == 0)) {
		if (dat == actual->codAlfanum) {
			if (EsHoja(actual)) {
				if (padre) {
					if (padre->derecho == actual) {
						padre->derecho = 0;
					}
					//Estas son verificaciones para eliminar
					else if (padre->izquierdo == actual) {
						padre->izquierdo = 0;
					}
				}
				//Si elimina el actaul a irse de una vez

				delete actual;
				actual = 0;

				if ((padre->derecho == actual && padre->factorEquilibrio == 1) || (padre->izquierdo == actual && padre->factorEquilibrio == -1)) {
					padre->factorEquilibrio = 0;
					actual = padre;
					padre = actual->padre;
				}
				if (padre)
					if (padre->derecho == actual) {
						equilibrar(padre, DERECHO, false);
					}
					else {
						equilibrar(padre, IZQUIERDO, false);
					}
				return;
			}
			else {
				padre = actual;

				if (actual->derecho) {
					nodo = actual->derecho;
					while (nodo->izquierdo) {
						padre = nodo;
						nodo = nodo->izquierdo;
					}
				}

				else {
					nodo = actual->izquierdo;
					while (nodo->derecho) {
						padre = nodo;
						nodo = nodo->derecho;
					}
				}

				aux = actual->dato;
				actual->dato = nodo->dato;
				nodo->dato = aux;
				actual = nodo;
			}
		}
		else {
			padre = actual;
			if (dat > actual->codAlfanum) {
				actual = actual->derecho;
			}
			else if (dat < actual->codAlfanum) {
				actual = actual->izquierdo;
			}
		}
	}
}

void ActivosRenta::recor() {
	if (this->raiz != 0) {
		this->recor(raiz);
	}
}

void ActivosRenta::recor(NodoActivo* nodo) {
	if (nodo != 0) {
		cout << nodo->nombreActivo << endl;
		recor(nodo->izquierdo);
		recor(nodo->derecho);
	}
}

bool ActivosRenta::buscar(const int dat)
{
	actual = raiz;


	while (!(actual == 0)) {
		if (dat == actual->dato) return true;
		else if (dat > actual->dato) actual = actual->derecho;
		else if (dat < actual->dato) actual = actual->izquierdo;
	}
	return false; // No está en árbol
}

bool ActivosRenta::buscar(string xodigo) {
	actual = raiz;


	while (!(actual == 0)) {
		if (xodigo == actual->codAlfanum) {
			return true;
		}
		else if (xodigo > actual->codAlfanum) {
			actual = actual->derecho;
		}
		else if (xodigo < actual->codAlfanum) {
			actual = actual->izquierdo;
		}
	}
	return false; // No está en árbol

}

void ActivosRenta::modificar(int aReemplazar, string nombreActivo, const int dat, string descripcion, bool disponibilidad) {
	if (this->raiz != 0) {
//		this->eliminar(aReemplazar);
		this->insertar(nombreActivo, dat, descripcion, disponibilidad);
	}
	else {
		cout << "No hay nada en el arbol" << endl;
	}
}

NodoActivo* ActivosRenta::buscarActivo(int id) {
	if (this->raiz != 0) {
		return buscarActivo(this->raiz, id);
	}
	else {
		cout << "No hay actios para este usuario" << endl;
		return 0;
	}
}

NodoActivo* ActivosRenta::buscarActivo(NodoActivo* nodo, int id) {
	if (nodo != 0) {
		if (id < nodo->dato) {
			buscarActivo(nodo->izquierdo, id);
		}
		else if (id > nodo->dato) {
			buscarActivo(nodo->derecho, id);
		}
		else {
			return nodo;
		}
	}
	else {

		return 0;
	}
}

NodoActivo* ActivosRenta::buscarActivo(string codigoActivo) {
	if (this->raiz != 0) {
		NodoActivo* aux = this->buscarActivo(this->raiz, codigoActivo);
		return aux;
	}
	else {
		cout << "No existen activos en este usuario" << endl;
		return 0;
	}
}

NodoActivo* ActivosRenta::buscarActivo(NodoActivo* nodo, string id) {
	actual = raiz;


	while (!(actual == 0)) {
		if (id == actual->codAlfanum) {
			return actual;
		}
		else if (id > actual->codAlfanum) {
			actual = actual->derecho;
		}
		else if (id < actual->codAlfanum) {
			actual = actual->izquierdo;
		}
	}
	return 0;
}

void ActivosRenta::reservados() {
	if (this->raiz != 0)
		reservados(this->raiz);
	else
		cout << "No hay activos" << endl;
}

bool ActivosRenta::EsHoja(NodoActivo* r) {
	return !r->derecho && !r->izquierdo;
}


void ActivosRenta::reservados(NodoActivo* nodo) {
	if (nodo != 0) {
		if (nodo->disponibilidad == false) {
			cout << "Id: " << nodo->codAlfanum << " Nombre activo: " << nodo->nombreActivo << " Disponibilidad: Alquilado" << endl;
		}
		reservados(nodo->izquierdo);
		reservados(nodo->derecho);
	}
}

void ActivosRenta::libres() {
	if (this->raiz != 0) {
		this->libres(this->raiz);
	}
	else {
		cout << "Sin activos disponibles." << endl;
	}
}

void ActivosRenta::libres(NodoActivo* nodo) {
	if (nodo != 0) {
		if (nodo->disponibilidad == true) {
			cout << "Id: " << nodo->codAlfanum << " Nombre activo: " << nodo->nombreActivo << "; Disponibilidad: Disponible" << endl;
		}
		libres(nodo->izquierdo);
		libres(nodo->derecho);
	}
}

void ActivosRenta::graficar() {
	if (this->raiz != 0) {
		controla = "";
		graficar(this->raiz);

		system("dot -Tpng Activos.dot -o Activos.png");
		system("Activos.png");
		controla = "";
	}
}

void ActivosRenta::graficar(NodoActivo* nodo) {
	if (nodo == 0) {
		return;
	}
	else {
		ofstream WriteFile("Activos.dot");
		WriteFile << "digraph reporte{" << endl;
		WriteFile << "node [shape = record, style=filled, fillcolor=seashell2];" << endl;

		controla += "				D" + nodo->codAlfanum + "[label = \"" + nodo->codAlfanum + " Nombre Activo: " + nodo->nombreActivo + "\"]\n";

		if (nodo->izquierdo != 0) {

			controla += "				D" + nodo->izquierdo->codAlfanum + "[label = \"" + nodo->codAlfanum + " Nombre Activo: " + nodo->nombreActivo + "\"]\n";
			controla += "				D" + nodo->codAlfanum + "-> D" + nodo->izquierdo->codAlfanum + "\n";
			//			controla += nodo->codAlfanum + "->" + nodo->izquierdo->codAlfanum + "\n";
		}
		else {
			this->graficar(nodo->izquierdo);
			this->graficar(nodo->derecho);
		}

		if (nodo->derecho != 0) {
			//WriteFile << "D" << nodo->codAlfanum << "[label = \"" << nodo->codAlfanum << "\nNombre: " << nodo->nombreActivo << "\"]" << endl;
			controla += "				D" + nodo->derecho->codAlfanum + "[label = \"" + nodo->codAlfanum + " Nombre Activo: " + nodo->nombreActivo + "\"]\n";
			controla += "				D" + nodo->codAlfanum + "-> D" + nodo->derecho->codAlfanum + "\n";
			//	controla += nodo + "->" + nodo->derecho->codAlfanum + "\n";

		}
		else {
			this->graficar(nodo->izquierdo);
			this->graficar(nodo->derecho);
		}
		this->graficar(nodo->izquierdo);
		this->graficar(nodo->derecho);
		//	controla += nodo->nombreActivo + "->" + nodo->izquierdo->nombreActivo + "\n";
			//controla += nodo->nombreActivo + "->" + nodo->derecho->nombreActivo + "\n";

		WriteFile << controla << endl;
		WriteFile << "}" << endl;
		WriteFile.close();

	}
}

string ActivosRenta::pasarDocumento(string nombre, int numCluster) {
	if (this->raiz == 0) {
		cout << "No hay activos. " << nombre << endl;
		return "";
	}
	else {
		return	pasarDocumento(nombre, this->raiz, numCluster, controla);
	}
}

string activado = "";

string ActivosRenta::pasarDocumento(string nombre, NodoActivo* nodo, int numCluster, string archivo) {
	if (nodo != 0) {
		archivo += "                                  subgraph cluster" + to_string(numCluster);
		archivo += "                                  {\n";
		archivo += "                                  label = \"Usuario\";\n";
		archivo += "                                  Titulo" + to_string(numCluster);
		archivo += "                                  [label=\"" + nombre + "\"]\n";
		archivo += "                                  }\n";

		archivo += "                                  subgraph cluster" + to_string(numCluster + 1);
		archivo += "                                  {\n";
		archivo += "                                  label =\"Activos\"";
		activado = "                                  ";
		arbolIndividual(this->raiz);
		archivo += "                                  " + activado;
		archivo += "                                  }\n";

		archivo += "\n";
		archivo += "                                  Titulo" + to_string(numCluster);
		archivo += "                                  -> D" + nodo->codAlfanum + "[ltail=cluster" + to_string(numCluster);
		archivo += " lhead=cluster" + to_string(numCluster + 1);
		archivo += "]\n";
		archivo += "                                  ;\n";
		//cout << archivo << endl;
	}
	return archivo;

}

void ActivosRenta::arbolIndividual(NodoActivo* nodo) {
	if (nodo != 0) {


		activado += "								D" + nodo->codAlfanum + "[label = \"" + nodo->codAlfanum + " Nombre Activo: " + nodo->nombreActivo + "\"]\n";
		if (nodo->izquierdo != 0) {
			activado += "								D" + nodo->izquierdo->codAlfanum + "[label = \"" + nodo->codAlfanum + " Nombre Activo: " + nodo->nombreActivo + "\"]\n";
			activado += "								D" + nodo->codAlfanum + "-> D" + nodo->izquierdo->codAlfanum + "\n";
			cout << nodo->nombreActivo << endl;
		}
		else {
			this->arbolIndividual(nodo->izquierdo);
			this->arbolIndividual(nodo->derecho);
		}
		if (nodo->derecho != 0) {
			activado += "								D" + nodo->derecho->codAlfanum + "[label = \"" + nodo->codAlfanum + " Nombre Activo: " + nodo->nombreActivo + "\"]\n";
			activado += "								D" + nodo->codAlfanum + "-> D" + nodo->derecho->codAlfanum + "\n";

		}
		else {
			this->arbolIndividual(nodo->izquierdo);
			this->arbolIndividual(nodo->derecho);
		}

		this->arbolIndividual(nodo->izquierdo);
		this->arbolIndividual(nodo->derecho);

	}

}
