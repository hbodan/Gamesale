#include <iostream>
#include "datos.h"
using namespace std;

void agregarVenta(Venta &sale, Acciones &action)
{
    if (action.accion1 == 5)
    {
        int cantidadJuegos;
        cout << "Ingrese el código de venta.\n";
        cin >> sale.codigo;
        cout << "Ingrese la cantidad de juegos vendida.\n";
        cin >> cantidadJuegos;
        cin.ignore();

        for (int i = 0; i < cantidadJuegos; ++i)
        {
            cout << "Ingrese los detalles para el juego " << i + 1 << ":\n";
            cout << "Digite el código del juego. (Máximo 12 caracteres)\n";
            cin.getline(sale.juegos[i].codigo, 12);

            cout << "Digite el nombre del juego. (Máximo 20 caracteres)\n";
            cin.getline(sale.juegos[i].nombre, 50);

            cout << "Digite el código del género del juego. (Máximo 3 caracteres)\n";
            cin.getline(sale.juegos[i].genero.codigo, 4);

            cout << "Digite el nombre del género del juego. (Máximo 30 caracteres)\n";
            cin.getline(sale.juegos[i].genero.nombre, 30);

            cout << "Digite el precio del juego.\n";
            cin >> sale.juegos[i].precio;

            cout << "Digite el stock del juego.\n";
            cin >> sale.juegos[i].stock;

            cin.ignore();
        }

        cout << "Ingrese la fecha de venta en formato MM/DD/AAA.\n";
        cin >> sale.fechaVenta.dia >> sale.fechaVenta.mes >> sale.fechaVenta.anio;

        cout << "Ingrese el nombre del empleado que realizó la venta. (Máximo 20 caracteres)\n";
        cin.getline(sale.empleado.nombre, 20);

        cout << "Su venta ha sido registrada.";
    }
}