#include <iostream>
#include "datos.h"
using namespace std;

void editarUsuario(Usuario &user, Acciones &action)
{
    if (action.accion1 == 2)
    {
        cout << "1. Editar código de usuario.\n";
        cout << "2. Editar nombre del usuario.\n";
        cout << "3. Editar ID del usuario\n";
        cout << "4. Editar contraseña\n";
        cout << "5. Editar número de ventas del usuario\n";
        cin >> action.accion2;

        if (action.accion2 == 1)
        {
            cout << "Digite el nuevo código del usuario. (Máximo 5 caracteres)\n";
            cin >> user.codigo;
            cout << "El código del usuario ha sido actualizado.";
        }

        else if (action.accion2 == 2)
        {
            cout << "Digite el nuevo nombre de usuario. (Máximo 20 caracteres)\n";
            cin >> user.nombre;
            cout << "El nombre de usuario ha sido actualizado.";
        }

        else if (action.accion2 == 3)
        {
            cout << "Digite el nuevo ID de usuario.\n";
            cin >> user.usuario;
            cout << "El ID del usuario ha sido actualizado.";
        }

        else if (action.accion2 == 4)
        {
            cout << "Digite su nueva contraseña.\n";
            cin >> user.contrasenia;
            cout << "La contraseña del usuario ha sido actualizada.";
        }

        else if (action.accion2 == 5)
        {
            cout << "Ingrese el nuevo número de ventas del usuario.\n";
            cin >> user.ventas;
            cout << "El número de ventas del usuario ha sido actualizado.";
        }
    }
}