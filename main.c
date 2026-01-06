#include <stdio.h>
#include <string.h>
#include "funciones.h"
int main()
{

    int opcion, subopcion = 0, opcionmarca, Eliminar;
    Vehiculo vehiculos[MAX_VEHICULOS]; // Arreglo para almacenar vehiculos
    int contador = 0;                  // Contador de vehiculos almacenados
    int marcasContador = 0;
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
           if (contador >= MAX_VEHICULOS) {
                printf("No se pueden agregar más vehículos. Capacidad máxima alcanzada.\n");
                break;
            }
            if (marcasContador == 0)
            {
                printf("No hay marcas disponibles. Por favor, agregue una marca primero.\n");
                break;
            }
            
            printf("Que desea hacer?\n");
            printf("1. Agregar vehiculo\n");
            printf("2. Eliminar vehiculo\n>> ");
            subopcion = leerInteger();
            while (subopcion < 1 || subopcion > 2){
                subopcion = leerInteger();
            }
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
                if (contador == 0)
                {
                    printf("No hay vehículos disponibles para eliminar.\n");
                    break;
                }
                listarVehiculosDisponibles();
                printf("Ingrese el ID del vehiculo a eliminar:\n>> ");
                Eliminar = leerInteger();
                AutoEliminar(Eliminar);
            }
            
            break;
            case 3: // Agregar/Eliminar marca de vehiculo
            if (marcasContador >= MAX_MARCAS) {
                printf("No se pueden agregar más marcas. Capacidad máxima alcanzada.\n");
                break;
            }
                MarcaNueva();
                marcasContador++;
            break;
        case 4: //Buscar vehiculos por id, marca, modelo o anio
            if (contador == 0)
            {
                printf("No hay vehículos disponibles para buscar.\n");
                break;
            }
            printf("Ingrese el ID del vehiculo a buscar:\n>> ");
            buscarVehiculoPorID(leerInteger());
            break;
        case 5:
            printf("Gracias...\n");
            break;

        default:
        printf("Opcion invalida. Intente nuevamente.\n");
            break;
        }

    } while (opcion != 5);

    return 0;
}
