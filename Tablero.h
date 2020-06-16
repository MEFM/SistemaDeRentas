#pragma once
#include <iostream>
#include "ActivoRenta.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class DatosEmpleado {
private:

	string departamento;
	string empresa;


	string userName;
	string contraseña;
	string nombreCompleto;
	ActivosRenta* rentas;


public:
	DatosEmpleado(string usernarme, string contraseña, string nombreCompleto, ActivosRenta* rentas) {
		this->userName = userName;
		this->contraseña = contraseña;
		this->nombreCompleto = nombreCompleto;
		this->rentas = rentas;
	}

	DatosEmpleado(string usernarme, string contraseña, string nombreCompleto, ActivosRenta* rentas, string departamento, string empresa) {
		this->userName = usernarme;
		
		this->contraseña = contraseña;
		this->nombreCompleto = nombreCompleto;
		this->rentas = rentas;
		this->departamento = departamento;
		this->empresa = empresa;
	}


	void setUser(string user) {
		this->userName = user;
	}
	void setContraseña(string contraseña) {
		this->contraseña = contraseña;
	}
	void setNombre(string nombre) {
		this->nombreCompleto;
	}
	void setRentas(ActivosRenta* renta) {
		this->rentas = rentas;
	}
	void setDepartamento(string departamento) {
		this->departamento = departamento;
	}
	void setEmpresa(string empresa) {
		this->empresa = empresa;
	}


	string getNombre() {
		return nombreCompleto;
	}
	string getContrasenia() {
		return contraseña;
	}
	string getUser() {
		return userName;
	}
	ActivosRenta* getRentas() {
		return rentas;
	}
	string getDepartamento() {
		return this->departamento;
	}
	string getEmpresa() {
		return this->empresa;
	}

};



class NodoTablero {
public:
	NodoTablero* siguiente;
	NodoTablero* anterior;
	NodoTablero* abajo;
	NodoTablero* arriba;
	NodoTablero* adelante;
	NodoTablero* atras;

	string nombre;
	string codigo;
	DatosEmpleado* empleado;

	int grupo_graf;
	NodoTablero(string nombre, DatosEmpleado* empleado) {
		siguiente = 0;
		anterior = 0;
		abajo = 0;
		arriba = 0;
		adelante = 0;
		atras = 0;

		grupo_graf = 1;

		this->nombre = nombre;
		this->empleado = empleado;
	}

};

class Tablero
{
private:
	NodoTablero* cabecera;
	NodoTablero* crearEmpresa(string empresa);
	NodoTablero* crearDepartamento(string departamento);

	NodoTablero* buscarEmpresa(string empresa, NodoTablero*);
	NodoTablero* buscarDepa(string departamento, NodoTablero*);

	int grupoColumna(NodoTablero*);
	int idGrupoColumna(NodoTablero*);
	int node_idgraph(NodoTablero* temp);
public:
	Tablero() {
		//Aca va iniciado el nodo raiz
		cabecera = new NodoTablero("", 0);
	}

	void insertarElemento(string usernarme, string contraseña, string nombreCompleto, ActivosRenta* rentas, string departamento, string empresa);


	NodoTablero* buscarNodo(string usuario);
	NodoTablero* buscarNodo(string usuario, string departamento, string empresa);//Metodo de soporte

	bool verificarEmpresa(string empresa, NodoTablero* inicio, NodoTablero* nodoUsuario);
	bool verificarDepa(string empresa, NodoTablero* inicio, NodoTablero* nodoUsuario);

	void recorrerTablero();
	void graficar();

	void reporteEmpresa(string empresa);
	void reporteDepartamento(string departamento);

};

