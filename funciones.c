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
void registrarUno(const Vehiculo *vehiculo) {
    FILE *f = fopen("vehiculos.dat", "ab");

    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo para escribir.\n");
        return;
    }

    size_t escritos = fwrite(vehiculo, sizeof(Vehiculo), 1, f);
    fclose(f);

    if (escritos != 1) {
        printf("Error: No se pudo guardar el vehiculo en el archivo.\n");
        return;
    }

    printf("Vehiculo guardado exitosamente.\n");
}

// Actualiza solo el campo estado de un vehiculo en el archivo binario
int actualizarEstado(int id, char nuevoEstado) {
    FILE *f = fopen("vehiculos.dat", "rb+");
    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo para actualizar.\n");
        return 0;
    }

    Vehiculo v;
    while (fread(&v, sizeof(Vehiculo), 1, f) == 1) {
        if (v.id == id) {
            v.estado = nuevoEstado;
            if (fseek(f, -(long)sizeof(Vehiculo), SEEK_CUR) != 0) {
                printf("Error: No se pudo posicionar en el archivo.\n");
                fclose(f);
                return 0;
            }
            if (fwrite(&v, sizeof(Vehiculo), 1, f) != 1) {
                printf("Error: No se pudo escribir la actualizacion.\n");
                fclose(f);
                return 0;
            }
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    printf("No se encontro un vehiculo con ese ID para actualizar.\n");
    return 0;
}