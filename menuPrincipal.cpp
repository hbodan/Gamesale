#include "datos.h"
#include <iostream>
#include <cstring>
using namespace std;

void registrarUsuario(Usuario* u);
void eliminarUsuario(Usuario* u);
void mostrarUsuarios(Usuario* u);
void modificarUsuario(Usuario* u);
void guardarUsuarios(Usuario* u);

//Recordar tener un usuario ya ingresado en el fichero (Usuario base)
bool iniciarSesion(Usuario* j){
    char codigo[5] = "";
    cout<<"Digite el código del usuario"<<endl;
    cin.getline(codigo, 5);

    for(int i = 0; i<10 ; i++){
        if(j[i].estado != EOF){
            if(strcmp(j[i].codigo, codigo) == 0){
                return true;
            }
        }
    }
    return false;
}

void menuUsuarios(Usuario* u){
    int opcionUsuario = 0;

    do{
        cout<<"*********************************************"<<endl;
        cout<<"Apartado Usuario"<<endl;
        cout<<"*********************************************"<<endl;
        cout<<"1. Agregar Usuario"<<endl;
        cout<<"2. Editar Usuario"<<endl;
        cout<<"3. Eliminar Usuario"<<endl;
        cout<<"4. Mostrar todos los usuarios"<<endl;
        cout<<"5. Guardar cambios realizados en Usuario"<<endl;
        cout<<"0. Regresar..."<<endl;
        cin>>opcionUsuario;

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


void mostrarMenuPrincipal(Juego* p, Ventas* v, Usuario* u){
    int opcionPrincipal = 0;
    do{
        cout<<"Bienvenidos a GameSale"<<endl;
        cout<<"1. Usuarios"<<endl;
        cout<<"2. Juegos"<<endl;
        cout<<"3. Ventas"<<endl;
        cout<<"4. Estadísticas"<<endl;
        cout<<"0. Salir"<<endl;
        cin>>opcionPrincipal;

        switch (opcionPrincipal)
        {
        case 1:
            menuUsuarios(u);
            break;
        case 2:
            cout<<"Juegos"<<endl;
            break;
        case 3:
            cout<<"Ventas"<<endl;
            break;
        case 4:
            cout<<"Estadísticas"<<endl;
            break;
        default:
            cout<<"Cia ciao"<<endl;
            break;
        }
    }while(opcionPrincipal!=0);
}