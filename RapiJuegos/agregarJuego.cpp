#include <iostream>
#include "datos.h"
using namespace std;

void agregarJuego(Juego &game, Acciones &action)
{
    if (action.accion1 == 3)
    {
        int cantidadJuegos;
        cout << "Digite la cantidad de juegos a agregar.\n";
        cin >> cantidadJuegos;

        for (int i = 0; i < cantidadJuegos; ++i)
        {
            cout << "Ingrese los detalles para el juego " << i + 1 << ":\n";
            cout << "Para agregar un nuevo juego, rellene los siguientes campos.\n";
            cout << "Digite el código del juego. (Máximo 12 caracteres)\n";
            cin >> game.codigo;
            cout << "Digite el nombre del juego. (Máximo 50 caracteres)\n";
            cin.ignore();
            cin.getline(game.nombre, 50);
            cout << "Digite el género del juego. (Máximo 30 caracteres)\n";
            cin.ignore();
            cin.getline(game.genero.nombre, 30);
            cout << "Digite el precio del juego.\n";
            cin >> game.precio;
            cout << "Digite el stock del juego.\n";
            cin >> game.stock;
            cout << "El nuevo juego ha sido registrado.";
        }
    }
}