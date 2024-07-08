#include "datos.h"
#include <iostream>
#include <cstring>
using namespace std;

void leerFechaSistema(Fecha &hoy);

void cargarVentas(Ventas* v) {
    FILE *archi;
    archi = fopen("ventas.dat", "r"); // Abrir en modo lectura

    if (archi == NULL) {
        perror("Error al abrir el archivo ventas.dat. Asignando valores por defecto.");
        for (int i = 0; i < 100; i++) {
            v[i].estado = 0; // Marcar como vacío
        }
        return;
    }

    int i = 0;
    while (i < 100 && fscanf(archi, "%9s\n", v[i].codigo) == 1) {
        if (fscanf(archi, "%d\n", &v[i].cantidadJuegos) != 1) break;

        for (int j = 0; j < v[i].cantidadJuegos; j++) {
            if (fscanf(archi, "%11s\n", v[i].codigosJuegos[j]) != 1) break;
        }

        if (fscanf(archi, "%d\n", &v[i].fechaVenta.dia) != 1) break;
        if (fscanf(archi, "%d\n", &v[i].fechaVenta.mes) != 1) break;
        if (fscanf(archi, "%d\n", &v[i].fechaVenta.anio) != 1) break;

        fgets(v[i].empleado.nombre, sizeof(v[i].empleado.nombre), archi);
        v[i].empleado.nombre[strcspn(v[i].empleado.nombre, "\n")] = '\0';

        if (fscanf(archi, "%d\n", &v[i].estado) != 1) break;

        i++;
    }

    // Marcar los espacios restantes como vacíos
    for (; i < 100; i++) {
        v[i].estado = 0; // Marcar como vacío
    }

    fclose(archi);
}

void agregarVentas(Ventas* v, int i) {
    cout << "Ingrese el código de la venta: ";
    cin.ignore();
    cin.getline(v[i].codigo, sizeof(v[i].codigo));

    cout << "Ingrese la cantidad de juegos que está comprando: ";
    cin >> v[i].cantidadJuegos;
    v[i].cantidadJuegos = min(v[i].cantidadJuegos, 15);
    cin.ignore(); // Para limpiar el buffer después de la entrada de enteros

    for (int j = 0; j < v[i].cantidadJuegos; j++) {
        cout << "Ingrese el código del juego " << j + 1 << ": ";
        cin.getline(v[i].codigosJuegos[j], sizeof(v[i].codigosJuegos[j]));
    }

    // Asignar la fecha del sistema
    leerFechaSistema(v[i].fechaVenta);

    cout << "Ingrese el nombre del empleado: ";
    cin.getline(v[i].empleado.nombre, sizeof(v[i].empleado.nombre));

    v[i].estado = 1; // Marcar como existente
}

void guardarVentas(Ventas* v) {
    char opcion;
    cout << "¿Está seguro que desea guardar los cambios permanentemente (S/N)?: ";
    cin >> opcion;

    if (opcion == 'S' || opcion == 's') {
        FILE *temp = fopen("ventasTemporal.dat", "w+");
        for (int i = 0; i < 100; i++) {
            if (v[i].estado != 0) { // Guardar solo ventas con estado válido
                fprintf(temp, "%s\n", v[i].codigo);
                fprintf(temp, "%d\n", v[i].cantidadJuegos);
                for (int j = 0; j < v[i].cantidadJuegos; j++) {
                    fprintf(temp, "%s\n", v[i].codigosJuegos[j]);
                }
                fprintf(temp, "%d\n", v[i].fechaVenta.dia);
                fprintf(temp, "%d\n", v[i].fechaVenta.mes);
                fprintf(temp, "%d\n", v[i].fechaVenta.anio);
                fprintf(temp, "%s\n", v[i].empleado.nombre);
                fprintf(temp, "%d\n", v[i].estado);
            }
        }
        fclose(temp);

        remove("ventas.dat");
        rename("ventasTemporal.dat", "ventas.dat");
        cout << "Los datos se han guardado exitosamente." << endl;
    }
}

void mostrarVentas(Ventas *v) {
    for (int i = 0; i < 100; i++) {
        if (v[i].estado != 0) {
            printf("Fecha de la venta: %d/%d/%d\n", v[i].fechaVenta.dia, v[i].fechaVenta.mes, v[i].fechaVenta.anio);
            printf("Código de la venta: %s\n", v[i].codigo);
            printf("Nombre del empleado: %s\n", v[i].empleado.nombre);
            printf("Cantidad de juegos comprados: %d\n", v[i].cantidadJuegos);
            printf("Códigos de los juegos:\n");
            for (int j = 0; j < v[i].cantidadJuegos; j++) {
                printf("  %d: %s\n", j + 1, v[i].codigosJuegos[j]);
            }
        }
    }
}

Ventas *buscarVenta(Ventas v[100], const char *codigo) {
    for (int i = 0; i < 100; i++) {
        if ((v[i].estado == 1 || v[i].estado == 2) && strcmp(v[i].codigo, codigo) == 0) {
            return &(v[i]);
        }
    }
    return NULL;
}

void registrarVenta(Ventas* v) {
    char codigo[10];
    cout << "Ingrese el código de la venta que desea registrar: ";
    cin.ignore();
    cin.getline(codigo, sizeof(codigo));

    Ventas* ventaRegistrar = buscarVenta(v, codigo);

    if (ventaRegistrar != NULL) {
        cout << "La venta ya está registrada en el sistema." << endl;
    } else {
        bool espacioDisponible = false;
        for (int i = 0; i < 100; i++) {
            if (v[i].estado == 0) {
                agregarVentas(v, i);
                cout << "Venta registrada exitosamente." << endl;
                espacioDisponible = true;
                break;
            }
        }

        if (!espacioDisponible) {
            cout << "No hay espacio para agregar más ventas." << endl;
        }
    }
}