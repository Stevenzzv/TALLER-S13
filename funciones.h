#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <string.h>
#define MAX 30
#define MAX_VEHICULOS 30
#define MAX_MARCAS 10
typedef struct
{
    char marca[MAX];
    char modelo[MAX];
    int anio;
    float precio;
    char estado; // 1: disponible, 0: no disponible
    int usado;
    int id;
} Vehiculo;

void menu(void);
int leerInteger(void);
void limpiarBuffer(void);
int blanco(const char str[]);
void leerChar(char str[], int size);
void registrarUno(const Vehiculo *vehiculo);
int actualizarEstado(int id, char nuevoEstado);
// Declarar las nuevas funciones para persistencia de datos
int cargarVehiculos(Vehiculo vehiculos[], int maxVehiculos);
void guardarMarcas(const char marcas[][MAX], int cantidad);
int cargarMarcas(char marcas[][MAX], int maxMarcas);

#endif // FUNCIONES_H