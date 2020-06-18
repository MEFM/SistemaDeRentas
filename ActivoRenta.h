#pragma once
#include <iostream>
#include<string>
#include <algorithm>
#include <fstream>
#include <cstdlib>


#include <time.h>


//ActivoRenta

using namespace std;


class NodoActivo {
public:



	string nombreActivo;
	string descripcioN;
	int dato; //Codigo
	int FE;
	NodoActivo* izquierdo;
	NodoActivo* derecho;
	NodoActivo* padre;
	bool disponibilidad;

	string codAlfanum;


	NodoActivo(string nombreActivo, const int codigo, string descripcion, NodoActivo* pad = NULL, NodoActivo* izq = NULL, NodoActivo* der = NULL) {
		this->dato = codigo;
		this->FE = 0;
		this->nombreActivo = nombreActivo;
		this->descripcioN = descripcion;
		this->izquierdo = izq;
		this->derecho = der;
		this->padre = pad;

	}


	NodoActivo(string nombreActivo, const int codigo, string descripcion, bool disponibilidad, NodoActivo* pad = NULL, NodoActivo* izq = NULL, NodoActivo* der = NULL) {
		this->dato = codigo;
		this->FE = 0;
		this->nombreActivo = nombreActivo;
		this->descripcioN = descripcion;
		this->izquierdo = izq;
		this->derecho = der;
		this->padre = pad;
		this->disponibilidad = disponibilidad;

	}


	NodoActivo(string nombreActivo, string codigo, string descripcion, NodoActivo* pad = NULL, NodoActivo* izq = NULL, NodoActivo* der = NULL) {
		this->codAlfanum = codigo;
		this->FE = 0;
		this->nombreActivo = nombreActivo;
		this->descripcioN = descripcion;
		this->izquierdo = izq;
		this->derecho = der;
		this->padre = pad;

	}


	NodoActivo(string nombreActivo, string codigo, string descripcion, bool disponibilidad, NodoActivo* pad = NULL, NodoActivo* izq = NULL, NodoActivo* der = NULL) {
		this->codAlfanum = codigo;
		this->FE = 0;
		this->nombreActivo = nombreActivo;
		this->descripcioN = descripcion;
		this->izquierdo = izq;
		this->derecho = der;
		this->padre = pad;
		this->disponibilidad = disponibilidad;

	}

	void setNombreAc(string nombre) {
		this->nombreActivo = nombre;
	}

	friend class AVL;
};

class ActivosRenta {
private:
	enum { IZQUIERDO, DERECHO };
	// Punteros de la lista, para cabeza y nodo actual:
	string controla = "";
	NodoActivo* raiz;
	NodoActivo* actual;
	int contador;
	int altura;

	void equilibrar(NodoActivo* nodo, int, bool);
	void rotacionSimpleIzquierda(NodoActivo* nodo);
	void rotacionSimpleDerecha(NodoActivo* nodo);
	void rotacionDobleIzquierda(NodoActivo* nodo);
	void rotacionDobleDerecha(NodoActivo* nodo);

	void Raiz() { actual = raiz; }
	void auxContador(NodoActivo*);
	void auxAltura(NodoActivo*, int);


	bool EsHoja(NodoActivo* r) { return !r->derecho && !r->izquierdo; }

	const int NumeroNodos();
	const int AlturaArbol();

	int Altura(const int dat);

	int& ValorActual() { return actual->dato; }


	void reservados(NodoActivo* nodo);
	void libres(NodoActivo* nodo);

	void inOrden(NodoActivo* nodo);
	void preOrden(NodoActivo* nodo);
	void postOrden(NodoActivo* nodo);

	void recor(NodoActivo* nodo);

	void arbolIndividual(NodoActivo*);

	void graficar(NodoActivo* nodo);
	NodoActivo* buscarActivo(NodoActivo* nodo, int id);

	NodoActivo* buscarActivo(NodoActivo* nodo, string id);

	string pasarDocumento(string,NodoActivo*, int,string);

public:
	// Constructor y destructor básicos:
	ActivosRenta() {
		this->raiz = 0;
		this->actual = 0;
	}

	void insertar(string nombreActivo, const int dat, string descripcion, bool disponibilidad);

	void insertar(string nombreActivo, string dat, string descripcion, bool disponibilidad);

	void eliminar(const int dat);
	bool buscar(const int dat);

	void recor();
	void reservados();
	void libres();

	NodoActivo* buscarActivo(int id);
	NodoActivo* buscarActivo(string codigoActivo);

	void modificar(int aReemplazar, string nombreActivo, const int dat, string descripcion, bool disponibilidad);

	void inOrden();
	void preOrden();
	void postOrden();
	void graficar();

	

	string pasarDocumento(string nombre,int numCluster);

	bool buscar(string);

};


