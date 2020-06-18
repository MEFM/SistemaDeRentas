// PPVPS2020.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
//#pragma warning(disable : 4996)

#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include "ActivoRenta.h"
#include "Tablero.h"
#include "Historial.h"

#define _CRT_SECURE_NO_WARNINGS
#define LONGITUD_DESEADA 15

using namespace std;


int idHistorialActivos;
int clave = 0;




Tablero* tablero = new Tablero();
Historial* transacciones = new Historial();




void menuUsuario(NodoTablero*);
void menuAdministrador();



//Area general
void logIn() {

	string nombre, contrasenia, departamento, empresa;

	bool validador = true;
	int option = 0;

	while (validador) {

		cout << "--------------------------PROYECTO RENTA ACTIVOS--------------------------" << endl;

		cout << "1. INGRESAR COMO ADMINISTRADOR" << endl;
		cout << "2. INGRESAR COMO TRABAJADO." << endl;
		cout << "3. SALIR." << endl;

		cout << endl << "Ingrese una opcion: ";
		cin >> option;

		switch (option)
		{
		case 1:
			cout << endl << endl;
			cout << "Administrador." << endl << endl;
			cout << "Ingrese name del administrador" << endl;
			cin >> nombre;
			cout << "Ingrese contraseña del administrador" << endl;
			cin >> contrasenia;

			if (nombre == "admin" && contrasenia == "admin") {
				menuAdministrador();
			}
			else {
				cout << "Usuario o Contrasenia erroneos" << endl;
			}

			break;

		case 2:
			cout << endl << endl;
			cout << "Usuario" << endl << endl;
			cout << "Ingrese username del usuario" << endl;
			cin >> nombre;
			cout << "Ingrese departamento" << endl;
			cin >> departamento;
			cout << "Ingrese empresa" << endl;
			cin >> empresa;
			cout << "Ingrese contraseña" << endl;
			cin >> contrasenia;

			if (tablero->buscarNodo(nombre, empresa, departamento) != 0) {
				if (tablero->buscarNodo(nombre, empresa, departamento)->empleado->getContrasenia() == contrasenia) {
					menuUsuario(tablero->buscarNodo(nombre, empresa, departamento));
				}
				else {
					cout << "Username o Contraseña erroneos." << endl;
				}
			}
			else {
				cout << nombre << " " << departamento << " " << empresa;
			}


			break;
		case 3:
			validador = false;
			break;
		default:
			break;
		}
	}

}



int  rangoaleatorio(int min, int max) {
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void cadaleatoria(int Longitud, char* Destino) {
	char Muestra[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	for (int x = 0; x < Longitud; x++) {
		int indiceAleatorio = rangoaleatorio(0, (int)strlen(Muestra) - 1);
		Destino[x] = Muestra[indiceAleatorio];
	}
}

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
void activosUser();
void rentasCsuario();
void activosDeUsuario(); // Grafica de arbol despues de buscar en matriz

void reporteXdepartamento();
void reporteXempresa();

void ordenarTransac();

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
			reporteXdepartamento();
			break;
		case 4:
			reporteXempresa();
			break;
		case 5:
			transacciones->graficar();
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
void activosDeUsuario() {
	string nombre, departamento, empresa;

	cout << "--------------------------------Activos de un usuario especifico--------------------------------" << endl;
	cout << "Ingrese nombre de usuario." << endl;
	cin >> nombre;
	cout << "Ingrese departamento" << endl;
	cin >> departamento;
	cout << "Ingrese empresa" << endl;
	cin >> empresa;

	NodoTablero* auxiliar = tablero->buscarNodo(nombre, empresa, departamento);

	if (auxiliar != 0) {
		auxiliar->empleado->getRentas()->graficar();
	}
	else {
		cout << "El usuario no existe o no ingresaste bien sus datos" << endl;
	}


}
void registrarUsuario() {
	//DatosEmpleado(string usernarme, string contraseña, string nombreCompleto, ActivoRenta rentas, string departamento, string empresa) {

	string userName, contrasea, nombreCompleto, departamento, empresa;
	system("cls");
	cout << "Por favor, SIN ESPACIOS." << endl << endl;
	cout << "Ingresar Nombre de usuario" << endl;
	cin >> userName;
	cout << "Ingresar Contraseña" << endl;
	cin >> contrasea;
	cout << "Ingresar Nombre completo" << endl;
	cin >> nombreCompleto;
	cout << "Ingresar Departamento" << endl;
	cin >> departamento;
	cout << "Ingresar Empresa" << endl;
	cin >> empresa;

	if (tablero->buscarNodo(userName, empresa, departamento) != 0) {
		cout << "Hey ingresaste un usuario que ya existe bro." << endl;
	}
	else {
		tablero->insertarElemento(userName, contrasea, nombreCompleto, new ActivosRenta(), empresa, departamento);
	}

}
void rentasCsuario() {
	//Usuario a buscar 
	string uName, departamento, empresa;
	//Para buscar al usuario
	cout << "Ingresar nombre del usuario a verificar sus rentas." << endl;
	cin >> uName;
	cout << "Ingresar el departamento al que pertenece." << endl;
	cin >> departamento;
	cout << "Ingresar la empresa en la que trabaja" << endl;
	cin >> empresa;

	NodoTablero* nodoUsuario = tablero->buscarNodo(uName, empresa, departamento);

	if (nodoUsuario != 0) {
		transacciones->graficarXusuario(nodoUsuario);
	}
	else {
		cout << "No existe el usuario." << endl;
	}

}
void reporteXdepartamento() {
	cout << "				Reporte de activos por departamento." << endl;
	string departamento;
	cout << "Ingrese el nombre del departamento a encontrar sus reportes." << endl;
	cin >> departamento;

	if (tablero->buscarNodo(departamento) != 0) {
		tablero->reporteDepartamento(departamento);
	}
	else {
		cout << "No existe ese departamento" << endl;
	}


}
void reporteXempresa() {
	cout << "				Reporte de activos por empresa." << endl;
	string empresa;
	cout << "Ingrese el nombre de la empresa a encontrar sus reportes." << endl;
	cin >> empresa;

	tablero->reporteEmpresa(empresa);


}
void ordenarTransac() {
	cout << "	Mostrar ordenado" << endl;
	cout << "1. Mayor a Menor (->)" << endl;
	cout << "2. Menor a Mayor (<-)" << endl;
	int opcion = 0;
	cout << "Ingrese opcion: ";
	cin >> opcion;
	if (opcion == 1) {
		transacciones->graficar();
	}
	else {
		transacciones->graficarAlReves();
	}
	cout << endl;
}

/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/

//Esto es para El usuario
void agregarA(ActivosRenta*);
void eliminarActivo(ActivosRenta*);
void modificarActivo(ActivosRenta*);
void rentarActivo(ActivosRenta*, NodoTablero*);
void activosRentados(ActivosRenta*, NodoTablero*);
void misActivosRentados(ActivosRenta*);

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
			//cambiar
			activosRentados(usuario->empleado->getRentas(), usuario);
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

void agregarA(ActivosRenta* arbolUsuario) {
	cout << "Todos los activos ingresados en este apartado seran disponibles." << endl;
	cout << "-----------------------Agregar activos-----------------------" << endl;
	string nombreActivo, descripcion;
	string id;
	char destino[LONGITUD_DESEADA + 1] = "";
	cadaleatoria(LONGITUD_DESEADA, destino);
	id = destino;

	//Lo siento solo lo pude hacer con enteros
	cout << "Ingrese el ID del activo, no repetido." << endl;

	if (arbolUsuario->buscar(id) == true) {
		cout << "Codigo previamente ingresado" << endl;
		return;
	}
	cout << "Ingrese nombre del activo." << endl;
	cin >> nombreActivo;


	cout << "Ingrese descripcion." << endl;
	cin >> descripcion;

	arbolUsuario->insertar(nombreActivo, id, descripcion, true);

}

void eliminarActivo(ActivosRenta* arbolUsuario) {
	cout << "Los activos aca eliminados no tienen reposicion" << endl;
	cout << "-----------------Eliminar activos de cartera-----------------" << endl;
	arbolUsuario->libres();
	cout << endl << endl;
	int id;
	cout << "Ingrese ID a eliminar" << endl;
	cin >> id;
	if (arbolUsuario->buscar(id) == true) {
		if (arbolUsuario->buscarActivo(id)->disponibilidad == false) {
			cout << "El activo no esta disponible " << endl;
		}
		else {
			arbolUsuario->eliminar(id);
		}
	}
	else {
		cout << "Ni si quiera existe man ajajaja" << endl;
	}

}

void modificarActivo(ActivosRenta* arbolUsuario) {
	cout << "Los cambios son irreversibles. SIN ESPACIOS, SOLO '-'." << endl;
	cout << "--------------------Modificacion Activo--------------------" << endl;
	cout << endl << endl;
	arbolUsuario->libres();
	cout << endl;
	string idModificar;
	cout << "Ingresa el ID del activo a modificar" << endl;
	cin >> idModificar;
	if (arbolUsuario->buscar(idModificar) == true) {
		NodoActivo* activo = arbolUsuario->buscarActivo(idModificar);
		if (activo->dato != 16843009) {
			cout << "entr" << endl;
			string gfd, descripcion;

			cout << "Cambiar nombre activo: " << endl;
			cin >> gfd;
			cout << "Agregar nueva descripcion: " << endl;
			cin >> descripcion;

			cout << endl << endl;
			activo->nombreActivo = gfd;
			activo->descripcioN = descripcion;
			//arbolUsuario->modificar(idModificar, gfd, idModificar, descripcion, true);

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

void rentarActivo(ActivosRenta* arbolUsuario, NodoTablero* infoUsuario) {
	cout << "----------------------------Catalogo de activos ----------------------------" << endl;

	tablero->activosDisponibles();

	cout << endl << endl;
	int opcion;
	cout << "1. Rentar activo." << endl;
	cout << "2. Regresar a menu principal." << endl;
	cout << "Ingrese opcion" << endl;
	cin >> opcion;
	cout << endl << endl;
	if (opcion == 1) {
		string activo_abuscar;
		cout << "Bienvenido a las reservaciones." << endl;
		string fecha, tiempo;
		cout << endl << "Ingresa el id del activo a reservar." << endl;
		cin >> activo_abuscar;

		//tablero->reservarActivo(activo_abuscar)->disponibilidad = false;
		//cout << "Este es mi nombre " << tablero->reservarActivo("1q0")->nombreActivo << endl;
		//tablero->nodoObjetivo("1q0")->empleado->getRentas()->libres();

		string id;
		char destino[LONGITUD_DESEADA + 1] = "";
		cadaleatoria(LONGITUD_DESEADA, destino);
		id = destino;

		if (tablero->reservarActivo(activo_abuscar) != 0) {
			cout << "Tiempo a reservar." << endl;
			cin >> tiempo;

			tablero->reservarActivo(activo_abuscar)->disponibilidad = false;
			transacciones->insertar(id, activo_abuscar, tablero->reservarActivo(activo_abuscar)->nombreActivo, infoUsuario, getDate(), tiempo);
			cout << "Activo rentado" << endl;
		}

	}
	else {
		cout << "Vete sin tu renta peus :(" << endl;
	}
}

void activosRentados(ActivosRenta* arbolUsuario, NodoTablero* usuario) {
	cout << "----------------------------Activos Rentados----------------------------" << endl;
	arbolUsuario->reservados();
	cout << endl << "1. Devolver activo" << endl;
	cout << "2. Regresar a menu usuario" << endl;
	string opcion;
	cin >> opcion;
	if (opcion == "1") {
		//Devolver activo
		opcion = "";
		cout << "Ingrese el id del activo a devolver" << endl;
		cin >> opcion;
		NodoActivo* auxiliar = tablero->reservarActivo(opcion);
		if (auxiliar != 0) {
			auxiliar->disponibilidad = true;
			transacciones->devolucion(usuario, opcion);
		}
		else {
			cout << "No existe o no esta reservado a nombre tuyo." << endl;
		}
	}
	else {
		cout << "Hasta la proxima" << endl;
	}
}

void misActivosRentados(ActivosRenta* arbolUsuario) {
	cout << "----------------------------Mis Activos Rentados----------------------------" << endl;
	arbolUsuario->reservados();
	cout << endl;
	system("pause");
}




int main()
{

	logIn();


	//ActivosRenta* arbol = new ActivosRenta();

	//arbol->insertar("Hol", "1q0", "", true);
	//arbol->insertar("Mi", "5e", "", false);
	//arbol->insertar("Op", "1b3", "", true);
	//arbol->insertar("Lp", "1a", "", false);
	//arbol->insertar("Qw", "6b", "", false);
	//arbol->insertar("Gf", "1c2", "", true);
	//arbol->insertar("bf", "11d", "", false);
	//arbol->insertar("Mk", "17e", "", true);
	//arbol->insertar("Ml", "15f", "", true);


	//ActivosRenta* arbol2 = new ActivosRenta();

	//arbol2->insertar("a1", "1f0", "", true);
	//arbol2->insertar("a2w", "h5", "", false);
	//arbol2->insertar("a3ddd", "i13", "", true);
	//arbol2->insertar("a4", "1j", "", false);
	//arbol2->insertar("a5", "k6", "", false);
	//arbol2->insertar("a6", "1l2", "", true);
	//arbol2->insertar("a7", "m11", "", false);
	//arbol2->insertar("a8", "1n7", "", true);
	//arbol2->insertar("a9", "15ni", "", true);


	//ActivosRenta* arbol3 = new ActivosRenta();

	//arbol3->insertar("b10", "o10", "", true);
	//arbol3->insertar("El", "55p6", "Unique", true);
	//arbol3->insertar("b12dddd", "1q3", "", true);
	//arbol3->insertar("b13L", "r1", "", false);
	//arbol3->insertar("b14w", "s6", "", false);
	//arbol3->insertar("b15f", "1t2", "", true);
	//arbol3->insertar("b16m", "11u", "", false);
	//arbol3->insertar("b17mio", "1v7", "", true);
	//arbol3->insertar("b18kiki", "w15", "", true);

	//ActivosRenta* arbol4 = new ActivosRenta();


	//arbol4->insertar("c19s", "afsd", "a", true);
	//arbol4->insertar("c20sw", "qwer", "b", false);
	//arbol4->insertar("c21dddd", "oiuo", "c", true);
	//arbol4->insertar("c22L", "Adfc", "d", false);
	//arbol4->insertar("c23w", "mlOPo", "e", false);
	//arbol4->insertar("c24f", "csxxqQ", "f", true);
	//arbol4->insertar("c25m", "cisCooo", "g", false);
	//arbol4->insertar("c26mio", "AklaksdkioIQoi", "h", true);
	//arbol4->insertar("c27kiki", "dd", "i", true);


	//tablero->insertarElemento("Mynor", "Mynor", "fd", arbol, "max", "guatemala");
	//tablero->insertarElemento("susan", "asd", "fd", arbol2, "hp", "jutiapa");
	//tablero->insertarElemento("sucel", "asd", "fd", arbol3, "hp", "jalapa");
	//tablero->insertarElemento("roxana", "asd", "fd", arbol4, "walmart", "jalapa");

	//tablero->reservarActivo("15f")->disponibilidad = false;
	//cout << "Este es mi nombre " << tablero->reservarActivo("15f")->nombreActivo << endl;
	//tablero->nodoObjetivo("15f")->empleado->getRentas()->libres();

	//NodoTablero* prueba = new NodoTablero("", new DatosEmpleado("MEFM", "asdf", "Estui", arbol, "ss", "qq"));


	//transacciones->insertar("sddfs", "1q0", tablero->reservarActivo("1q0")->nombreActivo, prueba, getDate(), "sd", true);

	//transacciones->graficar();


	//tablero->activosDisponibles();
	/*arbol->buscarActivo("1q0")->disponibilidad = false;

	arbol->libres();*/


	//int controlador = 0;
	//string palabra = "";
	//string id;
	//char destino[LONGITUD_DESEADA + 1] = "";
	//cadaleatoria(LONGITUD_DESEADA, destino);
	//id = destino;

	//cout << id << endl;
	//char destin[LONGITUD_DESEADA + 1] = "";
	//cadaleatoria(LONGITUD_DESEADA, destin);
	//id = destin;
	//cout << id << endl;
	//char destio[LONGITUD_DESEADA + 1] = "";
	//cadaleatoria(LONGITUD_DESEADA, destio);
	//id = destio;
	//cout << id << endl;




	//ActivosRenta* arbol = new ActivosRenta();

	//arbol->insertar("Hol", "1q0", "", true);
	//arbol->insertar("Mi", "5e", "", false);
	//arbol->insertar("Op", "1b3", "", true);
	//arbol->insertar("Lp", "1a", "", false);
	//arbol->insertar("Qw", "6b", "", false);
	//arbol->insertar("Gf", "1c2", "", true);
	//arbol->insertar("bf", "11d", "", false);
	//arbol->insertar("Mk", "17e", "", true);
	//arbol->insertar("Ml", "15f", "", true);

	//ActivosRenta* arbol2 = new ActivosRenta();

	//arbol2->insertar("a1", "1f0", "", true);
	//arbol2->insertar("a2w", "h5", "", false);
	//arbol2->insertar("a3ddd", "i13", "", true);
	//arbol2->insertar("a4", "1j", "", false);
	//arbol2->insertar("a5", "k6", "", false);
	//arbol2->insertar("a6", "1l2", "", true);
	//arbol2->insertar("a7", "m11", "", false);
	//arbol2->insertar("a8", "1n7", "", true);
	//arbol2->insertar("a9", "15ni", "", true);


	//ActivosRenta* arbol3 = new ActivosRenta();

	//arbol3->insertar("b10", "o10", "", true);
	//arbol3->insertar("El", "55p6", "Unique", true);
	//arbol3->insertar("b12dddd", "1q3", "", true);
	//arbol3->insertar("b13L", "r1", "", false);
	//arbol3->insertar("b14w", "s6", "", false);
	//arbol3->insertar("b15f", "1t2", "", true);
	//arbol3->insertar("b16m", "11u", "", false);
	//arbol3->insertar("b17mio", "1v7", "", true);
	//arbol3->insertar("b18kiki", "w15", "", true);

	//ActivosRenta* arbol4 = new ActivosRenta();


	//arbol4->insertar("c19s", "afsd", "a", true);
	//arbol4->insertar("c20sw", "qwer", "b", false);
	//arbol4->insertar("c21dddd", "oiuo", "c", true);
	//arbol4->insertar("c22L", "Adfc", "d", false);
	//arbol4->insertar("c23w", "mlOPo", "e", false);
	//arbol4->insertar("c24f", "csxxqQ", "f", true);
	//arbol4->insertar("c25m", "cisCooo", "g", false);
	//arbol4->insertar("c26mio", "AklaksdkioIQoi", "h", true);
	//arbol4->insertar("c27kiki", id, "i", true);

	////arbol.graficar();

	//tablero->insertarElemento("Mynor", "Mynor", "fd", arbol, "max", "guatemala");
	//tablero->insertarElemento("susan", "asd", "fd", arbol, "hp", "jutiapa");
	//tablero->insertarElemento("sucel", "asd", "fd", arbol, "hp", "jalapa");
	//tablero->insertarElemento("roxana", "asd", "fd", arbol, "walmart", "jalapa");
	//tablero->insertarElemento("andrea", "Mynor", "fd", arbol2, "walmart", "jalapa");
	//tablero->insertarElemento("sebas", "asd", "fd", arbol3, "walmart", "jalapa");
	//tablero->insertarElemento("andres", "asd", "fd", arbol, "hp", "guatemala");
	//tablero->insertarElemento("willy", "asd", "fd", arbol, "max", "jalapa");
	//tablero->insertarElemento("Mynor", "asd", "fd", arbol4, "walmart", "guatemala");
	//tablero->insertarElemento("Albrto", "alb", "fd", arbol, "max", "guatemala");
	//tablero->insertarElemento("Mario", "alb", "fd", arbol, "hp", "guatemala");
	//tablero->insertarElemento("Alfredo", "asd", "fd", arbol, "max", "jutiapa");
	//tablero->insertarElemento("Diego", "asd", "fd", arbol, "polo", "peten");


	////tablero->activosDisponibles();



	//NodoTablero* prueba = new NodoTablero("", new DatosEmpleado("MEFM", "asdf", "Estui", arbol, "ss", "qq"));

	//cout << endl << "Transacciones" << endl;
	//transacciones->insertar("asfadsfasdf", "9", "1a ", prueba, "sdfsdf", "sdfsdf", true);
	//transacciones->insertar("arrancala234", "9", "1a ", prueba, "sdfsdf", "sdfsdf", true);
	//transacciones->insertar("fasf332123", "9", "1a ", prueba, "sdfsdf", "sdfsdf", false);
	//transacciones->insertar("afasdf232", "1", "2d", new NodoTablero("", new DatosEmpleado("", "", "All Migth", arbol, "", "")), "", "", false);
	//transacciones->insertar("as234asdf", "3", "3e", new NodoTablero("", new DatosEmpleado("", "", "Deju", arbol, "", "")), "", "", true);
	//transacciones->insertar("asfadsA3df", "5", "4f", new NodoTablero("", new DatosEmpleado("", "", "Mario", arbol, "", "")), "", "");
	//transacciones->insertar("asfadsfasd354f", "10", "5c", new NodoTablero("", new DatosEmpleado("", "", "Ascari", arbol, "", "")), "", "", true);


	//transacciones->graficar();
	//transacciones->graficarAlReves();

	//logIn();

	//NodoActivo* pr = arbol3->buscarActivo(556);

	//if (tablero->reservarActivo(556) != 0) {
	//	cout << "ss" << endl;
	//	tablero->reservarActivo(556)->disponibilidad = false;
	//}
	//else {
	//	cout << "sorry" << endl;
	//}

	//tablero->reporteEmpresa("walmart");




	cout << endl << endl << "Estos metodos son lso que estan implementados ya en mi proyecto" << endl;
	cout << "Por eso es diferente a los metodos de la tarea." << endl;
	//arbol.reservados();



}

