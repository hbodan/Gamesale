#include "datos.h"
#include <iostream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;

#define ANSI_COLOR_ROJO     "\x1b[38;5;1m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_AZUL     "\x1b[38;5;4m"
#define ANSI_COLOR_VERDE     "\x1b[38;5;2m"

void registrarUsuario(Usuario* u);
void eliminarUsuario(Usuario* u);
void mostrarUsuarios(Usuario* u);
void modificarUsuario(Usuario* u);
void guardarUsuarios(Usuario* u);
void registrarJuego(Juego* j);
void modificarJuego(Juego* j);
void eliminarJuego(Juego* j);
void mostrarJuegos(Juego* j);
void guardarJuegos(Juego* j);
void registrarVenta(Ventas* v, Usuario* usuario, Juego* j);
void mostrarVentas(Ventas* v, Juego* j);
void guardarVentas(Ventas* v, Juego* j);
Usuario *buscarUsuario(Usuario u[10], const char *codigo);
void mostrarMenuPrincipal(Juego* j, Ventas* v, Usuario* u, Usuario* usuario);

bool inicioSesion(Usuario* u){
    char contraseniaIngresada[20] = "";
    system("cls");
    cout << "---------------------------------------" << endl;
    cout << "Hola: "<< u->nombre << endl;
    cout << "---------------------------------------" << endl;
    cout << "---------------------------------------" << endl;
    cout << "|                                     |" << endl;
    cout << "| Por favor, digite la contraseña     |" << endl;
    cout << "| del usuario:                        |" << endl;
    cout << "|                                     |" << endl;
    cout << "---------------------------------------" << endl;
    cout << ">>> ";
    cin.getline(contraseniaIngresada, 20);

    if(strcmp(u->contrasenia, contraseniaIngresada) == 0){
        return true;
    }


    return false;
}

void iniciarSesion(Juego* j, Ventas* v, Usuario* u){

    do{
        char codigo[5] = "";
        system("cls");
        cout << "---------------------------------------" << endl;
        cout << "|        Bienvenido a Gamesale        |" << endl;
        cout << "---------------------------------------" << endl;
        cout << "---------------------------------------" << endl;
        cout << "|                                     |" << endl;
        cout << "| Por favor, digite el código del     |" << endl;
        cout << "| usuario:                            |" << endl;
        cout << "|                                     |" << endl;
        cout << "---------------------------------------" << endl;
        cout << ">>> ";
        cin.getline(codigo, 5);

        Usuario *usuarioIngresado = buscarUsuario(u, codigo);

        if ((usuarioIngresado != NULL) && (usuarioIngresado->estado!=3)) {
            //Si existe el usuario, procedemos a verificar la contraseña
            do{
                if(inicioSesion(usuarioIngresado)){
                    cout <<ANSI_COLOR_VERDE << "Credenciales Válidas! " << ANSI_COLOR_AZUL << "Entrando al sistema";
                    cout.flush();

                    for (int i = 0; i < 5; ++i) {
                        this_thread::sleep_for(chrono::milliseconds(300));
                        cout<<ANSI_COLOR_AZUL << ".";
                        cout.flush();
                    }
                    cout <<ANSI_COLOR_VERDE << " Listo!" << ANSI_COLOR_RESET<<endl;
                    this_thread::sleep_for(chrono::milliseconds(500));
                    mostrarMenuPrincipal(j,v,u,usuarioIngresado);
                }else{
                    cout << ANSI_COLOR_ROJO <<"Contraseña Incorrecta.  " << ANSI_COLOR_AZUL << "Presiona ENTER para intentar de nuevo..." << ANSI_COLOR_RESET<<endl;
                    system("pause");
                }
            }while(true);
            
        } else {
            //Si no existe, se le preguntará nuevamente (Solo el usuario existente, puede crear nuevos usuarios)
            cout << ANSI_COLOR_ROJO <<"Usuario no existente.  " << ANSI_COLOR_AZUL << "Presiona ENTER para intentar de nuevo..." << ANSI_COLOR_RESET<<endl;
            system("pause");
        }
    }while(true);
}


void menuVentas(Juego* j, Ventas* v, Usuario* usuario){
    int opcionVenta = 0;

    do{
        system("cls");
        cout << "----------------------------------------------" << endl;
        cout << "|              Apartado de Ventas            |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "|                                            |" << endl;
        cout << "|  1. Agregar Venta                          |" << endl;
        cout << "|  2. Mostrar todas las ventas               |" << endl;
        cout << "|  3. Guardar cambios realizados en ventas   |" << endl;
        cout << "|  0. Regresar...                            |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << ">>> ";
        cin>>opcionVenta;

        switch (opcionVenta)
        {
        case 1:
            registrarVenta(v, usuario, j);
            break;
        case 2:
            mostrarVentas(v, j);
            break;
        case 3:
            guardarVentas(v, j);
            break;
        default:
        cout<< ANSI_COLOR_VERDE<< "Ciao ciao"<< ANSI_COLOR_RESET<<endl;
            break;
        }
    }while(opcionVenta !=0);
}
void menuJuegos(Juego* j){
    int opcionJuego = 0;

    do{
        system("cls");
        cout << "----------------------------------------------" << endl;
        cout << "|             Apartado de juegos             |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "|                                            |" << endl;
        cout << "|  1. Agregar Juego                          |" << endl;
        cout << "|  2. Editar juego                           |" << endl;
        cout << "|  3. Eliminar juego                         |" << endl;
        cout << "|  4. Mostrar todos los juegos               |" << endl;
        cout << "|  5. Guardar cambios realizados en juegos   |" << endl;
        cout << "|  0. Regresar...                            |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << ">>> ";
        cin>>opcionJuego;

        switch (opcionJuego)
        {
        case 1:
            registrarJuego(j);
            break;
        case 2:
            modificarJuego(j);
            break;
        case 3:
            eliminarJuego(j);
            break;
        case 4:
            mostrarJuegos(j);
            break;
        case 5:
            guardarJuegos(j);
            break;
        default:
            break;
        }
    }while(opcionJuego !=0);
}
void menuUsuarios(Usuario* u){
    int opcionUsuario = 0;

    do{
        system("cls");
        cout << "----------------------------------------------" << endl;
        cout << "|              Apartado Usuario              |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "|                                            |" << endl;
        cout << "|  1. Agregar Usuario                        |" << endl;
        cout << "|  2. Editar Usuario                         |" << endl;
        cout << "|  3. Eliminar Usuario                       |" << endl;
        cout << "|  4. Mostrar todos los usuarios             |" << endl;
        cout << "|  5. Guardar cambios realizados en Usuario  |" << endl;
        cout << "|  0. Regresar...                            |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << ">>> ";
        cin>>opcionUsuario;
        system("cls");

        switch (opcionUsuario)
        {
        case 1:
            registrarUsuario(u);
            break;
        case 2:
            modificarUsuario(u);
            break;
        case 3:
            eliminarUsuario(u);
            break;
        case 4:
            mostrarUsuarios(u);
            break;
        case 5:
            guardarUsuarios(u);
            break;
        default:
            break;
        }
    }while(opcionUsuario !=0);
}


void mostrarMenuPrincipal(Juego* j, Ventas* v, Usuario* u, Usuario* usuario){
    int opcionPrincipal = 0;
    do{
        system("cls");
        cout << "----------------------------------------------" << endl;
        cout << "|               Menu Principal               |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "|                                            |" << endl;
        cout << "|  1. Usuarios                               |" << endl;
        cout << "|  2. Juegos                                 |" << endl;
        cout << "|  3. Ventas                                 |" << endl;
        cout << "|  0. Salir                                  |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << ">>> ";
        cin>>opcionPrincipal;

        switch (opcionPrincipal)
        {
        case 1:
            menuUsuarios(u);
            break;
        case 2:
            menuJuegos(j);
            break;
        case 3:
            menuVentas(j,v,usuario);
            break;
        case 0:
            cout<<ANSI_COLOR_AZUL<<"Cia ciao!!!"<<ANSI_COLOR_RESET<<endl;
            exit(0);
            break;
        default:
            break;
        }
    }while(opcionPrincipal!=0);
}