#include "datos.h"
#include <iostream>
#include <cstring>
using namespace std;

void agregarVentas(Ventas v[5], int i)
{
    cout << "Ingrese el código de la venta: " << endl;
    cin >> v[i].codigo;
    cin.ignore();
    cout << "¿Cuántos juegos se están comprando? " << endl;
    cin >> v[i].cantidadJuegos;
    v[i].cantidadJuegos = min(v[i].cantidadJuegos, 15);
    for (int j = 0; j < v[i].cantidadJuegos; j++)
    {
        cout << "Ingrese el código del juego: " << j + 1 << endl;
        cin >> v[i].codigosJuegos[j];
        cin.ignore();
    }
    cout << "Ingrese el dia de la venta: " << endl;
    cin >> v[i].fechaVenta.dia;
    cout << "Ingrese el mes de la venta: " << endl;
    cin >> v[i].fechaVenta.mes;
    cout << "Ingrese el año de la venta: " << endl;
    cin >> v[i].fechaVenta.anio;
    cin.ignore();
    cout << "Ingrese el nombre del empleado: " << endl;
    cin.getline(v[i].empleado.nombre, sizeof(v[i].empleado.nombre));
    cout << "Ingrese el porcentaje de descuento: " << endl;
    cin >> v[i].porcentajeDescuento;
    cout << "Ingrese el total sin aplicar descuento: " << endl;
    cin >> v[i].totalSinDescuento;
    cout << "Ingrese el total con el descuento aplicado: " << endl;
    cin >> v[i].totalConDescuento;
}

void guardarVentas(Ventas v[5])
{
    char opcion;
    cout << "Está seguro que desea guardar los cambios permanentemente (S/N)?: " << endl;
    cin >> opcion;

    if (opcion == 'S' || opcion == 's')
    {
        FILE *archi;
        archi = fopen("ventas.dat", "a");

        for (int i = 0; i < 5; i++)
        {
            fprintf(archi, "%s\n", v[i].codigo);
            fprintf(archi, "%d\n", v[i].cantidadJuegos);
            for (int j = 0; j < v[i].cantidadJuegos; j++)
            {
                fprintf(archi, "%s\n", v[i].codigosJuegos[j]);
            }
            fprintf(archi, "%d\n", v[i].fechaVenta.dia);
            fprintf(archi, "%d\n", v[i].fechaVenta.mes);
            fprintf(archi, "%d\n", v[i].fechaVenta.anio);
            fprintf(archi, "%s\n", v[i].empleado.nombre);
            fprintf(archi, "%lf\n", v[i].porcentajeDescuento);
            fprintf(archi, "%lf\n", v[i].totalSinDescuento);
            fprintf(archi, "%lf\n", v[i].totalConDescuento);
        }
        fclose(archi);
        printf("Los datos se han guardado exitosamente...\n");
    }
    system("pause");
}

void cargarVentas(Ventas v[5])
{
    FILE *archi;
    archi = fopen("ventas.dat", "r");

    if (archi == NULL)
    {
        perror("Error al abrir el archivo ventas.dat");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        fscanf(archi, "%s\n", v[i].codigo);
        fscanf(archi, "%d\n", &v[i].cantidadJuegos);
        for (int j = 0; j < v[i].cantidadJuegos; j++)
        {
            fscanf(archi, "%s", v[i].codigosJuegos[j]);
        }
        fscanf(archi, "%d\n", &v[i].fechaVenta.dia);
        fscanf(archi, "%d\n", &v[i].fechaVenta.mes);
        fscanf(archi, "%d\n", &v[i].fechaVenta.anio);
        fgets(v[i].empleado.nombre, 20, archi);
        fscanf(archi, "%lf\n", &v[i].porcentajeDescuento);
        fscanf(archi, "%lf\n", &v[i].totalSinDescuento);
        fscanf(archi, "%lf\n", &v[i].totalConDescuento);
    }
    fclose(archi);
}

void mostrarVentas(Ventas v)
{
    printf("Fecha de la venta: %d/%d/%d\n", v.fechaVenta.dia, v.fechaVenta.mes, v.fechaVenta.anio);
    printf("Código de la venta: %s\n", v.codigo);
    printf("Nombre del empleado: %s", v.empleado.nombre);
    printf("Cantidad de juegos comprados: %d\n", v.cantidadJuegos);
    printf("Códigos de los juegos:\n");
    for (int j = 0; j < v.cantidadJuegos; j++)
    {
        printf("  %d: %s\n", j + 1, v.codigosJuegos[j]);
    }
    printf("Descuento: %.2lf\n", v.porcentajeDescuento);
    printf("Total sin descuento: %.2lf\n", v.totalSinDescuento);
    printf("Total con descuento: %.2lf\n\n", v.totalConDescuento);
}

Ventas *buscarVenta(Ventas v[5], const char *codigo)
{
    Ventas *vnt = NULL;
    for (int i = 0; i < 5; i++)
    {
        if ((v[i].estado == 1 || v[i].estado == 2) && strcmp(v[i].codigo, codigo) == 0)
        {
            vnt = &(v[i]);
            break;
        }
    }
    return vnt;
}

void eliminarVenta(Ventas v[5], const char *codigo)
{
    Ventas *ventaEliminar = buscarVenta(v, codigo);

    if (ventaEliminar != NULL)
    {
        ventaEliminar->estado = 0;
        cout << "Venta eliminada exitosamente." << endl;
    }
    else
    {
        cout << "No se encontró la venta con el código especificado." << endl;
    }
}

void actualizarVenta(Ventas v[5], int i)
{
    cout << "Ingrese el nuevo código de la venta: " << endl;
    cin >> v[i].codigo;
    cin.ignore();
    cout << "¿Cuántos juegos se están comprando? " << endl;
    cin >> v[i].cantidadJuegos;
    v[i].cantidadJuegos = min(v[i].cantidadJuegos, 15);
    for (int j = 0; j < v[i].cantidadJuegos; j++)
    {
        cout << "Ingrese el código del juego: " << j + 1 << endl;
        cin >> v[i].codigosJuegos[j];
        cin.ignore();
    }
    cout << "Ingrese el nuevo dia de la venta: " << endl;
    cin >> v[i].fechaVenta.dia;
    cout << "Ingrese el nuevo mes de la venta: " << endl;
    cin >> v[i].fechaVenta.mes;
    cout << "Ingrese el nuevo año de la venta: " << endl;
    cin >> v[i].fechaVenta.anio;
    cin.ignore();
    cout << "Ingrese el nuevo nombre del empleado: " << endl;
    cin.getline(v[i].empleado.nombre, sizeof(v[i].empleado.nombre));
    cout << "Ingrese el porcentaje de descuento: " << endl;
    cin >> v[i].porcentajeDescuento;
    cout << "Ingrese el nuevo total sin aplicar descuento: " << endl;
    cin >> v[i].totalSinDescuento;
    cout << "Ingrese el nuevo total con el descuento aplicado: " << endl;
    cin >> v[i].totalConDescuento;
    v[i].estado = 2;
}

void modificarVenta(Ventas v[5], const char *codigo)
{
    Ventas *ventaModificar = buscarVenta(v, codigo);

    if (ventaModificar != NULL)
    {
        cout << "El usuario está registrado en el sistema. Proceda a editar los datos: " << endl;
        actualizarVenta(v, ventaModificar - v);

        cout << "Venta editada exitosamente." << endl;
    }
    else
    {
        cout << "No se encontró la venta con el código especificado." << endl;
    }
}

void registrarVenta(Ventas v[5], const char *codigo)
{
    Ventas *ventaRegistrar = buscarVenta(v, codigo);

    if (ventaRegistrar != NULL)
    {
        cout << "La venta ya está registrada en el sistema." << endl;
    }
    else
    {
        for (int i = 0; i < 1; i++)
        {
            if (v[i].estado == 0)
            {
                agregarVentas(v, i);
                cout << "Venta agregada existosamente." << endl;
                return;
            }
        }
        cout << "No hay espacio para agregar más ventas." << endl;
    }
}