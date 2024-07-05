#include "datos.h"
#include <iostream>
#include <windows.h>
using namespace std;

void cargarVentas(Ventas v[5]);
Ventas *buscarVentas(Ventas v[5], const char *codigo);
void imprimirVentas(Ventas v);
void eliminarVenta(Ventas v[5], const char *codigo);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Ventas v[5];
    char codigo[10];

    cargarVentas(v);

    cout << "Por favor, digite código de venta:" << endl;
    cin >> codigo;

    eliminarVenta(v, codigo);
}