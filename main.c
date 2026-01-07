#include <stdio.h>
#include <string.h>
#include "funciones.h"
int main(int argc, char const *argv[])
{

    int opcion, opc, continuar, indix = 0;
    Vehiculo vehiculos[MAX_VEHICULOS]; // Arreglo para almacenar vehiculos
    int contador = 0, contadorPro = 0;                  // Contador de vehiculos almacenados
    char marca[MAX_MARCAS][MAX];
    int idOpc;
    float presupuesto, ventaTotal;
    
    // Cargar datos desde los archivos al inicio del programa
    presupuesto = leerPresupuesto();
    /* ventaTotal = leerGanancias(); */
    contador = cargarVehiculos(vehiculos, MAX_VEHICULOS);
    contadorPro = cargarVehiculos(vehiculos, MAX_VEHICULOS);   //Para evitar problemas con id
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
                printf("No hay vehiculos disponibles.\n");
            }
            else
            {
                listarVehiculosDisponibles();
            }

            break;
        case 2:
            if (contador >= MAX_VEHICULOS)
            {
                printf("No se pueden agregar mas vehiculos.\n");
                break;
            }
            if (indix == 0)
            {
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
                while (vehiculos[contador].anio <1900 || vehiculos[contador].anio > 2026)
                {
                    printf("Anio invalido. Ingrese un anio entre 1900 y 2026.\n>> ");
                    vehiculos[contador].anio = leerInteger();
                }

                printf("Ingrese el precio del vehiculo (USD): \n>> ");
                vehiculos[contador].precio = leerFloat();

                presupuesto += vehiculos[contador].precio;
                guardarPresupuesto(presupuesto);


                printf("Ingrese si es usado (1: usado, 0: nuevo): \n>> ");
                vehiculos[contador].usado = leerInteger();

                vehiculos[contador].estado = 1;        // Disponible por defecto
                vehiculos[contador].id = contadorPro + 1; // Asignar ID
                printf("Marcas disponibles:\n");
                for (int i = 0; i < indix; i++)
                {
                    printf("%d. %s\n", i + 1, marca[i]);
                }
                printf("Seleccione la marca del vehiculo:\n>> ");
                opc = (leerInteger()) - 1;
                while (opc < 0 || opc >= indix)
                {
                    printf("Elija una opcion dentro del menu, intentelo nuevamente.\n>> ");
                    opc = leerInteger();
                }
                strcpy(vehiculos[contador].marca, marca[opc]);

                registrarUno(&vehiculos[contador]);
                printf("Activo total acumulado: %.2f USD\n", presupuesto);
                contador++;
                contadorPro++;
                printf("Vehiculo agregado exitosamente!\n");
            }
            else if (continuar == 2)
            {
                if (contador == 0)
                {
                    printf("No hay vehiculos para eliminar.\n");
                    break;
                }
                listarVehiculosDisponibles();
                printf("Ingrese el ID del vehiculo a marcar como no disponible: \n>> ");
                int idEliminar = leerInteger();
                int encontrado = 0;

                for (int i = 0; i < contador; i++)
                {
                    if (vehiculos[i].id == idEliminar)
                    {
                        vehiculos[i].estado = 0;
                        if (actualizarEstado(idEliminar, 0))
                        {
                            printf("Estado actualizado en archivo.\n");
                        }
                        printf("Vehiculo marcado como no disponible.\n");
                        encontrado = 1;
                        contador--;
                        break;
                    }
                }

                if (!encontrado)
                {
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
                guardarMarcas(marca, indix); // Guardar las marcas en el archivo
            }
            break;
        case 4:
        if (contador == 0)
            {
                printf("No hay vehículos disponibles para buscar.\n");
                break;
            }
            printf("Como desea buscar el vehiculo?\n");
            printf("1. Por ID\n");
            printf("2. Por Marca (Proximamente)\n");
            printf("3. Por anio\n");
            printf("4. Por presupuesto\n");
            printf("5. Preferencial\n>> ");
            continuar = leerInteger();
            while (continuar > 5 || continuar < 1)
            {
                printf("Opcion invalida. Intente nuevamente.\n>> ");
                continuar = leerInteger();
            }
            
            switch (continuar)
            {
            case 1:
            buscarVehiculoPorID(leerInteger());
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            }
            break;
        case 5:
            if (contador == 0)
            {
                        printf("No hay vehiculos para vender.\n");
                        break;
            }
            listarVehiculosDisponibles();
            printf("Ingrese el ID del vehiculo a vender: \n>> ");
            idOpc = leerInteger();
            registrarVenta(idOpc);

            
            break;
        case 6: //Mostrar ganancias y ventas totales
            mostrarVentas ();

            break;
        case 7:
            printf("Gracias...\n");
            break;

        default:
            printf("Opcion invalida. Intente nuevamente.\n");
            break;
        }

    } while (opcion != 7);

    return 0;
}
