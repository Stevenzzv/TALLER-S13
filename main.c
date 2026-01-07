#include <stdio.h>
#include <string.h>
#include "funciones.h"
int main(int argc, char const *argv[])
{

    int opcion, opc, continuar, indix = 0;
    Vehiculo vehiculos[MAX_VEHICULOS]; // Arreglo para almacenar vehiculos
    int contador = 0;                  // Contador de vehiculos almacenados
    char marca[MAX_MARCAS][MAX];
    int idOpc;
    float presupuesto, ventaTotal;

    // Cargar datos desde los archivos al inicio del programa
    /* presupuesto = leerPresupuesto(); */
    /* ventaTotal = leerGanancias(); */
    contador = cargarVehiculos(vehiculos, MAX_VEHICULOS);
    indix = cargarMarcas(marca, MAX_MARCAS);

    printf("Se cargaron %d vehiculos y %d marcas desde los archivos.\n", contador, indix);

    do
    {
        menu();
        opcion = leerInteger();
        switch (opcion)
        {
        case 1: // Listar vehiculos disponibles
            if (contador == 0)
            {
                printf("\nNo hay vehiculos disponibles.\n\n");
            }
            else
            {
                listarVehiculosDisponibles();
            }

            break;
        case 2:
            if (indix == 0)
            {
                printf("\nNo hay marcas de vehiculo agregadas.\n\n");
                break;
            }
            printf("\n+====================================+\n");
            printf("|           Que desea hacer?         |\n");
            printf("+====================================+\n");
            printf("| 1. Agregar vehiculo                |\n");
            printf("| 2. Eliminar vehiculo               |\n");
            printf("+====================================+\n");
            printf(">> ");
            continuar = leerInteger();
            if (continuar == 1)
            {
                if (contador >= MAX_VEHICULOS)
                {
                    printf("\nMaximo de vehiculos alcanzado. \n");
                    printf("No se pueden agregar mas vehiculos.\n\n");
                    break;
                }
                printf("\nIngrese el modelo del vehiculo: \n>> ");
                leerChar(vehiculos[contador].modelo, MAX);

                printf("\nIngrese el anio del vehiculo: \n>> ");
                vehiculos[contador].anio = leerInteger();
                while (vehiculos[contador].anio < 1900 || vehiculos[contador].anio > 2026)
                {
                    printf("\nAnio invalido. Ingrese un anio entre 1900 y 2026.\n>> ");
                    vehiculos[contador].anio = leerInteger();
                }

                printf("\nIngrese el precio del vehiculo (USD): \n>> ");
                vehiculos[contador].precio = leerFloat();

                /*                 presupuesto += vehiculos[contador].precio;
                                guardarPresupuesto(presupuesto); */

                printf("\nIngrese si es usado (1: usado, 0: nuevo): \n>> ");
                vehiculos[contador].usado = leerInteger();

                vehiculos[contador].estado = 1;        // Disponible por defecto
                vehiculos[contador].id = contador + 1; // Asignar ID
                printf("\n-------------------------------------+\n\n");
                printf("Marcas disponibles:\n\n");
                for (int i = 0; i < indix; i++)
                {
                    printf("| %d. %s\n", i + 1, marca[i]);
                }
                printf("\n-------------------------------------+\n\n");
                printf("Seleccione la marca del vehiculo:\n>> ");
                opc = (leerInteger()) - 1;
                while (opc < 0 || opc >= indix)
                {
                    printf("\nElija una opcion dentro del menu, intentelo nuevamente.\n>> ");
                    opc = (leerInteger()) - 1;
                }
                strcpy(vehiculos[contador].marca, marca[opc]);

                registrarUno(&vehiculos[contador]);
                /* printf("Activo total acumulado: %.2f USD\n", presupuesto); */
                contador++;
                printf("\n+====================================+\n");
                printf("|   Vehiculo agregado exitosamente!  |\n");
                printf("+====================================+\n\n");
            }
            else if (continuar == 2)
            {
                if (contador == 0)
                {
                    printf("\nNo hay vehiculos para eliminar.\n\n");
                    break;
                }
                printf("\n");
                listarVehiculosDisponibles();
                printf("Ingrese el ID del vehiculo a eliminar: \n>> ");
                int idModificar = leerInteger();
                int encontrado = 0;

                for (int i = 0; i < contador; i++)
                {
                    if (vehiculos[i].id == idModificar)
                    {
                        vehiculos[i].estado = 0;
                        if (actualizarEstado(idModificar, 0))
                        {
                            printf("\n+====================================+\n");
                            printf("|    Estado actualizado en archivo.    |\n");
                            printf("| Vehiculo marcado como no disponible. |\n");
                            printf("+====================================+\n\n");
                        }
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado)
                {
                    printf("\nNo se encontro un vehiculo con ese ID.\n\n");
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
                printf("\nNo se pueden agregar mas marcas.\n\n");
            }
            else
            {
                printf("\n+====================================+\n\n");
                printf("Ingrese el nombre de la marca a agregar.\n>> ");
                leerChar(marca[indix], MAX);
                printf("\nMarca agregada exitosamente.\n\n");

                indix++;
                guardarMarcas(marca, indix); // Guardar las marcas en el archivo
            }
            break;
        case 4:
            if (contador == 0)
            {
                printf("\nNo hay vehiculos disponibles para buscar.\n\n");
                break;
            }
            printf("\n+====================================+\n");
            printf("|                BUSCAR              |\n");
            printf("+====================================+\n");
            printf("| 1. Por ID                          |\n");
            printf("| 2. Por Marca                       |\n");
            printf("| 3. Por anio                        |\n");
            printf("| 4. Por precio                      |\n");
            printf("| 5. Preferencial                    |\n");
            printf("+====================================+\n");
            printf(">> ");
            continuar = leerInteger();
            while (continuar > 5 || continuar < 1)
            {
                printf("Opcion invalida. Intente nuevamente.\n>> ");
                continuar = leerInteger();
            }

            switch (continuar)
            {
            case 1:
                printf("\nIngrese un ID\n>> ");
                buscarVehiculoPorID((leerInteger()));
                break;
            case 2:
                printf("\nIngrese la marca a buscar\n>> ");
                char marcaBuscada[MAX];
                leerChar(marcaBuscada, MAX);
                buscarVehiculoPorMarca(marcaBuscada);
                break;
            case 3:
                printf("\nIngrese el anio a buscar\n>> ");
                buscarVehiculoPorAnio(leerInteger());
                break;
            case 4:
                printf("\nIngrese el precio minimo\n>> ");
                float precioMin = leerFloat();
                printf("\nIngrese el precio maximo\n>> ");
                float precioMax = leerFloat();
                buscarVehiculoPorPrecio(precioMin, precioMax);
                break;
            case 5:
                printf("\nIngrese el ID\n>> ");
                int id = leerInteger();
                printf("\nIngrese la marca\n>> ");
                char marca[MAX];
                leerChar(marca, MAX);
                printf("\nIngrese el anio\n>> ");
                int anio = leerInteger();
                printf("\nIngrese el precio maximo\n>> ");
                float precio = leerFloat();
                buscarVehiculoPreferencial(id, marca, anio, precio);
                break;
            }
            break;
        case 5:
            if (contador == 0)
            {
                printf("\nNo hay vehiculos para vender.\n\n");
                break;
            }
            listarVehiculosDisponibles();
            printf("Ingrese el ID del vehiculo a vender: \n>> ");
            idOpc = leerInteger();
            registrarVenta(idOpc);

            break;
        case 6: // Mostrar ganancias y ventas totales
            mostrarVentas();

            break;
        case 7:
            printf("\n+====================================+\n");
            printf("|            ...Gracias...           |\n");
            printf("+====================================+\n");
            break;

        default:
            printf("Opcion invalida. Intente nuevamente.\n");
            break;
        }

    } while (opcion != 7);

    return 0;
}
