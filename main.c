#include <stdio.h>
#include <string.h>
#include "funciones.h"
int main(int argc, char const *argv[])
{

int opcion, opc, continuar, indix = 0;
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
                        printf("ID: %d | Modelo: %s | Anio: %d | Precio: %.2f$ | Marca: %s |%s\n",
                               vehiculos[i].id,
                               vehiculos[i].modelo,
                               vehiculos[i].anio,
                               vehiculos[i].precio,
                               vehiculos[i].marca,
                               vehiculos[i].usado ? "Usado" : "Nuevo");
                    }
                }
            }

            break;
        case 2:
            if (contador >= MAX_VEHICULOS)
            {
                printf("No se pueden agregar mas vehiculos.\n");
                break;
            }
            if (indix==0) {
                printf("No hay marcas de vehiculo agregadas.\n");
                break;
            }
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

                printf("Ingrese el precio del vehiculo (USD): \n>> ");
                scanf("%f", &vehiculos[contador].precio);

                printf("Ingrese si es usado (1: usado, 0: nuevo): \n>> ");
                vehiculos[contador].usado = leerInteger();
                

                vehiculos[contador].estado = 1; // Disponible
                vehiculos[contador].id = contador+1; // Asignar ID
                printf("Marcas disponibles:\n");
                for (int i = 0; i < indix; i++)
                {
                    printf("%d. %s\n", i + 1, marca[i]);
                }
                printf("Seleccione la marca del vehiculo:\n>> ");
                opc = (leerInteger())-1;
                while (opc < 0 || opc >= indix)
                {
                    printf("Elija una opcion dentro del menu, intentelo nuevamente.\n>> ");
                    opc = leerInteger();
                }
                strcpy(vehiculos[contador].marca, marca[opc]);

                registrarUno(&vehiculos[contador]);
                contador++;
                printf("Vehiculo agregado exitosamente!\n");
            }
            else if (continuar == 2)
            {
                if (contador == 0) {
                    printf("No hay vehiculos para eliminar.\n");
                    break;
                }

                printf("Ingrese el ID del vehiculo a marcar como no disponible: \n>> ");
                int idEliminar = leerInteger();
                int encontrado = 0;

                for (int i = 0; i < contador; i++) {
                    if (vehiculos[i].id == idEliminar) {
                        vehiculos[i].estado = 0;
                        if (actualizarEstado(idEliminar, 0)) {
                            printf("Estado actualizado en archivo.\n");
                        }
                        printf("Vehiculo marcado como no disponible.\n");
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("No se encontro un vehiculo con ese ID.\n");
                }
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
