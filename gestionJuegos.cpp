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

void agregarJuegos(Juego* j, int i, const char *codigo)
{
 
    strcpy(j[i].codigo, codigo);

    cout << "Ingrese el titulo del juego: " << endl;
    cin.getline(j[i].nombre, 50);

    cout << "Ingrese el nombre del género: " << endl;
    cin.getline(j[i].genero, 50);

    cout << "Ingrese la descripción del juego: " << endl;
    cin.getline(j[i].descripcion, 100);

    cout << "Ingrese el precio del juego: " << endl;
    cin >> j[i].precio;

    cout << "Ingrese el stock del juego: " << endl;
    cin >> j[i].stock;
    j[i].estado = 1;
}

void guardarJuegos(Juego* j)
{
    char opcion;
    cout<< "---------------------------------------------------------------"<<endl;
    cout << "Está seguro que desea guardar los cambios permanentemente (S/N)?: ";
    cin >> opcion;
    

    if (opcion == 'S' || opcion == 's')
    {
        FILE *archi;
        archi = fopen("juegos.dat", "w+"); // Cambiado a modo de actualización

        if (archi == NULL)
        {
            perror("Error al intentar abrir el archivo juegos.dat para escritura.");
            return;
        }

        for (int i = 0; i < 100; i++)
        {
            if (j[i].estado != 0) // Guardar solo los juegos que están en uso
            {
                fprintf(archi, "%s\n", j[i].codigo);
                fprintf(archi, "%s\n", j[i].nombre);
                fprintf(archi, "%s\n", j[i].genero);
                fprintf(archi, "%s\n", j[i].descripcion);
                fprintf(archi, "%lf\n", j[i].precio);
                fprintf(archi, "%d\n", j[i].stock);
                fprintf(archi, "%d\n", j[i].estado);
            }
        }

        fclose(archi);

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

void actualizarCantidadJuegos(Juego* j)
{

    FILE *archi;
    archi = fopen("juegos.dat", "w+"); // Cambiado a modo de actualización

    if (archi == NULL)
    {
        perror("Error al intentar abrir el archivo juegos.dat para escritura.");
        return;
    }

    for (int i = 0; i < 100; i++)
    {
        if (j[i].estado != 0) // Guardar solo los juegos que están en uso
        {
            fprintf(archi, "%s\n", j[i].codigo);
            fprintf(archi, "%s\n", j[i].nombre);
            fprintf(archi, "%s\n", j[i].genero);
            fprintf(archi, "%s\n", j[i].descripcion);
            fprintf(archi, "%lf\n", j[i].precio);
            fprintf(archi, "%d\n", j[i].stock);
            fprintf(archi, "%d\n", j[i].estado);
        }
    }

    fclose(archi);
}

void cargarJuegos(Juego* j)
{
    FILE *archi;
    archi = fopen("juegos.dat", "r");

    if (archi == NULL)
    {
        perror("Error al abrir el archivo juegos.dat. Asignando valores por defecto.");
        for (int i = 0; i < 100; i++)
        {
            j[i].estado = 0; // Marcar como vacío
        }
        return;
    }

    int i = 0;
    while (i < 100 &&
           fscanf(archi, "%11s\n", j[i].codigo) != EOF &&
           fgets(j[i].nombre, sizeof(j[i].nombre), archi) != NULL &&
           fgets(j[i].genero, sizeof(j[i].genero), archi) != NULL &&
           fgets(j[i].descripcion, sizeof(j[i].descripcion), archi) != NULL &&
           fscanf(archi, "%lf\n", &j[i].precio) != EOF && // Leer como double
           fscanf(archi, "%d\n", &j[i].stock) != EOF &&
           fscanf(archi, "%d\n", &j[i].estado) != EOF)
    {
        j[i].codigo[strcspn(j[i].codigo, "\n")] = '\0';
        j[i].nombre[strcspn(j[i].nombre, "\n")] = '\0';
        j[i].genero[strcspn(j[i].genero, "\n")] = '\0';
        j[i].descripcion[strcspn(j[i].descripcion, "\n")] = '\0';
        i++;
    }

    for (; i < 100; i++)
    {
        j[i].estado = 0;
    }

    fclose(archi);
}
void mostrarJuegos(Juego* j)
{
    system("cls");
    printf("--------------------------------------------------\n");
    printf("|              REGISTROS DE JUEGOS               |\n");
    printf("--------------------------------------------------\n");
    int contador = 0;
    for(int i =0; i<100; i++){
        if(j[i].estado == 1 || j[i].estado == 2){
            printf("--------------------------------------------------\n");
            printf("Código del juego:       %s\n", j[i].codigo);
            printf("Titulo del juego:       %s\n", j[i].nombre);
            printf("Genero del juego:       %s\n", j[i].genero);
            printf("Descripcion del juego:  %s\n", j[i].descripcion);            
            printf("precio del juego:       %lf\n", j[i].precio);
            printf("stock del juego:        %d\n", j[i].stock);
            printf("--------------------------------------------------\n");
            contador+=1;
        }
    }
    cout << ANSI_COLOR_VERDE << contador <<" Registros mostrados exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
    system("pause");
    system("cls");
}

Juego *buscarJuego(Juego j[100], const char *codigo)
{
    Juego *jg = NULL;
    for (int i = 0; i < 100; i++)
    {
        if ((j[i].estado == 1 || j[i].estado == 2 || j[i].estado == 3) && strcmp(j[i].codigo, codigo) == 0)
        {
            jg = &(j[i]);
            break;
        }
    }
    return jg;
}

void eliminarJuego(Juego* j)
{

    char codigo[12] = "";
    cout<<"Introduzca el codigo del juego: "<<endl;
    cin.ignore();
    cin.getline(codigo, 12);

    Juego *juegoEliminar = buscarJuego(j, codigo);

    if (juegoEliminar != NULL)
    {
        juegoEliminar->estado = 3;
        cout << ANSI_COLOR_VERDE << "Juego eliminado exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
        system("pause");
    }
    else
    {
        cout << ANSI_COLOR_ROJO << "No se encontró el juego con el código especificado. " << ANSI_COLOR_AZUL <<"Presiona ENTER para regresar al menú..."<<ANSI_COLOR_RESET<<endl;
        system("pause");
    }
}

void actualizarJuego(Juego* j, int i)
{
    cout << "Ingrese el titulo del juego: " << endl;
    cin.getline(j[i].nombre, 50);
    cout << "Ingrese el nombre del género: " << endl;
    cin.getline(j[i].genero, 30);
    cout << "Ingrese la descripción del juego: " << endl;
    cin.getline(j[i].descripcion, 100);
    cout << "Ingrese el precio del juego: " << endl;
    cin >> j[i].precio;
    cout << "Ingrese el stock del juego: " << endl;
    cin >> j[i].stock;
    cin.ignore();
    j[i].estado = 2;
}
void modificarJuego(Juego* j)
{
    char codigo[12] = "";
    cout<<"Ingrese el codigo del juego"<<endl;
    cin.ignore();
    cin.getline(codigo, 12);

    Juego *juegoModificar = buscarJuego(j, codigo);

    if (juegoModificar != NULL)
    {
        cout << ANSI_COLOR_VERDE << "El juego está registrado en el sistema. "<< ANSI_COLOR_AZUL << "Edita tu juego..."<<ANSI_COLOR_RESET<<endl;
        cout.flush();

        for(int i = 0; i<100; i++){
            if(j[i].estado!=0){
                if(strcmp(j[i].codigo, codigo)==0){
                    actualizarJuego(j,i);
                    break;
                 }
            }
            
        }
        cout << ANSI_COLOR_VERDE << "Juego editado exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
        system("pause");
    }
    else
    {
        cout << ANSI_COLOR_ROJO << "No se encontró el juego con el código especificado. " << ANSI_COLOR_AZUL <<"Presiona ENTER para regresar al menú..."<<ANSI_COLOR_RESET<<endl;
        cout.flush();
        system("pause");
    }
}

void registrarJuego(Juego* j)
{
    char codigo[12]; 
    cout << "Ingrese el código del juego a registrar: ";
    cin.ignore();
    cin.getline(codigo, sizeof(codigo));

    Juego *juegoRegistrar = buscarJuego(j, codigo);

    if (juegoRegistrar != NULL)
    {
        cout << ANSI_COLOR_ROJO << "El juego ya está registrado en el sistema. " << ANSI_COLOR_AZUL <<"Presiona ENTER para regresar al menú..."<<ANSI_COLOR_RESET<<endl;
        system("pause");
    }
    else
    {
        bool espacioDisponible = false;
        for (int i = 0; i < 100; i++)
        {
            if (j[i].estado == 0)
            {
                cout <<ANSI_COLOR_VERDE << "<<<Código Disponible!!! Sigue rellenando los datos...>>>"<< ANSI_COLOR_RESET<<endl;
                agregarJuegos(j, i, codigo);
                cout << ANSI_COLOR_VERDE << "Juego registrado exitosamente. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
                system("pause");
                espacioDisponible = true;
                break;
            }
        }

        if (!espacioDisponible)
        {
            cout << ANSI_COLOR_ROJO << "No hay espacio para agregar mas juegos. " << ANSI_COLOR_AZUL<<"Presiona ENTER para continuar..." << ANSI_COLOR_RESET<<endl;
            system("pause");
        }
    }
}
