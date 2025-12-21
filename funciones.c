#include <stdio.h>
#include "funciones.h"
void menu(void){
    printf("\n-------------MENU--------------\n");
    printf("1. Listar vehiculos disponibles\n");
    printf("2. Agregar/Eliminar vehiculo\n");
    printf("3. Agregar Marca de Vehiculo\n");
    printf("4. Buscar vehiculo\n");
    printf("5. Salir\n");
    printf("-------------------------------\n");
    printf(">> ");
}
int leerInteger(void){
    int d;
    while ((scanf("%d", &d))!=1)
    {
        limpiarBuffer();
        printf("**Error** Entrada invalida.\n");
        printf("Intenta nuevamente\n");
        printf(">> ");
    }
    limpiarBuffer(); // Limpiar el buffer despues de leer el entero
    return d;
}
void limpiarBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
