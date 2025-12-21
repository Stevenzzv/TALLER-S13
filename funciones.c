#include <stdio.h>
#include "funciones.h"
void menu(void){
    printf("-------------MENU--------------\n");
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
int blanco(const char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
        {
            return 0; // No está en blanco
        }
    }
    return 1; // Está en blanco
}

// Lee una cadena de caracteres con validación
void leerChar(char str[], int size)
{
    do
    {
        fgets(str, size, stdin);
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n')
        {
            str[len - 1] = '\0'; // Eliminar el salto de línea
        }
        if (blanco(str))
        {
            printf("La cadena ingresada esta en blanco. Intente nuevamente.\n>> ");
        }
    } while (blanco(str));
}