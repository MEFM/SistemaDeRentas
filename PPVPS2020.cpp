// PPVPS2020.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "ActivoRenta.h"
#include "Tablero.h"

using namespace std;
void menu() {
    int opcion = 0;
    bool validador = true;

    while (validador) {
        cout << "----------------Bienvenido al sistema de rentas----------------" << endl;
        cout << "" << endl;

        switch (opcion)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 5:
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

    ActivoRenta arbol;

    arbol.insertar("", "", 10);
    arbol.insertar("", "", 5);
    arbol.insertar("", "", 13);
    arbol.insertar("", "", 1);
    arbol.insertar("", "", 6);
    arbol.insertar("", "", 12);
    arbol.insertar("", "", 11);
    arbol.insertar("", "", 17);
    arbol.insertar("", "", 15);

    arbol.gPreorden();


    Tablero* tablero = new Tablero();

    tablero->insertarElemento("Mynor", "Mynor", "fd", arbol, "Guate", "max");
    tablero->insertarElemento("Diana", "asd", "fd", arbol, "Jalapa", "Qla");
    tablero->insertarElemento("Estuardo", "asd", "fd", arbol, "Jutipa", "PFA");
    tablero->insertarElemento("Paola", "asd", "fd", arbol, "Solola", "UPS");

    tablero->recorrerTablero();
    tablero->graficar();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
