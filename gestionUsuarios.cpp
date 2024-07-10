#include "datos.h"
#include <iostream>
#include <cstring>
#include <windows.h>
#include <thread>
#include <chrono>
using namespace std;

// VERIFICADO POR QA 

#define ANSI_COLOR_ROJO     "\x1b[38;5;1m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_AZUL     "\x1b[38;5;4m"
#define ANSI_COLOR_VERDE     "\x1b[38;5;2m"

void agregarUsuarios(Usuario* u, int i, const char *codigo)
{
    strcpy(u[i].codigo, codigo);
    cout << "Ingrese el nombre del empleado: " << endl;
    cin.getline(u[i].nombre, 20);
    cout << "Ingrese un nombre de usuario: " << endl;
    cin.getline(u[i].usuario,15);
    cout << "Ingrese una contraseña: " << endl;
    cin.getline(u[i].contrasenia,20);
    u[i].estado = 1;
}

void guardarUsuarios(Usuario* u)
{
    char opcion;
    cout << "-------------------------------------------------------------------"<<endl;
    cout << "Está seguro que desea guardar los cambios permanentemente (S/N)?: ";
    cin>>opcion;
    

    if (opcion == 'S' ||opcion == 's' )
    {
        FILE *temp, *archi;
        temp = fopen("usuariosTemporal.dat", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(temp, "%s\n", u[i].codigo);
            fprintf(temp, "%s\n", u[i].nombre);
            fprintf(temp, "%s\n", u[i].usuario);
            fprintf(temp, "%s\n", u[i].contrasenia);
            fprintf(temp, "%d\n", u[i].estado);
        }
        fclose(temp);


        if((archi=fopen("usuarios.dat","r"))!=NULL){
            fclose(archi);
            remove("usuarios.dat");
        }    
        rename("usuariosTemporal.dat","usuarios.dat");

        cout <<ANSI_COLOR_VERDE << "Datos guardados exitosamente. " <<ANSI_COLOR_AZUL<<"Volviendo al menú" << ANSI_COLOR_RESET;
        cout.flush();

        for (int i = 0; i < 5; ++i) {
            this_thread::sleep_for(chrono::milliseconds(300));
            cout<<ANSI_COLOR_AZUL << ".";
            cout.flush();
        }

        cout <<ANSI_COLOR_AZUL << " Listo!" << ANSI_COLOR_RESET<<endl;
        this_thread::sleep_for(chrono::milliseconds(500));

    }else{
        cout <<ANSI_COLOR_ROJO << "Has cancelado el guardado. " <<ANSI_COLOR_AZUL<<"Volviendo al menú" << ANSI_COLOR_RESET;
        cout.flush();

        for (int i = 0; i < 5; ++i) {
            this_thread::sleep_for(chrono::milliseconds(300));
            cout<<ANSI_COLOR_AZUL << ".";
            cout.flush();
        }

        cout <<ANSI_COLOR_AZUL << " Listo!" << ANSI_COLOR_RESET<<endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
}


void cargarUsuarios(Usuario* u)
{
    FILE *archi;
    archi = fopen("usuarios.dat", "r");

    if (archi == NULL)
    {
        perror("Error al abrir el archivo usuarios.dat. Asignando valores por defecto.");
        for (int i = 0; i < 10; i++)
        {
            u[i].estado = 0; // Marcar como vacío
        }
        return;
    }

    int i = 0;
    while (i < 10 &&
           fscanf(archi, "%5s\n", u[i].codigo) != EOF &&
           fgets(u[i].nombre, sizeof(u[i].nombre), archi) != NULL &&
           fgets(u[i].usuario, sizeof(u[i].usuario), archi) != NULL &&
           fgets(u[i].contrasenia, sizeof(u[i].contrasenia), archi) != NULL &&
           fscanf(archi, "%d\n", &u[i].estado) != EOF)
    {
        u[i].codigo[strcspn(u[i].codigo, "\n")] = '\0';
        u[i].nombre[strcspn(u[i].nombre, "\n")] = '\0';
        u[i].usuario[strcspn(u[i].usuario, "\n")] = '\0';
        u[i].contrasenia[strcspn(u[i].contrasenia, "\n")] = '\0';
        i++;
    }

    // Marcar los espacios restantes como vacíos
    for (; i < 10; i++)
    {
        u[i].estado = 0; // Marcar como vacío
    }

    fclose(archi);
}

void mostrarUsuarios(Usuario* u)
{
    system("cls");
    printf("--------------------------------------------------\n");
    printf("|             REGISTROS DE USUARIOS              |\n");
    printf("--------------------------------------------------\n");
    int contador = 0;
    for(int i =0; i<10; i++){
        if(u[i].estado == 1 || u[i].estado == 2){
            
            printf("--------------------------------------------------\n");
            printf("Código del empleado: %s\n", u[i].codigo);
            printf("Nombre:              %s\n", u[i].nombre);
            printf("Usuario:             %s\n", u[i].usuario);
            printf("Contraseña:          %s\n", u[i].contrasenia);
            printf("--------------------------------------------------\n");
            contador+=1;
        }
    }
    cout << ANSI_COLOR_VERDE << contador <<" Registros mostrados exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
    system("pause");
    system("cls");
}

Usuario *buscarUsuario(Usuario u[10], const char *codigo)
{
    Usuario *usr = NULL;
    for (int i = 0; i < 10; i++)
    {
        if ((u[i].estado == 1 || u[i].estado == 2 || u[i].estado == 3) && strcmp(u[i].codigo, codigo) == 0)
        {
            usr = &(u[i]);
            break;
        }
    }
    return usr;
}

void eliminarUsuario(Usuario* u)
{

    char codigo[5] = "";
    cout<<"Dame el código de usuario"<<endl;
    cin.ignore();
    cin.getline(codigo, 5);

    Usuario *usuarioEliminar = buscarUsuario(u, codigo);

    if (usuarioEliminar != NULL)
    {
        usuarioEliminar->estado = 3;
        cout << ANSI_COLOR_VERDE << "Usuario eliminado exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
        system("pause");
    }
    else
    {
        cout << ANSI_COLOR_ROJO << "No se encontró el usuario con el código especificado. " << ANSI_COLOR_AZUL <<"Presiona ENTER para regresar al menú..."<<ANSI_COLOR_RESET<<endl;
        system("pause");
    }
}

void actualizarUsuario(Usuario* u, int i)
{
    cout << "Ingrese el nuevo nombre del empleado: " << endl;
    cin.getline(u[i].nombre, 20);
    cout << "Ingrese el nuevo nombre de usuario: " << endl;
    cin.getline(u[i].usuario, 15);
    cout << "Ingrese la nueva contraseña: " << endl;
    cin.getline(u[i].contrasenia, 20);
    u[i].estado = 2;
}

void modificarUsuario(Usuario* u)
{
    char codigo[5] = "";
    cout<<"Dame el código de usuario"<<endl;
    cin.ignore();
    cin.getline(codigo, 5);

    Usuario *usuarioModificar = buscarUsuario(u, codigo);

    if (usuarioModificar != NULL)
    {
        cout << ANSI_COLOR_VERDE << "El usuario está registrado en el sistema. "<< ANSI_COLOR_AZUL << "Edita tu usuario..."<<ANSI_COLOR_RESET<<endl;
        cout.flush();

        for(int i = 0; i<10; i++){
            if(u[i].estado!=0){
                if(strcmp(u[i].codigo, codigo)==0){
                    actualizarUsuario(u,i);
                    break;
                 }
            }
            
        }

        cout << ANSI_COLOR_VERDE << "Usuario editado exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
        system("pause");

    }
    else
    {
        cout << ANSI_COLOR_ROJO << "No se encontró el usuario con el código especificado. " << ANSI_COLOR_AZUL <<"Presiona ENTER para regresar al menú..."<<ANSI_COLOR_RESET<<endl;
        cout.flush();
        system("pause");
    }
}

void registrarUsuario(Usuario* u)
{
    char codigo[6]; 
    cout << "Ingrese el código de usuario a registrar: ";
    cin.ignore();
    cin.getline(codigo, sizeof(codigo));

    Usuario *usuarioRegistrar = buscarUsuario(u, codigo);

    if (usuarioRegistrar != NULL)
    {
        cout << ANSI_COLOR_ROJO << "El usuario ya está registrado en el sistema. " << ANSI_COLOR_AZUL <<"Presiona ENTER para regresar al menú..."<<ANSI_COLOR_RESET<<endl;
        system("pause");
    }
    else
    {
        bool espacioDisponible = false;
        for (int i = 0; i < 10; i++)
        {
            if (u[i].estado == 0)
            {
                cout <<ANSI_COLOR_VERDE << "<<<Código Disponible!!! Sigue rellenando los datos...>>>"<< ANSI_COLOR_RESET<<endl;
                agregarUsuarios(u, i, codigo);
                cout << ANSI_COLOR_VERDE << "Usuario registrado exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
                system("pause");
                espacioDisponible = true;
                break;
            }
        }

        if (!espacioDisponible)
        {
            cout << ANSI_COLOR_ROJO << "No hay espacio para agregar a mas usuarios. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
            system("pause");
        }
    }
}
