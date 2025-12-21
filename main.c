#include <stdio.h>
#include "funciones.h"
int main(int argc, char const *argv[])
{

int opcion, continuar, indix = 0;
Vehiculo vehiculos[MAX_VEHICULOS]; // Arreglo para almacenar vehiculos
int contador = 0; // Contador de vehiculos almacenados
char marca[MAX_MARCAS][MAX];

    do
    {
        menu();
        opcion = leerInteger();
        switch (opcion)
        {
        case 1: //Listar vehiculos disponibles
            if (contador == 0)
            {
                printf("No hay vehiculos disponibles.\n");
            }
            else
            {
                printf("Vehiculos disponibles:\n");
                for (int i = 0; i < contador; i++)
                {
                    if (vehiculos[i].estado == 1) // Si el vehiculo esta disponible
                    {
                        printf("ID: %d | Modelo: %s | Anio: %d | Precio: %.2f$ | %s\n",
                               vehiculos[i].id,
                               vehiculos[i].modelo,
                               vehiculos[i].anio,
                               vehiculos[i].precio,
                               vehiculos[i].usado ? "Usado" : "Nuevo");
                    }
                }
            }

            break;
        case 2:
            printf("Que desea hacer?\n");
            printf("1. Agregar vehiculo\n");
            printf("2. Eliminar vehiculo\n>> ");
            continuar = leerInteger();
            if (continuar == 1)
            {
                printf("Ingrese el modelo del vehiculo: \n>> ");
                leerChar(vehiculos[contador].modelo, MAX);

                printf("Ingrese el anio del vehiculo: \n>> ");
                vehiculos[contador].anio = leerInteger();

                printf("Ingrese el precio del vehiculo: \n>> ");
                scanf("%f", &vehiculos[contador].precio);

                printf("Ingrese si es usado (1: usado, 0: nuevo): \n>> ");
                vehiculos[contador].usado = leerInteger();
                

                vehiculos[contador].estado = 1; // Disponible
                vehiculos[contador].id = contador+1; // Asignar ID
                contador++;
                printf("Vehiculo agregado exitosamente!\n");
            }
            else if (continuar == 2)
            {
                //Eliminar vehiculo
            }
            else
            {
                printf("Opcion invalida\n");
            }

            break;
        case 3:
            if (indix >= MAX_MARCAS)
            {
                printf("No se pueden agregar mas marcas.\n");
            }
            else
            {
                printf("Ingrese el nombre de la marca a agregar.\n>> ");
                leerChar(marca[indix], MAX);
                printf("Marca agregada exitosamente.\n");
                indix++;
            }
            break;
        case 4:
            /* code */
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
