#include "datos.h"
#include <iostream>
#include <cstring>
#include <windows.h>
#include <thread>
#include <chrono>
using namespace std;

#define ANSI_COLOR_ROJO     "\x1b[38;5;1m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_AZUL     "\x1b[38;5;4m"
#define ANSI_COLOR_VERDE     "\x1b[38;5;2m"

void leerFechaSistema(Fecha &hoy);
Juego *buscarJuego(Juego j[100], const char *codigo);
void actualizarCantidadJuegos(Juego* j);

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

void agregarVentas(Ventas* v, int i, const char *codigo, Usuario* usuario, Juego* j) {

    strcpy(v[i].codigo, codigo);

    cout << "Ingrese la cantidad de juegos que está comprando: ";
    cin >> v[i].cantidadJuegos;
    v[i].cantidadJuegos = min(v[i].cantidadJuegos, 15);
    cin.ignore(); // Para limpiar el buffer después de la entrada de enteros

    int contadorJuegos = 0;
    char codigoJuego[12] = "";

    while (contadorJuegos < v[i].cantidadJuegos) {
        cout << "Ingrese el código del juego " << contadorJuegos + 1 << ": ";
        cin.getline(codigoJuego, 12);

        Juego *juego = buscarJuego(j, codigoJuego);

        if ((juego != NULL) && (juego->stock > 0) && (juego->estado != 3)) {
            strcpy(v[i].codigosJuegos[contadorJuegos], codigoJuego);
            cout << ANSI_COLOR_VERDE <<"Juego agregado exitosamente. "<< ANSI_COLOR_AZUL<<"..."<< ANSI_COLOR_RESET <<endl;
            juego->stock--;
            contadorJuegos++;
        } else {
            cout << ANSI_COLOR_ROJO <<"Juego no disponible. "<<ANSI_COLOR_AZUL<< "Por favor agrega correctamente..."<< ANSI_COLOR_RESET <<endl;
        }
    }

    // Asignar la fecha del sistema
    leerFechaSistema(v[i].fechaVenta);
    strcpy(v[i].empleado.nombre, usuario->nombre);

    v[i].estado = 1; // Marcar como existente
}

void guardarVentas(Ventas* v, Juego* j) {
    char opcion;
    cout << "---------------------------------------------------------------------"<<endl;
    cout << "¿Está seguro que desea guardar los cambios permanentemente (S/N)?: ";
    cin >> opcion;

    if (opcion == 'S' || opcion == 's') {
        FILE *temp = fopen("ventasTemporal.dat", "w+");
        for (int i = 0; i < 100; i++) {
            if (v[i].estado != 0) { // Guardar solo ventas con estado válido
                fprintf(temp, "%s\n", v[i].codigo);
                fprintf(temp, "%d\n", v[i].cantidadJuegos);
                for (int k = 0; k < v[i].cantidadJuegos; k++) {
                    fprintf(temp, "%s\n", v[i].codigosJuegos[k]);
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

        actualizarCantidadJuegos(j);

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

void mostrarVentas(Ventas* v, Juego* j) {
    system("cls");
    printf("--------------------------------------------------\n");
    printf("|              REGISTROS DE VENTAS               |\n");
    printf("--------------------------------------------------\n");
    int contador = 0;
    for (int i = 0; i < 100; i++) {
        if (v[i].estado != 0) {
            printf("--------------------------------------------------\n");
            printf("Fecha de la venta: %d/%d/%d\n", v[i].fechaVenta.dia, v[i].fechaVenta.mes, v[i].fechaVenta.anio);
            printf("Código de la venta: %s\n", v[i].codigo);
            printf("Nombre del empleado: %s\n", v[i].empleado.nombre);
            printf("Cantidad de juegos comprados: %d\n", v[i].cantidadJuegos);
            printf("Códigos de los juegos:\n");
            for (int k = 0; k < v[i].cantidadJuegos; k++) {
                Juego *juego = buscarJuego(j, v[i].codigosJuegos[k]);
                if (juego != NULL) {
                     printf("  %d: Código de juego: %s, Nombre: %s\n", k + 1, v[i].codigosJuegos[k], juego->nombre);
                } else {
                    printf("  %d: Código de juego no encontrado\n", k + 1);
                }
            }
            printf("--------------------------------------------------\n");
            contador++;
        }
    }
    cout << ANSI_COLOR_VERDE << contador <<" Registros mostrados exitosamente. " << ANSI_COLOR_AZUL <<"Presiona ENTER para continuar..."<<ANSI_COLOR_RESET<<endl;
    system("pause");
    system("cls");
}

Ventas *buscarVenta(Ventas v[100], const char *codigo) {
    for (int i = 0; i < 100; i++) {
        if ((v[i].estado == 1 || v[i].estado == 2) && strcmp(v[i].codigo, codigo) == 0) {
            return &(v[i]);
        }
    }
    return NULL;
}

void registrarVenta(Ventas* v, Usuario* usuario, Juego* j) {
    char codigo[10];
    cout << "Ingrese el código de la venta que desea registrar: ";
    cin.ignore();
    cin.getline(codigo, sizeof(codigo));

    Ventas* ventaRegistrar = buscarVenta(v, codigo);

    if (ventaRegistrar != NULL) {
        cout << ANSI_COLOR_ROJO << "La venta ya está registrada en el sistema. " << ANSI_COLOR_AZUL <<"Presiona ENTER para regresar al menú..."<<ANSI_COLOR_RESET<<endl;
        system("pause");
    } else {
        bool espacioDisponible = false;
        for (int i = 0; i < 100; i++) {
            if (v[i].estado == 0) {
                cout <<ANSI_COLOR_VERDE << "<<<Código Disponible!!! Sigue rellenando los datos...>>>"<< ANSI_COLOR_RESET<<endl;
                agregarVentas(v, i, codigo, usuario, j);
                cout << ANSI_COLOR_VERDE << "Venta registrada exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
                system("pause");
                espacioDisponible = true;
                break;
            }
        }

        if (!espacioDisponible) {
            cout << ANSI_COLOR_ROJO << "No hay espacio para agregar mas ventas. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
            system("pause");
        }
    }
}