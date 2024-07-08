#include "datos.h"
#include <iostream>
#include <windows.h>
using namespace std;
void cargarJuegos(Juego* j);
void guardarUsuarios(Usuario u[10]);
void agregarUsuarios(Usuario u[10], int i);
void registrarUsuario(Usuario u[10]);
void mostrarMenuPrincipal(Juego* p, Ventas* v, Usuario* u);
void cargarUsuarios(Usuario* u);
bool iniciarSesion(Usuario* j);
void cargarVentas(Ventas v[5]);
Ventas *buscarVentas(Ventas v[5], const char *codigo);
void imprimirVentas(Ventas v);
void eliminarVenta(Ventas v[5], const char *codigo);
void mostrarVentas(Ventas v);
void cargarVentas(Ventas* v);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Juego j[100];
    Ventas v[100];
    Usuario u[10];
    cargarJuegos(j);
    cargarUsuarios(u);
    cargarVentas(v);
    
    bool bandera = true;

    do{
        if (iniciarSesion(u)) {
            //Si existe el usuario, procedemos a menuPrincipal
            mostrarMenuPrincipal(j,v,u);
        } else {
            //Si no existe, se le preguntará nuevamente (Solo el usuario existente, puede crear nuevos usuarios)
            cout << "Inicio de sesión fallido." <<endl;
        }
    }while(bandera);
}