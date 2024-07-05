#include "datos.h"
#include <iostream>
#include <cstring>
using namespace std;

void agregarUsuarios(Usuario u[5], int i)
{
    cout << "Ingrese el código del usuario: " << endl;
    cin >> u[i].codigo;
    cin.ignore();
    cout << "Ingrese el nombre del empleado: " << endl;
    cin.getline(u[i].nombre, sizeof(u[i].nombre));
    cout << "Ingrese un nombre de usuario: " << endl;
    cin >> u[i].usuario;
    cout << "Ingrese una contraseña: " << endl;
    cin >> u[i].contrasenia;
    cout << "Ingrese la cantidad juegos vendida: " << endl;
    cin >> u[i].juegosVendidos;
}

void guardarUsuarios(Usuario u[5])
{
    char opcion;
    cout << "Está seguro que desea guardar los cambios permanentemente (S/N)?: " << endl;
    cin >> opcion;

    if (opcion == 'S' || opcion == 's')
    {
        FILE *archi;
        archi = fopen("usuarios.dat", "a");

        for (int i = 0; i < 5; i++)
        {
            fprintf(archi, "%s\n", u[i].codigo);
            fprintf(archi, "%s\n", u[i].nombre);
            fprintf(archi, "%s\n", u[i].usuario);
            fprintf(archi, "%s\n", u[i].contrasenia);
            fprintf(archi, "%d\n", u[i].juegosVendidos);
        }
        fclose(archi);
        printf("Los datos se han guardado exitosamente...\n");
    }
    system("pause");
}

void cargarUsuarios(Usuario u[5])
{
    FILE *archi;
    archi = fopen("usuarios.dat", "r");

    if (archi == NULL)
    {
        perror("Error al abrir el archivo usuarios.dat");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        fscanf(archi, "%s\n", u[i].codigo);
        fgets(u[i].nombre, 20, archi);
        fscanf(archi, "%s\n", u[i].usuario);
        fscanf(archi, "%s\n", u[i].contrasenia);
        fscanf(archi, "%d\n", &u[i].juegosVendidos);
    }
    fclose(archi);
}

void mostrarUsuarios(Usuario u)
{
    printf("Código del empleado: %s\n", u.codigo);
    printf("Nombre: %s", u.nombre);
    printf("Usuario: %s", u.usuario);
    printf("Contraseña: %s\n", u.contrasenia);
    printf("Cantidad de juegos vendidos: %d\n\n", u.juegosVendidos);
}

Usuario *buscarUsuario(Usuario u[5], const char *codigo)
{
    Usuario *usr = NULL;
    for (int i = 0; i < 5; i++)
    {
        if ((u[i].estado == 1 || u[i].estado == 2) && strcmp(u[i].codigo, codigo) == 0)
        {
            usr = &(u[i]);
            break;
        }
    }
    return usr;
}

void eliminarUsuario(Usuario u[5], const char *codigo)
{
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

void actualizarUsuario(Usuario u[5], int i)
{
    cout << "Ingrese el nuevo código de usuario: " << endl;
    cin >> u[i].codigo;
    cin.ignore();
    cout << "Ingrese el nuevo nombre del empleado: " << endl;
    cin.getline(u[i].nombre, sizeof(u[i].nombre));
    cout << "Ingrese el nuevo nombre de usuario: " << endl;
    cin >> u[i].usuario;
    cout << "Ingrese la nueva contraseña: " << endl;
    cin >> u[i].contrasenia;
    cout << "Ingrese la nueva cantidad juegos vendida: " << endl;
    cin >> u[i].juegosVendidos;
    cout << "Los datos han sido editados exitosamente." << endl;
    u[i].estado = 2;
}

void modificarUsuario(Usuario u[5], const char *codigo)
{
    Usuario *usuarioModificar = buscarUsuario(u, codigo);

    if (usuarioModificar != NULL)
    {
        cout << "El usuario está registrado en el sistema. Proceda a editar los datos: " << endl;
        actualizarUsuario(u, usuarioModificar - u);

        cout << "Usuario editado exitosamente." << endl;
    }
    else
    {
        cout << "No se encontró el usuario con el código especificado." << endl;
    }
}

void registrarUsuario(Usuario u[5], const char *codigo)
{
    Usuario *usuarioRegistrar = buscarUsuario(u, codigo);

    if (usuarioRegistrar != NULL)
    {
        cout << "El usuario ya está registrado en el sistema." << endl;
    }
    else
    {
        for (int i = 0; i < 1; i++)
        {
            if (u[i].estado == 0)
            {
                agregarUsuarios(u, i);
                cout << "Usuario agregado existosamente." << endl;
                return;
            }
        }
        cout << "No hay espacio para agregar más usuarios." << endl;
    }
}
