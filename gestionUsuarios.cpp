#include "datos.h"
#include <iostream>
#include <cstring>
#include <windows.h>
using namespace std;

void agregarUsuarios(Usuario* u, int i)
{
    cout << "Ingrese nuevamente el código del usuario: " << endl;
    cin.getline(u[i].codigo, 5);
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
    cout << "-------------------------------------------------------------------";
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
        printf("Los datos se han guardado exitosamente...\n");
        if((archi=fopen("usuarios.dat","r"))!=NULL){
            fclose(archi);
            remove("usuarios.dat");
        }    
        rename("usuariosTemporal.dat","usuarios.dat");
        printf("Los datos se han guardado exitosamente...\n");
    }
    system("pause");
}


void cargarUsuarios(Usuario* u)
{
    FILE *archi;
    archi = fopen("usuarios.dat", "r"); // Abrir en modo lectura

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
    for(int i =0; i<10; i++){
        if(u[i].estado == 1 || u[i].estado == 2){
            printf("----------------------------------------------\n");
            printf("Código del empleado: %s\n", u[i].codigo);
            printf("Nombre: %s\n", u[i].nombre);
            printf("Usuario: %s\n", u[i].usuario);
            printf("Contraseña: %s\n", u[i].contrasenia);
        }
    }
    printf("----------------------------------------------\n");
}

Usuario *buscarUsuario(Usuario u[10], const char *codigo)
{
    Usuario *usr = NULL;
    for (int i = 0; i < 10; i++)
    {
        if ((u[i].estado == 1 || u[i].estado == 2) && strcmp(u[i].codigo, codigo) == 0)
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
        usuarioEliminar->estado = 0;
        cout << "Usuario eliminado exitosamente." << endl;
    }
    else
    {
        cout << "No se encontró el usuario con el código especificado." << endl;
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
    cout << "Los datos han sido editados exitosamente." << endl;
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
        cout << "El usuario está registrado en el sistema. Proceda a editar los datos: " << endl;

        for(int i = 0; i<10; i++){
            if(u[i].estado!=0){
                if(strcmp(u[i].codigo, codigo)==0){
                    actualizarUsuario(u,i);
                    break;
                 }
            }
            
        }
        cout << "Usuario editado exitosamente." << endl;
    }
    else
    {
        cout << "No se encontró el usuario con el código especificado." << endl;
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
        cout << "El usuario ya está registrado en el sistema." << endl;
    }
    else
    {
        bool espacioDisponible = false;
        for (int i = 0; i < 10; i++)
        {
            if (u[i].estado == 0)
            {
                agregarUsuarios(u, i);
                cout << "Usuario registrado exitosamente." << endl;
                espacioDisponible = true;
                break;
            }
        }

        if (!espacioDisponible)
        {
            cout << "No hay espacio para agregar más usuarios." << endl;
        }
    }
}
