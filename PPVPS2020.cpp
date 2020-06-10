// PPVPS2020.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "ActivoRenta.h"
#include "Tablero.h"

using namespace std;

Tablero* tablero = new Tablero();
AVL rentas;

void Mostrar(int& d, int FE)
{
	cout << d << endl;
}

//Area general
void logIn(string, string);
/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/

//Esto es para el area de administrador
void registrarUsuario();
void registrarInmueble();
void reportesMatriz();
void transaccion();
/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/

//Esto es para El usuario
void agregarA(AVL);
void eliminarActivo(AVL);
void modificarActivo(AVL);
void rentarActivo(AVL);





/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/
void menuAdministrador() {
	int opcion = 0;
	bool validador = true;

	while (validador) {
		//
		cout << "----------------Bienvenido al sistema de rentas----------------" << endl;
		cout << "-----------------------------Menu------------------------------" << endl;
		cout << "1. Registrar usuario" << endl;
		cout << "2. Reporte Matriz" << endl;
		cout << "3. Reportes de un departamento" << endl;
		cout << "4. Reportes de una empresa" << endl;
		cout << "5. Reporte transacciones" << endl;
		cout << "6. Activos de un usuario" << endl;
		cout << "7. Activos rentados por un usuario" << endl;
		cout << "8. Ordenar transacciones" << endl;

		cout << "Ingrese una opcion" << endl;
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			registrarUsuario();
			break;
		case 2:
			break;
		case 3:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
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

	tablero->insertarElemento(userName, contrasea, nombreCompleto, AVL(), departamento, empresa);
}

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

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:
			//Hacer recorrido de activos rentados
			break;
		case 6:
			//Hacer recorrido de mis activos rentados(por usuario)
			break;
		case 7:
			//Salir a Log in
			break;
		default:
			break;
		}
	}



}

int main()
{
	string palabra1 = "allain";
	string palabra2 = "allaan";

	if (palabra1 < palabra2) {
		cout << "Correcto" << endl;
	}
	else {
		cout << "Hm" << endl;
	}

	AVL arbol;

	arbol.insertar("Hol", 10, "", true);
	arbol.insertar("Mi", 5, "", false);
	arbol.insertar("Op", 13, "", true);
	arbol.insertar("Lp", 1, "", false);
	arbol.insertar("Qw", 6, "", false);
	arbol.insertar("Gf", 12, "", true);
	arbol.insertar("bf", 11, "", false);
	arbol.insertar("Mk", 17, "", true);
	arbol.insertar("Ml", 15, "", true);

	//arbol.InOrden(Mostrar);

	arbol.recor();

	Tablero* tablero = new Tablero();

	tablero->insertarElemento("Mynor", "Mynor", "fd", arbol, "Guate", "max");
	tablero->insertarElemento("Diana", "asd", "fd", arbol, "Jalapa", "Qla");
	tablero->insertarElemento("Estuardo", "asd", "fd", arbol, "Jutipa", "PFA");
	tablero->insertarElemento("Paola", "asd", "fd", arbol, "Solola", "UPS");

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
