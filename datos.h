//Estado = 0 (De alta) Estado = 1 (Eliminado)

struct Usuario{
    char codigo[5] = "";
    char nombre[20] = "";
    char usuario[15] = "";
    char contrasenia[20] = "";
    int juegosVendidos = 0;
    int estado = 0;
};

struct Genero{
    char codigo[3] = "";
    char nombre[30] = "";
    char descripcion[100] = "";
    int estado = 0;
};

struct Juego{
    char codigo[12] = "";
    char nombre[50] = "";
    Genero genero;
    double precio = 0.00;
    int stock = 0;
    int estado = 0;
};

struct Fecha{
    int dia;
    int mes;
    int anio;
};

struct Descuento{
    char nombre[30] = "";
    int identificador = 0;
    int porcentajeDescuento = 0;
    char codigoVideojuego[12] = "";
    char codigoGenero[3] = "";
    double precio = 0.00;
    int cantidad = 0;
    int estado = 0;
};

struct Venta{
    char codigo[10] = "";
    Juego juegos[15];
    Fecha fechaVenta;
    Usuario empleado;
    double descuentoTotal  = 0.00;
    double totalSinDescuento = 0.00;
    double totalConDescuento = 0.00;
};