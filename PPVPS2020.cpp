// PPVPS2020.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "ActivoRenta.h"
#include "Tablero.h"

using namespace std;

int idHistorialActivos;

Tablero* tablero = new Tablero();
ActivosRenta rentas;

void Mostrar(int& d, int FE)
{
	cout << d << endl;
}

//Area general
void logIn();
/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/

//Esto es para el area de administrador
void registrarUsuario();
void activosUser() {};
void rentasCsuario();



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
		cout << "6. Activos de un usuario" << endl;
		cout << "7. Activos rentados por un usuario" << endl;
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
		case 5:
			//Crear metodo para sacar los metodos de cada empresa
						//tablero->graficasEmpresa();
			/*
				Tiene que ser un menu con las posibilidades de generar
				los reportes de todos los usuarios de una empresa
				cagadales
			*/
			break;
		case 6:
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

	tablero->insertarElemento(userName, contrasea, nombreCompleto, ActivosRenta(), departamento, empresa);
}
void rentasCsuario() {
	//Usuario a buscar 
	string userUsuario;
	cin.getline((char*)userUsuario.c_str(), 100, '\n');
	cin.ignore();

	NodoTablero* usuario = tablero->buscarNodo(userUsuario);

	//Llamar a metodo de graficar arbol de usuario

}

/*__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--__--*/

//Esto es para El usuario
void agregarA(ActivosRenta);
void eliminarActivo(ActivosRenta);
void modificarActivo(ActivosRenta);
void rentarActivo(ActivosRenta) {};
void activosRentados() {};
void misActivosRentados(ActivosRenta) {};

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
			rentarActivo(usuario->empleado->getRentas());
			break;
		case 5:
			activosRentados();
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


	modificarActivo(arbol);

	arbol.preOrden();



	//arbol.recor();

	cout << endl << endl << "Estos metodos son lso que estan implementados ya en mi proyecto" << endl;
	cout << "Por eso es diferente a los metodos de la tarea." << endl;
	//arbol.reservados();


	/*
	Tablero* tablero = new Tablero();

	tablero->insertarElemento("Mynor", "Mynor", "fd", arbol, "Guate", "max");
	tablero->insertarElemento("Diana", "asd", "fd", arbol, "Jalapa", "Qla");
	tablero->insertarElemento("Estuardo", "asd", "fd", arbol, "Jutipa", "PFA");
	tablero->insertarElemento("Paola", "asd", "fd", arbol, "Solola", "UPS");
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
