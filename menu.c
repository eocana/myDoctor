/*****************
*
* @Propòsit: Todos los menus del programa
* @Autor/s: Eric Ocaña Segura
* @Data de creació: 14/03/2023
* @Data de l’última modificació: 25/04/2023
*
****************/
#include <stdio.h>
#include <string.h>
#include "menu.h"

/*****************
*
* @Finalitat: Muestra el menú principal cuando ya se ha cargado
* @Paràmetres:
* @Retorn: Retorna la opción del menu que el usuario ha escogido
*
****************/
int mostrar_menu() {
    int opcion;
    int error = 1;
    do {
        printf("1. Show diseases | 2. Load research advances | 3. Help me! | 4. Quit");
        printf("\nEnter option:");
        fflush(stdin);
        if (scanf("%d", &opcion) == 1) { //nos aseguramos de que escribe un numero
            error = 0;
        } else {
            printf("ERROR: Wrong option\n");
            fflush(stdin); //limpiamos
        }
    } while (error);

    return opcion;
}

/*****************
*
* @Finalitat: Pide el nombre del archivo
* @Paràmetres: nombre_archivo: el nombre del archivo que contiene la información de las enfermedades
* @Retorn: void
*
****************/
void pedir_nombre_archivo(char nombre_archivo[]) {
    printf("Introduce el nombre del archivo:");
    scanf("%s", nombre_archivo);
}

