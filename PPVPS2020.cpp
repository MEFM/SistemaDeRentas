// PPVPS2020.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#pragma warning(disable : 4996)

#include <iostream>
#include <sstream>
#include <string>
#include <time.h>


#include <stdio.h>
#include <stdlib.h>
#include "ActivoRenta.h"
#include "Tablero.h"
#include "Historial.h"

#define _CRT_SECURE_NO_WARNINGS


using namespace std;


int idHistorialActivos;

Tablero* tablero = new Tablero();
Historial* transacciones = new Historial();



void Mostrar(int& d, int FE)
{
	cout << d << endl;
}

//Area general
void logIn();



string getDate()
{
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);

	stringstream ss_year;
	ss_year << timePtr->tm_year + 1900;
	string Year = ss_year.str();

	stringstream ss_month;
	ss_month << timePtr->tm_mon + 1;
	string Month = ss_month.str();
	if (atoi(Month.c_str()) < 10)
		Month = "0" + Month;

	stringstream ss_day;
	ss_day << timePtr->tm_mday;
	string Day = ss_day.str();
	if (atoi(Day.c_str()) < 10)
		Day = "0" + Day;

	stringstream ss_hour;
	ss_hour << timePtr->tm_hour;
	string Hour = ss_hour.str();
	if (atoi(Hour.c_str()) < 10)
		Hour = "0" + Hour;

	stringstream ss_min;
	ss_min << timePtr->tm_min;
	string Min = ss_min.str();
	if (atoi(Min.c_str()) < 10)
		Min = "0" + Min;

	stringstream ss_sec;
	ss_sec << timePtr->tm_sec;
	string Sec = ss_sec.str();
	if (atoi(Sec.c_str()) < 10)
		Sec = "0" + Sec;

	
	string Fecha = Day + "/" + Month + "/" + "/" + Year + " -- " + Hour + ":" + Min + ":" + Sec;
	return Fecha;
}
/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/

//Esto es para el area de administrador
void registrarUsuario();
void activosUser() {};
void rentasCsuario();
void activosDeUsuario() {}; // Grafica de arbol despues de buscar en matriz


void ordenarTransac() {};

/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/
void menuAdministrador() {
	int opcion = 0;
	bool validador = true;


	while (validador) {

		cout << "----------------Bienvenido al sistema de rentas----------------" << endl;
		cout << "-----------------------------Menu------------------------------" << endl;
		cout << "1. Registrar usuario" << endl;
		cout << "2. Reporte Matriz" << endl;
		cout << "3. Reportes de un departamento" << endl;
		cout << "4. Reportes de una empresa" << endl;
		cout << "5. Reporte transacciones" << endl;
		cout << "6. Reporte Activos de un usuario" << endl;
		cout << "7. Reporte Activos rentados por un usuario" << endl;
		cout << "8. Ordenar transacciones" << endl;
		cout << "9. Salir de modo admin." << endl;

		cout << "Ingrese una opcion" << endl;
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			registrarUsuario();
			break;
		case 2:
			tablero->graficar();
			break;
		case 3:
			//Crear metodo para sacar los metodos de cada departamento
			//tablero->graficasDepartamento();
			/*
				Tiene que ser un menu con las posibilidades de generar
				los reportes de todos los usuarios de un mes
				cagadales
			*/
			break;
		case 4:
			//Crear metodo para sacar los metodos de cada empresa
						//tablero->graficasEmpresa();
			/*
				Tiene que ser un menu con las posibilidades de generar
				los reportes de todos los usuarios de una empresa
				cagadales
			*/
			break;
		case 5:
			//transacciones->graficar();
			break;
		case 6:
			activosDeUsuario();
			break;
		case 7:
			rentasCsuario();
			break;
		case 8:
			ordenarTransac();
			break;
		case 9:
			validador = false;
			break;
		default:

			break;
		}
	}

}
void registrarUsuario() {
	//DatosEmpleado(string usernarme, string contraseña, string nombreCompleto, ActivoRenta rentas, string departamento, string empresa) {

	string userName, contrasea, nombreCompleto, departamento, empresa;
	system("cls");
	cout << "Ingresar Nombre de usuario" << endl;
	cin.getline((char*)userName.c_str(), 100, '\n');
	cin.ignore();
	cout << "Ingresar Contraseña" << endl;
	cin.getline((char*)contrasea.c_str(), 100, '\n');
	cin.ignore();
	cout << "Ingresar Nombre completo" << endl;
	cin.getline((char*)nombreCompleto.c_str(), 100, '\n');
	cin.ignore();
	cout << "Ingresar Departamento" << endl;
	cin.getline((char*)departamento.c_str(), 100, '\n');
	cin.ignore();
	cout << "Ingresar Empresa" << endl;
	cin.getline((char*)empresa.c_str(), 100, '\n');
	cin.ignore();

	tablero->insertarElemento(userName, contrasea, nombreCompleto, ActivosRenta(), empresa, departamento);
}
void rentasCsuario() {
	//Usuario a buscar 


}

/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/

//Esto es para El usuario
void agregarA(ActivosRenta);
void eliminarActivo(ActivosRenta);
void modificarActivo(ActivosRenta);
void rentarActivo(ActivosRenta, NodoTablero*);
void activosRentados(ActivosRenta);
void misActivosRentados(ActivosRenta);

void menuUsuario(NodoTablero* usuario) {
	int opcion = 0;
	bool validador = true;

	while (validador) {
		system("cls");
		cout << "--------------------------" << usuario->empleado->getNombre() << "--------------------------" << endl;
		cout << "----------------------------------------------------------------------------" << endl << endl;

		cout << "1. Agregar activo." << endl;
		cout << "2. Elminacion de activo." << endl;
		cout << "3. Modificar Activo." << endl;
		cout << "4. Rentar Activo." << endl;
		cout << "5. Activos Rentados" << endl;
		cout << "6. Mis activos rentados" << endl;
		cout << "7. Cerrar sesion" << endl;
		cout << "Ingrese opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			agregarA(usuario->empleado->getRentas());
			break;
		case 2:
			eliminarActivo(usuario->empleado->getRentas());
			break;
		case 3:
			modificarActivo(usuario->empleado->getRentas());
			break;
		case 4:
			rentarActivo(usuario->empleado->getRentas(), usuario);
			break;
		case 5:
			activosRentados(usuario->empleado->getRentas());
			break;
		case 6:
			//Hacer recorrido de mis activos rentados(por usuario)
			misActivosRentados(usuario->empleado->getRentas());
			break;
		case 7:
			//Salir a Log in
			validador = false;
			break;
		default:
			break;
		}
	}



}
void agregarA(ActivosRenta arbolUsuario) {
	cout << "Todos los activos ingresados en este apartado seran disponibles." << endl;
	cout << "-----------------------Agregar activos-----------------------" << endl;
	string nombreActivo, descripcion;
	int codigo;
	//Lo siento solo lo pude hacer con enteros
	cout << "Ingrese el ID del activo, no repetido." << endl;
	cin >> codigo;
	if (arbolUsuario.buscar(codigo) == true) {
		cout << "Codigo previamente ingresado" << endl;
		return;
	}
	cout << "Ingrese nombre del activo." << endl;
	cin.getline((char*)nombreActivo.c_str(), 100, '\n');
	cin.ignore();
	cout << "Ingrese descripcion." << endl;
	cin.getline((char*)descripcion.c_str(), 100, '\n');
	cin.ignore();

	arbolUsuario.insertar(nombreActivo, codigo, descripcion, true);

}

void eliminarActivo(ActivosRenta arbolUsuario) {
	cout << "Los activos aca eliminados no tienen reposicion" << endl;
	cout << "-----------------Eliminar activos de cartera-----------------" << endl;
	arbolUsuario.libres();
	cout << endl << endl;
	int id;
	cout << "Ingrese ID a eliminar" << endl;
	cin >> id;
	if (arbolUsuario.buscar(id) == true) {
		if (arbolUsuario.buscarActivo(id)->disponibilidad == false) {
			cout << "El activo no esta disponible " << endl;
		}
		else {
			arbolUsuario.eliminar(id);
		}
	}
	else {
		cout << "Ni si quiera existe man ajajaja" << endl;
	}

}

void modificarActivo(ActivosRenta arbolUsuario) {
	cout << "Los cambios son irreversibles. SIN ESPACIOS, SOLO '-'." << endl;
	cout << "--------------------Modificacion Activo--------------------" << endl;
	cout << endl << endl;
	arbolUsuario.libres();
	cout << endl;
	int idModificar;
	cout << "Ingresa el ID del activo a modificar" << endl;
	cin >> idModificar;
	if (arbolUsuario.buscar(idModificar) == true) {
		NodoActivo* activo = arbolUsuario.buscarActivo(idModificar);
		if (activo->disponibilidad == true) {
			cout << "entr" << endl;
			string gfd, descripcion;

			cout << "Cambiar nombre activo: " << endl;
			cin >> gfd;
			cout << "Agregar nueva descripcion: " << endl;
			cin >> descripcion;
			cout << gfd << endl;
			cout << descripcion << endl;
			arbolUsuario.modificar(idModificar, gfd, idModificar, descripcion, true);

			cout << "" << endl;
		}
		else {
			cout << "Activo que quieres reemplazar esta ocupado." << endl;
			return;
		}
	}
	else {
		cout << "El activo buscado no existe" << endl;
	}
}

void rentarActivo(ActivosRenta arbolUsuario, NodoTablero* infoUsuario) {
	cout << "----------------------------Catalogo de activos ----------------------------" << endl;
	arbolUsuario.libres();

	cout << endl << endl;
	int opcion;
	cout << "1. Rentar activo." << endl;
	cout << "2. Regresar a menu principal." << endl;
	cout << "Ingrese opcion";
	cin >> opcion;
	cout << endl << endl;
	if (opcion == 1) {
		int activo_abuscar;
		cout << "Bienvenido a las reservaciones." << endl;
		string nombreActivo, fecha, tiempo;
		cout << endl << "Ingresa el id del activo a reservar." << endl;
		cin >> activo_abuscar;


		if (arbolUsuario.buscar(activo_abuscar) == true) {
			//Solo admite que utilices activos que estan disponibles
			string alfaNumerico = "";
			nombreActivo = arbolUsuario.buscarActivo(activo_abuscar)->nombreActivo;
			fecha = getDate();
			cout << "Ingresa el tiempo que tendra la propiedad en alquiler." << endl;
			cin >> tiempo;
			arbolUsuario.buscarActivo(activo_abuscar)->disponibilidad = false;
			transacciones->insertar(alfaNumerico, activo_abuscar, nombreActivo, infoUsuario, fecha, tiempo);
		}
		else {
			cout << "El activo no esta en el catalogo en este momento." << endl;
		}

	}
	else {
		cout << "Vete sin tu renta peus :(" << endl;
	}
}

void activosRentados(ActivosRenta arbolUsuario) {
	cout << "----------------------------Activos Rentados----------------------------" << endl;
	arbolUsuario.reservados();
	cout << endl << "1. Devolver activo" << endl;
	cout << "2. Regresar a menu usuario" << endl;
	int opcion;
	cin >> opcion;
	if (opcion == 1) {
		//Devolver activo
		opcion = 0;
		cout << "Ingrese el id del activo a devolver" << endl;
		cin >> opcion;
		if (arbolUsuario.buscar(opcion) == true) {
			if (arbolUsuario.buscarActivo(opcion)->disponibilidad == false) {
				arbolUsuario.buscarActivo(opcion)->disponibilidad = true;
				cout << "Devolucion concretada." << endl;
			}
			else {
				cout << "El activo no esta alquilado, no lo puedes devolver." << endl;
			}
		}
		else {
			cout << "El activo que buscas no existe" << endl;
		}
	}
	else {
		cout << "Hasta la proxima" << endl;
	}
}

void misActivosRentados(ActivosRenta arbolUsuario) {
	cout << "----------------------------Mis Activos Rentados----------------------------" << endl;
	arbolUsuario.reservados();
	cout << endl;
}


int main()
{
	string palabra1 = "a5B3";
	string palabra2 = "a5B2";

	if (palabra1 < palabra2) {
		cout << "Correcto" << endl;
	}
	else {
		cout << "Hm" << endl;
	}
	Tablero* tablero = new Tablero();



	ActivosRenta arbol;

	arbol.insertar("Hol", 10, "", true);
	arbol.insertar("Mi", 5, "", false);
	arbol.insertar("Op", 13, "", true);
	arbol.insertar("Lp", 1, "", false);
	arbol.insertar("Qw", 6, "", false);
	arbol.insertar("Gf", 12, "", true);
	arbol.insertar("bf", 11, "", false);
	arbol.insertar("Mk", 17, "", true);
	arbol.insertar("Ml", 15, "", true);

	ActivosRenta arbol2;

	arbol2.insertar("a1", 10, "", true);
	arbol2.insertar("a2w", 5, "", false);
	arbol2.insertar("a3ddd", 13, "", true);
	arbol2.insertar("a4", 1, "", false);
	arbol2.insertar("a5", 6, "", false);
	arbol2.insertar("a6", 12, "", true);
	arbol2.insertar("a7", 11, "", false);
	arbol2.insertar("a8", 17, "", true);
	arbol2.insertar("a9", 15, "", true);
	

	ActivosRenta arbol3;

	arbol3.insertar("b10", 10, "", true);
	arbol3.insertar("b11sw", 5, "", false);
	arbol3.insertar("b12dddd", 13, "", true);
	arbol3.insertar("b13L", 1, "", false);
	arbol3.insertar("b14w", 6, "", false);
	arbol3.insertar("b15f", 12, "", true);
	arbol3.insertar("b16m", 11, "", false);
	arbol3.insertar("b17mio", 17, "", true);
	arbol3.insertar("b18kiki", 15, "", true);

	ActivosRenta arbol4;

	arbol4.insertar("c19s", 10, "", true);
	arbol4.insertar("c20sw", 5, "", false);
	arbol4.insertar("c21dddd", 13, "", true);
	arbol4.insertar("c22L", 1, "", false);
	arbol4.insertar("c23w", 6, "", false);
	arbol4.insertar("c24f", 12, "", true);
	arbol4.insertar("c25m", 11, "", false);
	arbol4.insertar("c26mio", 17, "", true);
	arbol4.insertar("c27kiki", 15, "", true);

	//arbol.graficar();

	tablero->insertarElemento("Mynor", "Mynor", "fd", arbol, "max", "guatemala");
	tablero->insertarElemento("susan", "asd", "fd", arbol, "hp", "jutiapa");
	tablero->insertarElemento("sucel", "asd", "fd", arbol, "hp", "jalapa");
	tablero->insertarElemento("roxana", "asd", "fd", arbol, "walmart", "jalapa");
	tablero->insertarElemento("andrea", "Mynor", "fd", arbol2, "walmart", "jalapa");
	tablero->insertarElemento("sebas", "asd", "fd", arbol3, "walmart", "jalapa");
	tablero->insertarElemento("andres", "asd", "fd", arbol, "hp", "guatemala");
	tablero->insertarElemento("willy", "asd", "fd", arbol, "max", "jalapa");
	tablero->insertarElemento("Mynor", "asd", "fd", arbol4, "walmart", "guatemala");
	tablero->insertarElemento("Albrto", "alb", "fd", arbol, "max", "guatemala");
	tablero->insertarElemento("Mario", "alb", "fd", arbol, "hp", "guatemala");
	tablero->insertarElemento("Alfredo", "asd", "fd", arbol, "max", "jutiapa");
	
	tablero->recorrerTablero();

	//registrarUsuario();
	//tablero->graficar();

	NodoTablero* prueba = new NodoTablero("", new DatosEmpleado("MEFM", "asdf", "Estui", arbol, "ss", "qq"));

	cout << endl << "Transacciones" << endl;
	transacciones->insertar("asfadsfasdf", 9, "1a ", prueba, "sdfsdf", "sdfsdf");
	transacciones->insertar("arrancala234", 9, "1a ", prueba, "sdfsdf", "sdfsdf");
	transacciones->insertar("fasf332123", 9, "1a ", prueba, "sdfsdf", "sdfsdf");
	transacciones->insertar("afasdf232", 1, "2d", new NodoTablero("", new DatosEmpleado("", "", "All Migth", arbol, "", "")), "", "");
	transacciones->insertar("as234asdf", 3, "3e", new NodoTablero("", new DatosEmpleado("", "", "Deju", arbol, "", "")), "", "");
	transacciones->insertar("asfadsA3df", 5, "4f", new NodoTablero("", new DatosEmpleado("", "", "Mario", arbol, "", "")), "", "");
	transacciones->insertar("asfadsfasd354f", 10, "5c", new NodoTablero("", new DatosEmpleado("", "", "Ascari", arbol, "", "")), "", "");


	transacciones->recorrer();
	//transacciones->graficar();
	//transacciones->graficarXusuario(prueba);
	tablero->reporteEmpresa("walmart");
	string a;

	/*
	miObjeto->insertarElemento("mynor", 1, "max", "Guatemala");
	miObjeto->insertarElemento("susan", 2, "hp", "jutiapa");
	miObjeto->insertarElemento("susel", 3, "hp", "jalapa");
	miObjeto->insertarElemento("roxana", 4, "walmart", "jalapa");
	miObjeto->insertarElemento("andrea", 5, "walmart", "jalapa");
	miObjeto->insertarElemento("sebas", 6, "walmart", "jalapa");
	miObjeto->insertarElemento("andres", 7, "hp", "Guatemala");
	miObjeto->insertarElemento("willy", 8, "max", "jalapa");
	miObjeto->insertarElemento("mynor", 6, "walmart", "Guatemala");
	*/

	

	//arbol.recor();

	cout << endl << endl << "Estos metodos son lso que estan implementados ya en mi proyecto" << endl;
	cout << "Por eso es diferente a los metodos de la tarea." << endl;
	//arbol.reservados();


	/*

	*/
	//tablero->recorrerTablero();
	//tablero->graficar();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
