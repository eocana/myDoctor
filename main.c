/***********************************************
* @Propòsit: Función principal del programa que implementa el menú principal y llama a otras funciones según la opción elegida por el usuario.
* @Autor/s: Eric Ocaña Segura
* @Data de creació: 01/04/2023
* @Data de l’última modificació: 23/04/2023
************************************************/
#include <stdio.h>
#include "menu.h"
#include "enfermedades.h"

int main() {
    int opcion;
    char nombre_archivo[50];
    char nombre_bin[50];
    CargaEnfermedades totalEnfermedades;

    printf("Introduzca el nombre del archivo de enfermedades:");
    scanf("%s", nombre_archivo);

    cargarEnfermedades(&totalEnfermedades, nombre_archivo);

    if (totalEnfermedades.num_enfermedades == NULL ) { //Si es 0 (lo cual significa error) se acaba el programa
        return 1;
    }

     /*
          for (int i = 0; i < totalEnfermedades.num_enfermedades; i++) {
            printf("Enfermedad %d: %s (%d sintomas)\n", i+1, totalEnfermedades.enfermedades[i].nombre, totalEnfermedades.enfermedades[i].num_sintomas);
          }

     */

    do {

        opcion = mostrar_menu(); // guardamos la opcion del usuario

        switch(opcion) {
            case 1:
                mostrarEnfermedades(&totalEnfermedades); //mostrar como piden
                break;
            case 2:
                pedir_nombre_archivo(nombre_bin); //obtener nombre del bin
                actualizarEnfermedades(nombre_bin, &totalEnfermedades); //actualizamos
                break;
            case 3:
                helpMe(totalEnfermedades.enfermedades, totalEnfermedades.num_enfermedades); //mostrar enfermedades en base sintomas
                break;
            case 4:
                printf("\nStay healthy!");
                break;
            default:
                printf("ERROR: Wrong option\n");
        }
    } while(opcion != 4);

    return 0;
}
