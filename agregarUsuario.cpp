#include <iostream>
#include "datos.h"
using namespace std;

void agregarUsuario(Usuario &user, Acciones &action)
{
    if (action.accion1 == 1)
    {
        int cantidadUsuarios;
        cout << "Digite la cantidad de usuarios a agregar.\n";
        cin >> cantidadUsuarios;

        for (int i = 0; i < cantidadUsuarios; ++i)
        {
            cout << "Ingrese la información del usuario " << i + 1 << ":\n";
            cout << "Para crear un usuario, rellene los siguientes campos.\n";
            cout << "Digite el nuevo código del usuario. (Máximo 5 caracteres)\n";
            cin >> user.codigo;
            cout << "Ingrese el nombre del usuario.";
            cin >> user.nombre;
            cout << "Ingrese un ID de usuario. (Máximo 15 caracteres)\n";
            cin >> user.usuario;
            cout << "Ingrese una contraseña. (Máximo 20 caracteres)\n";
            cin >> user.contrasenia;
            cout << "¡Su usuario ha sido creado con éxito!";
        }
    }
}