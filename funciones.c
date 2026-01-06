#include <stdio.h>
#include "funciones.h"
void menu(void)
{
    printf("-------------MENU--------------\n");
    printf("1. Listar vehiculos disponibles\n");
    printf("2. Agregar/Eliminar vehiculo\n");
    printf("3. Agregar Marca de Vehiculo\n");
    printf("4. Buscar vehiculo\n");
    printf("5. Salir\n");
    printf("-------------------------------\n");
    printf(">> ");
}
int leerInteger(void)
{
    int d;
    while ((scanf("%d", &d)) != 1)
    {
        limpiarBuffer();
        printf("**Error** Entrada invalida.\n");
        printf("Intenta nuevamente\n");
        printf(">> ");
    }
    limpiarBuffer(); // Limpiar el buffer despues de leer el entero
    return d;
}
void limpiarBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
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
void registrarUno(const Vehiculo *vehiculo)
{
    FILE *f = fopen("vehiculos.dat", "ab");

    if (f == NULL)
    {
        printf("Error: No se pudo abrir el archivo para escribir.\n");
        return;
    }

    size_t escritos = fwrite(vehiculo, sizeof(Vehiculo), 1, f);
    fclose(f);

    if (escritos != 1)
    {
        printf("Error: No se pudo guardar el vehiculo en el archivo.\n");
        return;
    }

    printf("Vehiculo guardado exitosamente.\n");
}

// Actualiza solo el campo estado de un vehiculo en el archivo binario
int actualizarEstado(int id, char nuevoEstado)
{
    FILE *f = fopen("vehiculos.dat", "rb+");
    if (f == NULL)
    {
        printf("Error: No se pudo abrir el archivo para actualizar.\n");
        return 0;
    }

    Vehiculo v;
    while (fread(&v, sizeof(Vehiculo), 1, f) == 1)
    {
        if (v.id == id)
        {
            v.estado = nuevoEstado;
            if (fseek(f, -(long)sizeof(Vehiculo), SEEK_CUR) != 0)
            {
                printf("Error: No se pudo posicionar en el archivo.\n");
                fclose(f);
                return 0;
            }
            if (fwrite(&v, sizeof(Vehiculo), 1, f) != 1)
            {
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

// Agregar función para cargar vehículos desde el archivo binario
int cargarVehiculos(Vehiculo vehiculos[], int maxVehiculos)
{
    FILE *f = fopen("vehiculos.dat", "rb");
    if (f == NULL)
    {
        printf("No se encontro el archivo de vehiculos. Se iniciara con una lista vacia.\n");
        return 0; // No hay vehículos cargados
    }

    int contador = 0;
    while (contador < maxVehiculos && fread(&vehiculos[contador], sizeof(Vehiculo), 1, f) == 1)
    {
        contador++;
    }

    fclose(f);
    return contador; // Retorna el número de vehículos cargados
}

// Agregar función para guardar marcas en un archivo de texto
void guardarMarcas(const char marcas[][MAX], int cantidad)
{
    FILE *f = fopen("marcas.txt", "w");
    if (f == NULL)
    {
        printf("Error: No se pudo abrir el archivo de marcas para escribir.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++)
    {
        fprintf(f, "%s\n", marcas[i]);
    }

    fclose(f);
}

// Agregar función para cargar marcas desde un archivo de texto
int cargarMarcas(char marcas[][MAX], int maxMarcas)
{
    FILE *f = fopen("marcas.txt", "r");
    if (f == NULL)
    {
        printf("No se encontro el archivo de marcas. Se iniciara con una lista vacia.\n");
        return 0; // No hay marcas cargadas
    }

    int contador = 0;
    while (contador < maxMarcas && fgets(marcas[contador], MAX, f))
    {
        size_t len = strlen(marcas[contador]);
        if (len > 0 && marcas[contador][len - 1] == '\n')
        {
            marcas[contador][len - 1] = '\0'; // Eliminar el salto de línea
        }
        contador++;
    }

    fclose(f);
    return contador; // Retorna el número de marcas cargadas
}

void buscarVehiculoPorID(int idBuscado) {
    FILE *archivo = fopen("vehiculos.dat", "rb"); 
    if (!archivo) {
        printf("No se encontró el archivo de vehículos.\n");
        return;
    }

    Vehiculo v;
    int encontrado = 0;

    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v.id == idBuscado) {
            printf("Vehículo encontrado:\n");
            printf("ID: %d | Modelo: %s | Anio: %d | Precio: %.2f$ | Marca: %s | %s\n",
                   v.id,
                   v.modelo,
                   v.anio,
                   v.precio,
                   v.marca,
                   v.usado ? "Usado" : "Nuevo");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("No se encontró un vehículo con ID %d.\n", idBuscado);

    fclose(archivo);
}