#include <stdio.h>
#include <string.h>
#include "funciones.h"
int main()
{

    int opcion, subopcion = 0, opcionmarca, Eliminar;
    Vehiculo vehiculos[MAX_VEHICULOS]; // Arreglo para almacenar vehiculos
    int contador = 0;                  // Contador de vehiculos almacenados
    char marca[MAX_MARCAS][MAX];
    char temporal[MAX];

    // Cargar datos desde los archivos al inicio del programa

    do
    {
        menu();
        opcion = leerInteger();
        switch (opcion)
        {
        case 1: // Listar vehiculos disponibles
            printf("Cargando vehiculos disponibles...\n");
            listarVehiculosDisponibles();
            break;
        case 2: // Agregar/Eliminar vehiculo
           
            printf("Que desea hacer?\n");
            printf("1. Agregar vehiculo\n");
            printf("2. Eliminar vehiculo\n>> ");
            subopcion = leerInteger();
            if (subopcion == 1)
            {
                listarMarcas();
                printf("Seleccione la marca del vehiculo:\n>> ");
                opcionmarca = leerInteger();
                extrerMarcaArchivo(opcionmarca, temporal);
                AutoNuevo(temporal, contador);
                contador++;
            }
            else if (subopcion == 2)
            {
                listarVehiculosDisponibles();
                printf("Ingrese el ID del vehiculo a eliminar:\n>> ");
                Eliminar = leerInteger();
                AutoEliminar(Eliminar);
            }
            
            break;
            case 3: // Agregar/Eliminar marca de vehiculo
                MarcaNueva();
            break;
        case 4: //Buscar vehiculos por id, marca, modelo o anio
            buscarVehiculoPorID(leerInteger());
            break;
        case 5:
            printf("Gracias...\n");
            break;

        default:
            break;
        }

    } while (opcion != 5);

    return 0;
}
