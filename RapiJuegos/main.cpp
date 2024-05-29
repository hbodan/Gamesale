#include <iostream>
#include "datos.h"
using namespace std;

void verificarUsuario(Usuario &user);
void recopilarDatos(Acciones &action);
void agregarUsuario(Usuario &user, Acciones &action);
void editarUsuario(Usuario &user, Acciones &action);
void agregarJuego(Juego &game, Acciones &action);
void editarJuego(Juego &game, Acciones &action);
void agregarVenta(Venta &sale, Acciones &action);

int main()
{
    // Declaración de estructuras.
    Usuario user;
    Juego game;
    Venta sale;
    Acciones action;

    // Verificar usuario.
    verificarUsuario(user);

    // Recopilar datos.
    recopilarDatos(action);

    // Agregar usuario.
    agregarUsuario(user, action);

    // Editar usuario.
    editarUsuario(user, action);

    // Agregar juego.
    agregarJuego(game, action);

    // Editar juego.
    editarJuego(game, action);

    // Agregar venta.
    agregarVenta(sale, action);
}
