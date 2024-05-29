#include <iostream>
#include "datos.h"
using namespace std;

void recopilarDatos(Acciones &action)
{
    do
    {
        cout << "Seleccione la opción que quiere utilizar.\n";
        cout << "1. Agregar usuario.\n";
        cout << "2. Editar usuario.\n";
        cout << "3. Agregar juego.\n";
        cout << "4. Editar juego.\n";
        cout << "5. Agregar venta.\n";
        cin >> action.accion1;

        if (action.accion1 > 5 || action.accion1 < 1)
        {
            cout << "Por favor, elija una opción correcta.";
        }
    } while (action.accion1 > 5 || action.accion1 < 1);
}
