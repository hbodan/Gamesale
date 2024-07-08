// Estado = 0 (De alta) Estado = 1 (Eliminado)

// Estructura Fecha
struct Fecha
{
    int dia;
    int mes;
    int anio;
};

// Estructura Usuario
struct Usuario
{
    char codigo[5] = "";
    char nombre[20] = "";
    char usuario[15] = "";
    char contrasenia[20] = "";
    int estado = 1; // EOF-Eliminado, 0-Vacío 1-Existente, 2-Modificado, 3-Devuelto
};

// Estructura Juego
struct Juego
{
    char codigo[12] = "";
    char nombre[50] = "";
    char genero[30];
    char descripcion [100];
    double precio = 0.00;
    int stock = 0;
    int estado = 1; // EOF-Eliminado, 1-Existente, 2-Modificado, 3-Devuelto
};

// Estructura Venta
struct Ventas
{
    char codigo[10] = "";
    char codigosJuegos[15][12];
    int cantidadJuegos;
    Fecha fechaVenta;
    Usuario empleado;
    int estado = 1;
};

// Estructura Historial
struct Historial
{
    int numVentas;
};
