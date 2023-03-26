/***********************************************
* @Propòsit: Función principal del programa que implementa el menú principal y llama a otras funciones según la opción elegida por el usuario.
* @Autor/s: Eric Ocaña Segura
* @Data de creació: 18/03/2023
* @Data de l’última modificació: 26/03/2023
************************************************/
#include <stdio.h>
#include "menu.h"
#include "enfermedades.h"

int main() {
    int opcion;
    char nombre_archivo[50];
    char nombre_bin[50];
    CargaEnfermedades enfermedades;

    printf("Introduzca el nombre del archivo de enfermedades:");
    scanf("%s", nombre_archivo);

    enfermedades = cargar_enfermedades(nombre_archivo);
    if (enfermedades.num_enfermedades == 0 ) { //Si es 0 (lo cual significa error) se acaba el programa
        return 1;
    }

    do {

        opcion = mostrar_menu(); // guardamos la opcion del usuario

        switch(opcion) {
            case 1:
                mostrar_enfermedades(enfermedades.enfermedades, enfermedades.num_enfermedades); //mostrar como piden
                break;
            case 2:
                pedir_nombre_archivo(nombre_bin); //obtener nombre del bin
                actualizar_enfermedades(nombre_bin,enfermedades.enfermedades, enfermedades.num_enfermedades); //actualizamos
                break;
            case 3:
                help_me(enfermedades.enfermedades, enfermedades.num_enfermedades); //mostrar enfermedades en base sintomas
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
