#include "datos.h"
#include <iostream>
#include <windows.h>
using namespace std;

void cargarJuegos(Juego* j);
void cargarUsuarios(Usuario* u);
void cargarVentas(Ventas* v);
void iniciarSesion(Juego* j, Ventas* v, Usuario* u);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Juego j[100];
    Ventas v[100];
    Usuario u[10];
    cargarJuegos(j);
    cargarUsuarios(u);
    cargarVentas(v);

    iniciarSesion(j,v,u);
}