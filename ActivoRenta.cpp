#include "ActivoRenta.h"



void AVL::Podar(Nodo*& nodo)
{
	// Algoritmo recursivo, recorrido en postorden
	if (nodo) {
		Podar(nodo->izquierdo); // Podar izquierdo
		Podar(nodo->derecho);   // Podar derecho
		delete nodo;            // Eliminar nodo
		nodo = 0;
	}
}

void AVL::insertar(string nombreActivo, const int dat, string descripcion, bool disponibilidad)
{
	Nodo* padre = 0;

	cout << "Insertar: " << dat << endl;
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
		raiz = new Nodo(nombreActivo, dat, descripcion);
	}

	else if (dat < padre->dato) {
		padre->izquierdo = new Nodo(nombreActivo, dat, descripcion, disponibilidad, padre);
		equilibrar(padre, IZQUIERDO, true);
	}

	else if (dat > padre->dato) {
		padre->derecho = new Nodo(nombreActivo, dat, descripcion, disponibilidad, padre);
		equilibrar(padre, DERECHO, true);
	}
}


void AVL::equilibrar(Nodo* nodo, int rama, bool nuevo)
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

void AVL::rotacionDobleDerecha(Nodo* nodo)
{
	cout << "RDD" << endl;
	Nodo* Padre = nodo->padre;
	Nodo* P = nodo;
	Nodo* Q = P->izquierdo;
	Nodo* R = Q->derecho;
	Nodo* B = R->izquierdo;
	Nodo* C = R->derecho;

	if (Padre)
		if (Padre->derecho == nodo) Padre->derecho = R;
		else Padre->izquierdo = R;
	else raiz = R;

	// Reconstruir árbol:
	Q->derecho = B;
	P->izquierdo = C;
	R->izquierdo = Q;
	R->derecho = P;

	// Reasignar padres:
	R->padre = Padre;
	P->padre = Q->padre = R;
	if (B) B->padre = Q;
	if (C) C->padre = P;

	// Ajustar valores de FE:
	switch (R->FE) {
	case -1: Q->FE = 0; P->FE = 1; break;
	case 0:  Q->FE = 0; P->FE = 0; break;
	case 1:  Q->FE = -1; P->FE = 0; break;
	}
	R->FE = 0;
}


void AVL::rotacionDobleIzquierda(Nodo* nodo)
{
	cout << "RDI" << endl;
	Nodo* Padre = nodo->padre;
	Nodo* P = nodo;
	Nodo* Q = P->derecho;
	Nodo* R = Q->izquierdo;
	Nodo* B = R->izquierdo;
	Nodo* C = R->derecho;

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


void AVL::rotacionSimpleDerecha(Nodo* nodo)
{
	cout << "RSD" << endl;
	Nodo* Padre = nodo->padre;
	Nodo* P = nodo;
	Nodo* Q = P->izquierdo;
	Nodo* B = Q->derecho;

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


void AVL::rotacionSimpleIzquierda(Nodo* nodo)
{
	cout << "RSI" << endl;
	Nodo* Padre = nodo->padre;
	Nodo* P = nodo;
	Nodo* Q = P->derecho;
	Nodo* B = Q->izquierdo;

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

void AVL::eliminar(const int dat)
{
	Nodo* padre = 0;
	Nodo* nodo;
	int aux;

	actual = raiz;
	while (!(actual == 0)) {
		if (dat == actual->dato) { // Si el valor está en el nodo actual
			if (EsHoja(actual)) { // Y si además es un nodo hoja: lo borramos
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


void AVL::InOrden(void (*func)(int&, int), Nodo* nodo, bool r)
{
	if (r) nodo = raiz;
	if (nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
	func(nodo->dato, nodo->FE);
	if (nodo->derecho) InOrden(func, nodo->derecho, false);
}


void AVL::PreOrden(void (*func)(int&, int), Nodo* nodo, bool r)
{
	if (r) nodo = raiz;
	cout << nodo->nombreActivo << endl;
	func(nodo->dato, nodo->FE);
	if (nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);
	if (nodo->derecho) PreOrden(func, nodo->derecho, false);
}


void AVL::PostOrden(void (*func)(int&, int), Nodo* nodo, bool r)
{
	if (r) nodo = raiz;
	if (nodo->izquierdo) PostOrden(func, nodo->izquierdo, false);
	if (nodo->derecho) PostOrden(func, nodo->derecho, false);
	func(nodo->dato, nodo->FE);
}


void AVL::recor() {
	if (this->raiz != 0) {
		this->recor(raiz);
	}
}

void AVL::recor(Nodo* nodo) {
	if (nodo != 0) {
		cout << nodo->nombreActivo << endl;
		recor(nodo->izquierdo);
		recor(nodo->derecho);
	}
}

bool AVL::buscar(const int dat)
{
	actual = raiz;


	while (!(actual == 0)) {
		if (dat == actual->dato) return true;
		else if (dat > actual->dato) actual = actual->derecho;
		else if (dat < actual->dato) actual = actual->izquierdo;
	}
	return false; // No está en árbol
}

// Calcular la altura del nodo que contiene el dato dat
int AVL::Altura(const int dat)
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

// Contar el número de nodos
const int AVL::NumeroNodos()
{
	contador = 0;

	auxContador(raiz); // FUnción auxiliar
	return contador;
}

// Función auxiliar para contar nodos. Función recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
void AVL::auxContador(Nodo* nodo)
{
	contador++;  // Otro nodo
	// Continuar recorrido
	if (nodo->izquierdo) auxContador(nodo->izquierdo);
	if (nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del árbol, que es la altura del nodo de mayor altura.
const int AVL::AlturaArbol()
{
	altura = 0;

	auxAltura(raiz, 0); // Función auxiliar
	return altura;
}




void AVL::auxAltura(Nodo* nodo, int a)
{
	// Recorrido postorden
	if (nodo->izquierdo) auxAltura(nodo->izquierdo, a + 1);
	if (nodo->derecho)   auxAltura(nodo->derecho, a + 1);
	// Proceso, si es un nodo hoja, y su altura es mayor que la actual del
	// árbol, actualizamos la altura actual del árbol
	if (EsHoja(nodo) && a > altura) altura = a;
}


