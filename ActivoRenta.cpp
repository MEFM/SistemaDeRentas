#include "ActivoRenta.h"




void ActivosRenta::insertar(string nombreActivo, const int dat, string descripcion, bool disponibilidad)
{
	NodoActivo* padre = 0;


	actual = raiz;

	while (!(actual == 0) && dat != actual->dato) {
		padre = actual;
		if (dat > actual->dato) actual = actual->derecho;
		else if (dat < actual->dato) actual = actual->izquierdo;
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


void ActivosRenta::equilibrar(NodoActivo* nodo, int rama, bool nuevo)
{
	bool salir = false;

	// Recorrer camino inverso actualizando valores de FE:
	while (nodo && !salir) {
		if (nuevo)
			if (rama == IZQUIERDO) nodo->FE--;
			else  nodo->FE++;
		else
			if (rama == IZQUIERDO) nodo->FE++;
			else                  nodo->FE--;
		if (nodo->FE == 0) salir = true; // La altura de las rama que

		else if (nodo->FE == -2) { // Rotar a derechas y salir:
			if (nodo->izquierdo->FE == 1) rotacionDobleDerecha(nodo); // Rotación doble
			else rotacionSimpleDerecha(nodo);                         // Rotación simple
			salir = true;
		}
		else if (nodo->FE == 2) {  // Rotar a izquierdas y salir:
			if (nodo->derecho->FE == -1) rotacionDobleIzquierda(nodo); // Rotación doble
			else rotacionSimpleIzquierda(nodo);                        // Rotación simple
			salir = true;
		}
		if (nodo->padre)
			if (nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
		nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
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

	if (Padre)
		if (Padre->derecho == nodo) Padre->derecho = R;
		else Padre->izquierdo = R;
	else raiz = R;

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


	switch (R->FE) {
	case -1:
		Q->FE = 0; P->FE = 1;
		break;
	case 0:
		Q->FE = 0; P->FE = 0;
		break;
	case 1:
		Q->FE = -1; P->FE = 0;
		break;
	}
	R->FE = 0;
}

void ActivosRenta::rotacionDobleIzquierda(NodoActivo* nodo)
{

	NodoActivo* Padre = nodo->padre;
	NodoActivo* P = nodo;
	NodoActivo* Q = P->derecho;
	NodoActivo* R = Q->izquierdo;
	NodoActivo* B = R->izquierdo;
	NodoActivo* C = R->derecho;

	if (Padre)
		if (Padre->derecho == nodo) Padre->derecho = R;
		else Padre->izquierdo = R;
	else raiz = R;

	// Reconstruir árbol:
	P->derecho = B;
	Q->izquierdo = C;
	R->izquierdo = P;
	R->derecho = Q;

	// Reasignar padres:
	R->padre = Padre;
	P->padre = Q->padre = R;
	if (B) B->padre = P;
	if (C) C->padre = Q;

	// Ajustar valores de FE:
	switch (R->FE) {
	case -1: P->FE = 0; Q->FE = 1; break;
	case 0:  P->FE = 0; Q->FE = 0; break;
	case 1:  P->FE = -1; Q->FE = 0; break;
	}
	R->FE = 0;
}

void ActivosRenta::rotacionSimpleDerecha(NodoActivo* nodo)
{

	NodoActivo* Padre = nodo->padre;
	NodoActivo* P = nodo;
	NodoActivo* Q = P->izquierdo;
	NodoActivo* B = Q->derecho;

	if (Padre)
		if (Padre->derecho == P) Padre->derecho = Q;
		else Padre->izquierdo = Q;
	else raiz = Q;

	// Reconstruir árbol:
	P->izquierdo = B;
	Q->derecho = P;

	// Reasignar padres:
	P->padre = Q;
	if (B) B->padre = P;
	Q->padre = Padre;

	// Ajustar valores de FE:
	P->FE = 0;
	Q->FE = 0;
}

void ActivosRenta::rotacionSimpleIzquierda(NodoActivo* nodo)
{

	NodoActivo* Padre = nodo->padre;
	NodoActivo* P = nodo;
	NodoActivo* Q = P->derecho;
	NodoActivo* B = Q->izquierdo;

	if (Padre)
		if (Padre->derecho == P) Padre->derecho = Q;
		else Padre->izquierdo = Q;
	else raiz = Q;

	// Reconstruir árbol:
	P->derecho = B;
	Q->izquierdo = P;

	// Reasignar padres:
	P->padre = Q;
	if (B) B->padre = P;
	Q->padre = Padre;

	// Ajustar valores de FE:
	P->FE = 0;
	Q->FE = 0;
}

void ActivosRenta::eliminar(const int dat)
{
	NodoActivo* padre = 0;
	NodoActivo* nodo;
	int aux;

	actual = raiz;
	while (!(actual == 0)) {
		if (dat == actual->dato) {
			if (EsHoja(actual)) {
				if (padre) {
					if (padre->derecho == actual) {
						padre->derecho = 0;
					}
					else if (padre->izquierdo == actual) {
						padre->izquierdo = 0;
					}
				}
				delete actual;
				actual = 0;

				if ((padre->derecho == actual && padre->FE == 1) || (padre->izquierdo == actual && padre->FE == -1)) {
					padre->FE = 0;
					actual = padre;
					padre = actual->padre;
				}
				if (padre)
					if (padre->derecho == actual) equilibrar(padre, DERECHO, false);
					else                         equilibrar(padre, IZQUIERDO, false);
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
			if (dat > actual->dato) {
				actual = actual->derecho;
			}
			else if (dat < actual->dato) {
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

int ActivosRenta::Altura(const int dat)
{
	int altura = 0;
	actual = raiz;

	// Todavía puede aparecer, ya que quedan nodos por mirar
	while (!(actual == 0)) {
		if (dat == actual->dato) return altura; // dato encontrado
		else {
			altura++; // Incrementamos la altura, seguimos buscando
			if (dat > actual->dato) actual = actual->derecho;
			else if (dat < actual->dato) actual = actual->izquierdo;
		}
	}
	return -1; // No está en árbol
}


const int ActivosRenta::NumeroNodos()
{
	contador = 0;

	auxContador(raiz);
	return contador;
}

void ActivosRenta::auxContador(NodoActivo* nodo)
{
	contador++;  // Otro nodo
	// Continuar recorrido
	if (nodo->izquierdo) auxContador(nodo->izquierdo);
	if (nodo->derecho)   auxContador(nodo->derecho);
}


const int ActivosRenta::AlturaArbol()
{
	altura = 0;

	auxAltura(raiz, 0); // Función auxiliar
	return altura;
}

void ActivosRenta::inOrden() {
	if (raiz != 0)
		inOrden(this->raiz);
	else
		cout << "No hay nada en el arbol brou" << endl;
}

void ActivosRenta::inOrden(NodoActivo* nodo) {
	if (nodo != 0) {
		inOrden(nodo->izquierdo);
		cout << nodo->nombreActivo << endl;
		inOrden(nodo->derecho);
	}
}

void ActivosRenta::preOrden() {
	if (raiz != 0)
		preOrden(this->raiz);
	else
		cout << "No hay arbol bro" << endl;
}

void ActivosRenta::preOrden(NodoActivo* nodo) {
	if (nodo != 0) {
		if (nodo->disponibilidad == true) {
			cout << "Id: " << nodo->dato << " Nombre activo: " << nodo->nombreActivo << " Disponibilidad: Disponible" << endl;
		}
		else {
			cout << "Id: " << nodo->dato << " Nombre activo: " << nodo->nombreActivo << " Disponibilidad: No Disponible" << endl;
		}

		preOrden(nodo->izquierdo);
		preOrden(nodo->derecho);
	}
}

void ActivosRenta::postOrden() {
	if (raiz != 0)
		postOrden(this->raiz);
	else
		cout << "No hay arbol para recorrer" << endl;
}

void ActivosRenta::postOrden(NodoActivo* nodo) {
	if (nodo != 0) {
		postOrden(nodo->izquierdo);
		postOrden(nodo->derecho);
		cout << nodo->nombreActivo << endl;
	}
}

void ActivosRenta::auxAltura(NodoActivo* nodo, int a)
{

	if (nodo->izquierdo) auxAltura(nodo->izquierdo, a + 1);
	if (nodo->derecho)   auxAltura(nodo->derecho, a + 1);

	if (EsHoja(nodo) && a > altura) altura = a;
}

void ActivosRenta::modificar(int aReemplazar, string nombreActivo, const int dat, string descripcion, bool disponibilidad) {
	if (this->raiz != 0) {
		this->eliminar(aReemplazar);
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
}


void ActivosRenta::reservados() {
	if (this->raiz != 0)
		reservados(this->raiz);
	else
		cout << "No hay activos" << endl;
}

void ActivosRenta::reservados(NodoActivo* nodo) {
	if (nodo != 0) {
		if (nodo->disponibilidad == false) {
			cout << "Id: " << nodo->dato << " Nombre activo: " << nodo->nombreActivo << " Disponibilidad: Alquilado" << endl;
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
		cout << "No hay activos en este usuario." << endl;
	}
}

void ActivosRenta::libres(NodoActivo* nodo) {
	if (nodo != 0) {
		if (nodo->disponibilidad == true) {
			cout << "Id: " << nodo->dato << " Nombre activo: " << nodo->nombreActivo << " Disponibilidad: Disponible" << endl;
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


		if (nodo->izquierdo != 0) {
			//WriteFile << nodo->nombreActivo << "->" << nodo->izquierdo->nombreActivo << endl;
			controla += nodo->nombreActivo + "->" + nodo->izquierdo->nombreActivo + "\n";
		}
		else {
			this->graficar(nodo->izquierdo);
			this->graficar(nodo->derecho);
		}

		if (nodo->derecho != 0) {
			controla += nodo->nombreActivo + "->" + nodo->derecho->nombreActivo + "\n";

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
		//controla = "";
	}
}

string ActivosRenta::pasarDocumento(string nombre, int numCluster) {
	if (this->raiz == 0) {
		cout << "No hay activos." << endl;
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
		archivo += "                                  -> " + nodo->nombreActivo + "[ltail=cluster" + to_string(numCluster);
		archivo += " lhead=cluster" + to_string(numCluster + 1);
		archivo += "]\n";
		archivo += "                                  ;\n";
		//cout << archivo << endl;
	}
	return archivo;

}

void ActivosRenta::arbolIndividual(NodoActivo* nodo) {
	if (nodo != 0) {


		if (nodo->izquierdo != 0) {
			activado += "                                  ";
			activado += nodo->nombreActivo + "->" + nodo->izquierdo->nombreActivo + "\n";
			cout << nodo->nombreActivo << endl;
		}
		if (nodo->derecho != 0) {
			activado += "                                  ";
			activado += nodo->nombreActivo + "->" + nodo->derecho->nombreActivo + "\n";
			cout << nodo->nombreActivo << endl;
		}

		this->arbolIndividual(nodo->izquierdo);
		this->arbolIndividual(nodo->derecho);

	}

}
