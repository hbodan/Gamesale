#include <iostream>
#include "datos.h"
using namespace std;

void editarJuego(Juego &game, Acciones &action)
{
    if (action.accion1 == 4)
    {
        cout << "1. Editar código del juego.\n";
        cout << "2. Editar nombre juego.\n";
        cout << "3. Editar género del juego.\n";
        cout << "4. Editar precio del juego\n";
        cout << "5. Editar stock del juego\n";
        cin >> action.accion3;

        if (action.accion3 == 1)
        {
            cout << "Digite el nuevo código del juego.\n";
            cin >> game.codigo;
            cout << "El código del juego ha sido actualizado.";
        }

        else if (action.accion3 == 2)
        {
            cout << "Digite el nuevo nombre del juego. (Máximo 20 caracteres)\n";
            cin >> game.nombre;
            cout << "El nombre del juego ha sido actualizado.";
        }

        else if (action.accion3 == 3)
        {
            cout << "Digite el nuevo género del juego. (Máximo 30 caracteres)\n";
            cin >> game.genero.nombre;
            cout << "El género del juego ha sido actualizado.";
        }

        else if (action.accion3 == 4)
        {
            cout << "Digite el nuevo precio del juego.\n";
            cin >> game.precio;
            cout << "El precio del juego sido actualizado.";
        }

        else if (action.accion3 == 5)
        {
            cout << "Ingrese el nuevo stock del juego.\n";
            cin >> game.stock;
            cout << "El stock del juego ha sido actualizado.";
        }
    }
}