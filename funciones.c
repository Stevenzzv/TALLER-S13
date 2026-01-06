#include <stdio.h>
#include "funciones.h"
void menu(void)
{
    printf("-------------MENU--------------\n");
    printf("1. Listar vehiculos disponibles\n");
    printf("2. Agregar/Desactivar vehiculo\n");
    printf("3. Agregar marca de Vehiculo\n");
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
    limpiarBuffer(); 
    return d;
}
float leerFloat(void)
{
    float f;
    while ((scanf("%f", &f)) != 1)
    {
        limpiarBuffer();
        printf("**Error** Entrada invalida.\n");
        printf("Intenta nuevamente\n");
        printf(">> ");
    }
    limpiarBuffer(); 
    return f;
}
void limpiarBuffer(void)
{
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

// FUNCIONES DE PERSISTENCIA DE DATOS

void MarcaNueva(){
    FILE *archivo;
    archivo = fopen("marcas.txt", "a");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de marcas para agregar nueva marca.\n");
        return;
    }
    char nuevaMarca[MAX];
    printf("Ingrese la nueva marca de vehiculo: ");
    leerChar(nuevaMarca, MAX);
    fprintf(archivo, "%s\n", nuevaMarca);
    fclose(archivo);
    printf("Marca agregada exitosamente.\n");
}

void listarMarcas() {
    FILE *archivo = fopen("marcas.txt", "r");  // Abrir archivo en modo lectura de texto
    if (!archivo) {
        printf("No se encontró el archivo de marcas.\n");
        return;
    }

    char marca[MAX];
    int contador = 1;

    printf("Listado de marcas:\n");
    while (fgets(marca, MAX, archivo)) {
        marca[strcspn(marca, "\n")] = 0;

        printf("%d. %s\n", contador, marca);
        contador++;
    }

    fclose(archivo);
}
void extrerMarcaArchivo (int indexMarca, char temporal[]) {
    FILE *archivo = fopen("marcas.txt", "r");  // Abrir archivo en modo lectura de texto
    if (!archivo) {
        printf("No se encontró el archivo de marcas.\n");
        return;
    }

    char marca[MAX];
    int contador = 1;

    while (fgets(marca, MAX, archivo)) {
        marca[strcspn(marca, "\n")] = 0;

        if (contador == indexMarca) {
            printf("Marca seleccionada: %s\n", marca);
            strcpy(temporal, marca);
            break;
        }
        contador++;
    }

    fclose(archivo);
}
void AutoNuevo (char marca[], int id) {
    FILE *archivo;
    archivo = fopen("vehiculos.bin", "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de vehiculos para agregar nuevo vehiculo.\n");
        return;
    }
    Vehiculo nuevoVehiculo;
    strcpy(nuevoVehiculo.marca, marca);
    printf("Ingrese el modelo del vehiculo:\n>> ");
    leerChar(nuevoVehiculo.modelo, MAX);
    printf("Ingrese el anio del vehiculo:\n>> ");
    nuevoVehiculo.anio = leerInteger();
    printf("Ingrese el precio del vehiculo:\n>> ");
    nuevoVehiculo.precio = leerFloat();
    printf("Ingrese si el vehiculo es usado (1: usado, 0: nuevo):\n>> ");
    nuevoVehiculo.usado = leerInteger();
    nuevoVehiculo.id = id; 
    nuevoVehiculo.estado = 1; // Disponible por defecto

    fwrite(&nuevoVehiculo, sizeof(Vehiculo), 1, archivo);


    fclose(archivo);    
    printf("Vehiculo agregado exitosamente.\n");

}

void AutoEliminar(int idVehiculo) {
    FILE *archivo = fopen("vehiculos.bin", "r+b"); // lectura/escritura binaria
    if (!archivo) {
        printf("No se pudo abrir el archivo de vehículos.\n");
        return;
    }

    Vehiculo v;
    long pos = 0;
    int encontrado = 0;

    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v.id == idVehiculo) {
            encontrado = 1;
            break;
        }
        pos++;
    }

    if (encontrado && v.estado == 1) {
        v.estado = 0; // marcar como no disponible

        fseek(archivo, pos * sizeof(Vehiculo), SEEK_SET);
        fwrite(&v, sizeof(Vehiculo), 1, archivo);

        printf("Vehículo con ID %d desactivado exitosamente.\n", idVehiculo);
    } else {
        printf("Vehículo con ID %d no encontrado.\n", idVehiculo);
    }

    fclose(archivo);
}

void listarVehiculosDisponibles() {
    FILE *archivo = fopen("vehiculos.bin", "rb"); // lectura binaria
    if (!archivo) {
        printf("No se encontró el archivo de vehículos.\n");
        return;
    }

    Vehiculo v;
    int contador = 0;

    printf("Vehículos disponibles:\n");
    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v.estado == 1) { // disponible
            printf("ID: %d | Modelo: %s | Anio: %d | Precio: %.2f$ | Marca: %s | %s\n",
                   v.id,
                   v.modelo,
                   v.anio,
                   v.precio,
                   v.marca,
                   v.usado ? "Usado" : "Nuevo");
            contador++;
        }
    }

    if (contador == 0)
        printf("No hay vehículos disponibles.\n");

    fclose(archivo);
}

void buscarVehiculoPorID(int idBuscado) {
    FILE *archivo = fopen("vehiculos.bin", "rb"); 
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