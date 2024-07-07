#include "datos.h"
#include <iostream>
#include <windows.h>
using namespace std;

void agregarProductos(Juego j[100], int i)
{
    cout << "Ingrese el código del juego: " << endl;
    cin >> j[i].codigo;
    cin.ignore();

    cout << "Ingrese el nombre del juego: " << endl;
    cin.getline(j[i].nombre, 50);

    cout << "Ingrese el código del género: " << endl;
    cin >> j[i].genero.codigo;
    cin.ignore();

    cout << "Ingrese el nombre del género: " << endl;
    cin.getline(j[i].genero.nombre, 30);

    cout << "Ingrese la descripción del género: " << endl;
    cin.getline(j[i].genero.descripcion, 100);

    cout << "Ingrese el precio del juego: " << endl;
    cin >> j[i].precio;

    cout << "Ingrese el stock del juego: " << endl;
    cin >> j[i].stock;
    cin.ignore();
}

void guardarProductos(Juego j[100])
{
    char opcion;
    cout << "Está seguro que desea guardar los cambios permanentemente (S/N)?: " << endl;
    cin >> opcion;

    if (opcion == 'S' || opcion == 's')
    {
        FILE *archi;
        archi = fopen("productos.dat", "a");

        if (archi == NULL)
        {
            perror("Error al abrir el archivo productos.dat");
            return;
        }

        for (int i = 0; i < 100; i++)
        {
            fprintf(archi, "%s\n", j[i].codigo);
            fprintf(archi, "%s\n", j[i].nombre);
            fprintf(archi, "%s\n", j[i].genero.codigo);
            fprintf(archi, "%s\n", j[i].genero.nombre);
            fprintf(archi, "%s\n", j[i].genero.descripcion);
            fprintf(archi, "%lf\n", j[i].precio);
            fprintf(archi, "%d\n", j[i].stock);
        }
        fclose(archi);
        printf("Los datos se han guardado exitosamente...\n");
    }
    system("pause");
}

void cargarProductos(Juego j[100])
{
    FILE *archi;
    archi = fopen("productos.dat", "r");

    for (int i = 0; i < 100; i++)
    {
        fscanf(archi, "%s\n", j[i].codigo);
        cin.ignore();
        fgets(j[i].nombre, 50, archi);
        fscanf(archi, "%s\n", j[i].genero.codigo);
        cin.ignore();
        fgets(j[i].genero.nombre, 30, archi);
        fgets(j[i].genero.descripcion, 100, archi);
        fscanf(archi, "%lf\n", &j[i].precio);
        fscanf(archi, "%d\n", &j[i].stock);
    }
    fclose(archi);
}

void mostrarProductos(Juego j)
{
    printf("Código del juego: %s\n", j.codigo);
    printf("Nombre del juego: %s\n", j.nombre);
    printf("Código del género: %s\n", j.genero.codigo);
    printf("Nombre del género: %s\n", j.genero.nombre);
    printf("Descripción del género: %s\n", j.genero.descripcion);
    printf("Precio del juego: %.2lf\n", j.precio);
    printf("Stock del juego: %.2lf\n", j.precio);
}

Juego *buscarProducto(Juego j[100], const char *codigo)
{
    Juego *pdo = NULL;
    for (int i = 0; i < 5; i++)
    {
        if ((j[i].estado == 1 || j[i].estado == 2) && strcmp(j[i].codigo, codigo) == 0)
        {
            pdo = &(j[i]);
            break;
        }
    }
    return pdo;
}

void eliminarProducto(Juego j[100], const char *codigo)
{
    Juego *productoEliminar = buscarProducto(j, codigo);

    if (productoEliminar != NULL)
    {
        productoEliminar->estado = 0;
        cout << "Producto eliminado exitosamente." << endl;
    }
    else
    {
        cout << "No se encontró el producto con el código especificado." << endl;
    }
}

void actualizarProducto(Juego j[100], int i)
{
    cout << "Ingrese el código del juego: " << endl;
    cin >> j[i].codigo;
    cin.ignore();
    cout << "Ingrese el nombre del juego: " << endl;
    cin.getline(j[i].nombre, 50);
    cout << "Ingrese el código del género: " << endl;
    cin >> j[i].genero.codigo;
    cin.ignore();
    cout << "Ingrese el nombre del género: " << endl;
    cin.getline(j[i].genero.nombre, 30);
    cout << "Ingrese la descripción del género: " << endl;
    cin.getline(j[i].genero.descripcion, 100);
    cout << "Ingrese el precio del juego: " << endl;
    cin >> j[i].precio;
    cout << "Ingrese el stock del juego: " << endl;
    cin >> j[i].stock;
    cin.ignore();
    j[i].estado = 2;
}

void modificarProducto(Juego j[100], const char *codigo)
{
    Juego *productoModificar = buscarProducto(j, codigo);

    if (productoModificar != NULL)
    {
        cout << "El producto está registrado en el sistema. Proceda a editar los datos: " << endl;
        actualizarProducto(j, productoModificar - j);

        cout << "Producto editado exitosamente." << endl;
    }
    else
    {
        cout << "No se encontró producto con el código especificado." << endl;
    }
}

void registrarProducto(Juego j[100], const char *codigo)
{
    Juego *productoRegistrar = buscarProducto(j, codigo);

    if (productoRegistrar != NULL)
    {
        cout << "El producto ya está registrado en el sistema." << endl;
    }
    else
    {
        for (int i = 0; i < 1; i++)
        {
            if (j[i].estado == 0)
            {
                agregarProductos(j, i);
                cout << "Producto agregado existosamente." << endl;
                return;
            }
        }
        cout << "No hay espacio para agregar más productos." << endl;
    }
}
