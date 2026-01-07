#include <stdio.h>
#include "funciones.h"
void menu(void)
{
    printf("-------------MENU--------------\n");
    printf("1. Listar vehiculos disponibles\n");
    printf("2. Agregar/Eliminar vehiculo\n");
    printf("3. Agregar Marca de Vehiculo\n");
    printf("4. Buscar vehiculo\n");
    printf("5. Registrar venta\n");
    printf("6. Mostrar ventas\n");
    printf("7. Salir\n");
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
    limpiarBuffer(); // Limpiar el buffer despues de leer el entero
    return f;
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
float leerPresupuesto() {
    FILE *archivo = fopen("presupuesto.bin", "rb");
    float presupuesto = 0.0f;

    if (archivo) {
        fread(&presupuesto, sizeof(float), 1, archivo);
        fclose(archivo);
    }

    return presupuesto; // Si no existe el archivo, retorna 0
}

void guardarPresupuesto(float presupuesto) {
    FILE *archivo = fopen("presupuesto.bin", "ab");
    if (!archivo) {
        printf("Error al guardar el presupuesto.\n");
        return;
    }
    fwrite(&presupuesto, sizeof(float), 1, archivo);
    fclose(archivo);
}

void listarVehiculosDisponibles() {

    FILE *archivo = fopen("vehiculos.dat", "rb");
    if (!archivo) {
        printf("No se encontró el archivo de vehículos.\n");
        return;
    }

    Vehiculo v;
    int encontrado = 0;

    printf("Vehículos disponibles:\n");
    while (fread(&v, sizeof(Vehiculo), 1, archivo) == 1) {
        if (v.estado == 1) { // Si el vehículo está disponible
            printf("ID: %-4d | Modelo: %s | Anio: %d | Precio: %.2f$ | Marca: %s | %s | %s |\n",
                   v.id,
                   v.modelo,
                   v.anio,
                   v.precio,
                   v.marca,
                   v.usado ? "Usado" : "Nuevo",
                (v.estado == 1) ? "Disponible" : "No Disponible");
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("No hay vehículos disponibles en este momento.\n");

    fclose(archivo);
}

void registrarVenta (int id){
    FILE *archivo = fopen("ventas.dat", "ab");
    if (!archivo) {
        printf("Error al abrir el archivo de ventas.\n");
        return;
    }

    Venta nuevaVenta;
    nuevaVenta.idVehiculoVendido = id;

    printf("Ingrese el nombre del cliente:\n>> ");
    leerChar(nuevaVenta.cliente.nombre, MAX);

    printf("Ingrese la direccion del cliente:\n>> ");
    leerChar(nuevaVenta.cliente.direccion, MAX);

    printf("Ingrese el telefono del cliente:\n>> ");
    leerChar(nuevaVenta.cliente.telefono, MAX);

    printf("Ingrese el nombre del vendedor:\n>> ");
    leerChar(nuevaVenta.vendedor.vendedor, MAX);

    printf("Ingrese la tarifa de comision del vendedor (en porcentaje):\n>> ");
    nuevaVenta.vendedor.tarifaComision = leerFloat();
    
    nuevaVenta.ganancia = 0.0; // Inicializar ganancia en 0, se puede calcular despues
    FILE *archivoVehiculos = fopen("vehiculos.dat", "rb");
    if (!archivoVehiculos) {
        printf("Error al abrir el archivo de vehiculos para calcular ganancia.\n");
        fclose(archivo);
        return;
    }
    Vehiculo v;
    int encontrado = 0;
    while ((fread(&v, sizeof(Vehiculo), 1, archivoVehiculos) == 1) && !encontrado) {
        if (v.id == id) {
            nuevaVenta.vendedor.totalVendido += (nuevaVenta.vendedor.tarifaComision / 100.0f) * v.precio;
            nuevaVenta.ganancia = v.precio - (v.precio * (nuevaVenta.vendedor.tarifaComision / 100.0f));
            v.estado = 0; 
            encontrado = 1;
                break;
            }
        }
        fclose(archivoVehiculos);
    fwrite(&nuevaVenta, sizeof(Venta), 1, archivo);
    fclose(archivo);

    printf("Venta registrada exitosamente.\n");
    
}

void mostrarVentas () {
    FILE *archivo = fopen("ventas.dat", "rb");
    if (!archivo) {
        printf("No se encontró el archivo de ventas.\n");
        return;
    }

    Venta v;
    int encontrado = 0;

    printf("Ventas realizadas:\n");
    while (fread(&v, sizeof(Venta), 1, archivo) == 1) {
        printf("ID Vehiculo Vendido: %d | Cliente: %s | Vendedor: %s | Ganancia: %.2f$\n",
               v.idVehiculoVendido,
               v.cliente.nombre,
               v.vendedor.vendedor,
               v.ganancia);
        encontrado = 1;
    }

    if (!encontrado)
        printf("No hay ventas registradas en este momento.\n");

    fclose(archivo);
}