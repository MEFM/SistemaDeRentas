#pragma once
#include <iostream>
#include<string>
#include <algorithm>
//ActivoRenta

using namespace std;


class Nodo {
public:



	string nombreActivo;
	string descripcioN;
	int dato; //Codigo
	int FE;
	Nodo* izquierdo;
	Nodo* derecho;
	Nodo* padre;
	bool disponibilidad;


	Nodo(string nombreActivo, const int codigo, string descripcion, Nodo* pad = NULL, Nodo* izq = NULL, Nodo* der = NULL) {
		this->dato = codigo;
		this->FE = 0;
		this->nombreActivo = nombreActivo;
		this->descripcioN = descripcion;
		this->izquierdo = izq;
		this->derecho = der;
		this->padre = pad;

	}

	Nodo(string nombreActivo, const int codigo, string descripcion, bool disponibilidad, Nodo* pad = NULL, Nodo* izq = NULL, Nodo* der = NULL) {
		this->dato = codigo;
		this->FE = 0;
		this->nombreActivo = nombreActivo;
		this->descripcioN = descripcion;
		this->izquierdo = izq;
		this->derecho = der;
		this->padre = pad;
		this->disponibilidad = disponibilidad;

	}


	friend class AVL;
};

class AVL {
private:
	enum { IZQUIERDO, DERECHO };
	// Punteros de la lista, para cabeza y nodo actual:

	Nodo* raiz;
	Nodo* actual;
	int contador;
	int altura;

public:
	// Constructor y destructor básicos:
	AVL() {
		this->raiz = 0;
		this->actual = 0;
	}
	//~AVL() { Podar(raiz); }
	// Insertar en árbol ordenado:
	void insertar(string nombreActivo, const int dat, string descripcion, bool disponibilidad);
	void eliminar(const int dat);
	// Función de búsqueda:
	bool buscar(const int dat);

	
	// Comprobar si es un nodo hoja:
	bool EsHoja(Nodo* r) { return !r->derecho && !r->izquierdo; }
	// Contar número de nodos:
	const int NumeroNodos();
	const int AlturaArbol();
	// Calcular altura de un dato:
	int Altura(const int dat);
	// Devolver referencia al dato del nodo actual:
	int& ValorActual() { return actual->dato; }
	// Moverse al nodo raiz:
	void Raiz() { actual = raiz; }
	// Aplicar una función a cada elemento del árbol:
	void InOrden(void (*func)(int&, int), Nodo* nodo = NULL, bool r = true);
	void PreOrden(void (*func)(int&, int), Nodo* nodo = NULL, bool r = true);
	void PostOrden(void (*func)(int&, int), Nodo* nodo = NULL, bool r = true);

	void rentador(void (*func)(int&, int), Nodo* nodo = NULL, bool r = true);
	void recor();
	void reservador(void (*func)(int&, int), Nodo* nodo = NULL, bool r = true);
	void libres(void (*func)(int&, int), Nodo* nodo = NULL, bool r = true);
private:

	void recor(Nodo* nodo);
	void equilibrar(Nodo* nodo, int, bool);
	void rotacionSimpleIzquierda(Nodo* nodo);
	void rotacionSimpleDerecha(Nodo* nodo);
	void rotacionDobleIzquierda(Nodo* nodo);
	void rotacionDobleDerecha(Nodo* nodo);

	//Esta funcion es solo para eliminar todos los nodos a partir de uno
		//No se si utilizarla pero weno a ver que pedo

	void Podar(Nodo*&);
	void auxContador(Nodo*);
	void auxAltura(Nodo*, int);
};


