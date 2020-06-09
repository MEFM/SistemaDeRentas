#include "ActivoRenta.h"


void ActivoRenta::buscar(int id) {
	if (this->raiz == 0) {
		cout << "Vacio aun no hay nada" << endl;
		return;
	}
	this->buscar(id, raiz);
}

NodoActivo* ActivoRenta::buscar(int id, NodoActivo* r) {
	if (raiz == 0) {
		cout << "Lo sentimos, el activo que buscas no existe o fue eliminado" << endl;
		return 0;
	}
	else if (r->getIdActivo() == id) {
		//Se ha encontrado el nodo buscado
		return r;
	}
	else if (r->getIdActivo() < id) {
		return buscar(id, r->getDerecha());
	}
	else {
		return buscar(id, r->getIzquierda());
	}
}

//Obtener el factor de equilibrio

int ActivoRenta::obtenerFe(NodoActivo* x) {
	if (x == 0) {
		return -1;
	}
	return x->getFe();
}

//Rotacion simple izquierda 
NodoActivo* ActivoRenta::rotacionSimpleIzquierda(NodoActivo* c) {

	NodoActivo* auxiliar = c->getIzquierda();

	c->setIzquierda(auxiliar->getDerecha());
	auxiliar->setDerecha(c);
	c->setFe(max(obtenerFe(c->getIzquierda()), obtenerFe(c->getDerecha())) + 1);
	auxiliar->setFe(max(obtenerFe(auxiliar->getIzquierda()), obtenerFe(auxiliar->getDerecha())) + 1);
	return auxiliar;


}

//Rotacion derecha
NodoActivo* ActivoRenta::rotacionSimpleDerecha(NodoActivo* c) {

	NodoActivo* auxiliar = c->getDerecha();
	c->setDerecha(auxiliar->getIzquierda());
	auxiliar->setIzquierda(c);
	c->setFe(max(obtenerFe(c->getIzquierda()), obtenerFe(c->getDerecha())) + 1);
	auxiliar->setFe(max(obtenerFe(auxiliar->getIzquierda()), obtenerFe(auxiliar->getDerecha())) + 1);
	return auxiliar;
}

//Rotacion doble derecha
NodoActivo* ActivoRenta::rotacionDobleDerecha(NodoActivo* c) {

	c->setIzquierda(this->rotacionSimpleDerecha(c->getIzquierda()));
	NodoActivo* temporal = rotacionSimpleIzquierda(c);

	return temporal;
}

//Rotacion double izquierdo
NodoActivo* ActivoRenta::rotacionDobleIzquierda(NodoActivo* c) {

	c->setDerecha(this->rotacionSimpleIzquierda(c->getDerecha()));
	NodoActivo* temporal = this->rotacionSimpleDerecha(c);

	return temporal;
}


void ActivoRenta::insertar(string nombre, string descripcion, int id) {
	NodoActivo* nuevo = new NodoActivo(nombre, descripcion, id);
	if (this->raiz == 0) {
		raiz = nuevo;
	}
	else {
		
		raiz = insertar(nuevo, raiz);
	}
}

NodoActivo* ActivoRenta::insertar(NodoActivo* nuevo, NodoActivo* subAr) {
	NodoActivo* nuevoPadre = subAr;
	
	if (nuevo->getIdActivo() < subAr->getIdActivo()) {
		if (subAr->getIzquierda() == 0)
		{

			subAr->setIzquierda(nuevo);
		}
		else
		{
			subAr->setIzquierda(insertar(nuevo, subAr->getIzquierda()));

			if ((obtenerFe(subAr->getIzquierda()) - obtenerFe(subAr->getDerecha())) == 2) {
				if (nuevo->getIdActivo() < subAr->getIzquierda()->getIdActivo()) {
					nuevoPadre = rotacionSimpleIzquierda(subAr);
				}
				else {
					nuevoPadre = rotacionDobleDerecha(subAr);
				}
			}
		}
	}
	else if (nuevo->getIdActivo() > subAr->getIdActivo()) {
		if (subAr->getDerecha() == 0) {
			subAr->setDerecha(nuevo);
		}
		else {
			subAr->setDerecha(insertar(nuevo, subAr->getDerecha()));
			if ((obtenerFe(subAr->getDerecha()) - obtenerFe(subAr->getIzquierda())) == 2) {
				nuevoPadre = rotacionSimpleDerecha(subAr);
			}
			else {
				nuevoPadre = rotacionDobleIzquierda(subAr);
			}
		}
	}
	else {
		cout << "Repetido insertar arctivo con otro codigo, porfa" << endl;
	}

	if ((subAr->getIzquierda() == 0) && (subAr->getDerecha() != 0)) {
		subAr->setFe(subAr->getDerecha()->getFe() + 1);
	}
	else if ((subAr->getDerecha() == 0) && (subAr->getIzquierda() != 0)) {
		subAr->setFe(subAr->getIzquierda()->getFe() + 1);
	}
	else {
		subAr->setFe(max(obtenerFe(subAr->getIzquierda()), obtenerFe(subAr->getDerecha())) + 1);
	}

	return nuevoPadre;
}

void ActivoRenta::grfInorden() {
	if (this->raiz != 0) {
		recorridoInnorden(this->raiz);
	}
	else {
		cout << "" << endl;
	}
}

void ActivoRenta::grfPostorden() {
	if (this->raiz != 0) {
		recorridoPostorden(this->raiz);
	}
	else {
		cout << "" << endl;
	}
}

void ActivoRenta::gPreorden() {
	if (this->raiz != 0) {
		recorridoPreorden(this->raiz);
	}
	else {
		cout << "" << endl;
	}
}


void ActivoRenta::recorridoInnorden(NodoActivo* nodo) {
	if (nodo != 0) {

		recorridoInnorden(nodo->getIzquierda());
		cout << nodo->getIdActivo() << endl;
		recorridoInnorden(nodo->getDerecha());
	}
}

void ActivoRenta::recorridoPostorden(NodoActivo* nodo) {
	if (nodo != 0) {
		recorridoPostorden(nodo->getIzquierda());
		recorridoPostorden(nodo->getDerecha());
		cout << nodo->getIdActivo() << endl;
	}
}

void ActivoRenta::recorridoPreorden(NodoActivo* nodo) {
	if (nodo != 0) {
		cout << nodo->getIdActivo() << endl;
		recorridoPreorden(nodo->getIzquierda());
		recorridoPreorden(nodo->getDerecha());
	}
}