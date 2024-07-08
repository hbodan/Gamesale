#include <time.h>
#include "datos.h"

void leerFechaSistema(Fecha &hoy){
    time_t tiempo = time(NULL);//variables donde guardo el valor de la funcion time. 
    tm *fechaSistema = localtime(&tiempo); //estructura donde obtengo el tiempo 
    hoy.dia=fechaSistema->tm_mday;
    hoy.mes=fechaSistema->tm_mon+1;
    hoy.anio=fechaSistema->tm_year+1900;   
}
