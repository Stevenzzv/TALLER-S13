#ifndef FUNCIONES_H
#define FUNCIONES_H
#define MAX 30
typedef struct
{
    char marca[MAX];
    char modelo[MAX];
    int anio;
    float precio;
    char estado;
    int usado;
} Vehiculo;


void menu(void);
int leerInteger(void);
void limpiarBuffer(void);


#endif // FUNCIONES_H