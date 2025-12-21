#include <stdio.h>
#include "funciones.h"
int main(int argc, char const *argv[])
{

int opcion, continuar;

    do
    {
        menu();
        opcion = leerInteger();
        switch (opcion)
        {
        case 1:

            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
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
