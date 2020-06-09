#pragma once
#include <iostream>
#include<string>
#include <algorithm>


using namespace std;
class NodoActivo {
private:
	NodoActivo* izquierda;
	NodoActivo* derecha;
	int fe; //factor de equilibrio
	string nombreActivo;
	string descripcion;
	int idActivo;
public:
	NodoActivo(string nombreActivo, string descripcion, int idActivo) {
		this->izquierda = 0;
		this->derecha = 0;
		this->fe = 0;
		this->nombreActivo = nombreActivo;
		this->descripcion = descripcion;
		this->idActivo = idActivo;
	}

	void setIzquierda(NodoActivo* izquierda) {
		this->izquierda = izquierda;
	}
	void setDerecha(NodoActivo* derecha) {
		this->derecha = derecha;
	}
	void setNombre(string nombre) {
		this->nombreActivo = nombre;
	}
	void setDescripcion(string descripcion) {
		this->descripcion = descripcion;
	}
	void setIdActivo(int idActivo) {
		this->idActivo = idActivo;
	}
	void setFe(int fe) {
		this->fe = fe;
	}

	
	NodoActivo* getIzquierda() {
		return izquierda;
	}
	NodoActivo* getDerecha() {
		return derecha;
	}
	string getNombre() {
		return nombreActivo;
	}
	string getDescripcion() {
		return descripcion;
	}
	int getIdActivo() {
		return idActivo;
	}
	int getFe() {
		return this->fe;
	}

};

class ActivoRenta
{
private:
	NodoActivo* raiz;

	NodoActivo* insertar(NodoActivo* nuevo, NodoActivo* subAr);
	NodoActivo* buscar(int id, NodoActivo* r);
	int obtenerFe(NodoActivo* x);

	NodoActivo* rotacionSimpleIzquierda(NodoActivo* c);
	NodoActivo* rotacionSimpleDerecha(NodoActivo* c);
	NodoActivo* rotacionDobleIzquierda(NodoActivo* c);
	NodoActivo* rotacionDobleDerecha(NodoActivo* c);

	void recorridoPreorden(NodoActivo*);
	void recorridoPostorden(NodoActivo*);
	void recorridoInnorden(NodoActivo*);

public:
	ActivoRenta() {
		raiz = 0;
	}



	void insertar(string nombre, string descripcion, int id);
	void* eliminar(string id);
	void buscar(int id);

	void imprimirEnConsola(string id);
	void graficar();

	void gPreorden();
	void grfInorden();
	void grfPostorden();

};

