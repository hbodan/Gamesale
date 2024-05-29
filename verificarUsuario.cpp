#include <iostream>
#include "datos.h"
using namespace std;

void verificarUsuario(Usuario &user)
{
    cout << "SISTEMA DE RAPIJUEGOS\n";

    // Bucle para verificar el código de usuario
    do
    {
        cout << "Ingrese su código de usuario. (Máximo 5 caracteres)";
        cin >> user.codigo;

        if (user.codigo != "12345")
        {
            cout << "El código que ha digitado es incorrecto. Inténtenlo de nuevo.\n";
        }
    } while (user.codigo != "12345");

    // Bucle para verificar el usuario y la contraseña
    do
    {
        cout << "Ingrese su usuario: ";
        cin >> user.usuario;
        cout << "Ingrese su contraseña: ";
        cin >> user.contrasenia;

        // Verificar credenciales
        if (user.usuario == "admin" && user.contrasenia == "rapijuegos123")
        {
            cout << "¡Bienvenido!\n";
        }
        else
        {
            cout << "Las credenciales que ha digitado son incorrectas. Inténtenlo de nuevo.\n";
        }

    } while (user.usuario != "admin" || user.contrasenia != "rapijuegos123");
}
