#ifndef FUNCIONES_H
#include <string.h>
#define FUNCIONES_H
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

// Declarar las nuevas funciones para persistencia de datos

void MarcaNueva ();
void listarMarcas();
void extrerMarcaArchivo (int indexMarca, char temporal[]);
void AutoNuevo (char marca[], int id);
void AutoEliminar (int idVehiculo);
void listarVehiculosDisponibles();
void buscarVehiculoPorID(int idBuscado);
#endif // FUNCIONES_H