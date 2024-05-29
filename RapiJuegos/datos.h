#include <iostream>
#include <string>
using namespace std;

struct Usuario
{
    std::string codigo;
    char nombre[20];
    std::string usuario;
    std::string contrasenia;
    int ventas;
};

struct Genero
{
    char codigo[3];
    char nombre[30];
    char descripcion[100];
};

struct Juego
{
    char codigo[12];
    char nombre[50];
    Genero genero;
    double precio;
    int stock;
};

struct Fecha
{
    int dia;
    int mes;
    int anio;
};

struct Descuento
{
    char nombre[30];
    int identificador;
    int porcentajeDescuento;
    char codigoVideoJuego[12];
    char codigoGenero[3];
    double precio;
    int cantidad;
};

struct Venta
{
    char codigo[10];
    Juego juegos[15];
    Fecha fechaVenta;
    Usuario empleado;
    double descuentoTotal;
    double totalSinDescuento;
    double totalConDescuento;
};

struct Acciones
{
    int accion1;
    int accion2;
    int accion3;
};

// Prototipos de funciones.
void verificarUsuario(Usuario &user);
void recopilarDatos(Acciones &action, Juego &game, Usuario &user, Venta &sale);
void agregarUsuario(Usuario &user, Acciones &action);
void editarUsuario(Usuario &user, Acciones &action);
void agregarJuego(Juego &game, Acciones &action);
void editarJuego(Juego &game, Acciones &action);
void agregarVenta(Venta &sale, Acciones &action);