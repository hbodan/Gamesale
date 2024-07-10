#include "datos.h"
#include <iostream>
#include <windows.h>
using namespace std;

// VERIFICADO POR QA 

#define ANSI_COLOR_ROJO     "\x1b[38;5;1m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_AZUL     "\x1b[38;5;4m"
#define ANSI_COLOR_VERDE     "\x1b[38;5;2m"

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