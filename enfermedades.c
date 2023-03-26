/***********************************************
* @Propòsit: Implementar las funciones necesarias para cargar y manipular información sobre enfermedades y síntomas.
* @Autor/s: Eric Ocaña Segura
* @Data de creació: 18/03/2023
* @Data de l’última modificació: 26/03/2023
************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enfermedades.h"
#include <stdio.h>
#include <string.h>

#define MAX_ENFERMEDADES 30
#define MAX_SINTOMAS 10
#define MAX_CHAR 50
#define MAX_LINE 100

/***********************************************
*
* @Finalitat: Buscar una enfermedad en el array de enfermedades.
* @Paràmetres: nombre: el nombre de la enfermedad a buscar.
*              enfermedades: el array de estructuras Enfermedad.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: El índice de la enfermedad en el array si se encuentra, -1 en caso contrario.
*
************************************************/
int buscar_enfermedad(char nombre[], Enfermedad enfermedades[], int num_enfermedades) {
    int i;
    for (i = 0; i < num_enfermedades; i++) {
        if (strcmp(nombre, enfermedades[i].nombre) == 0) {
            return i;
        }
    }
    return -1;
}

/***********************************************
*
* @Finalitat: Buscar un síntoma en el array de síntomas.
* @Paràmetres: nombre: el nombre del síntoma a buscar.
*              sintomas: el array de estructuras Sintoma.
*              num_sintomas: el número de elementos en el array de sintomas.
* @Retorn: El índice del síntoma en el array si se encuentra, -1 en caso contrario.
*
************************************************/
int buscar_sintoma(char nombre[], Sintoma sintomas[], int num_sintomas) {
    int i;
    for (i = 0; i < num_sintomas; i++) {
        if (strcmp(nombre, sintomas[i].sintoma) == 0) {
            return i;
        }
    }
    return -1;
}

/***********************************************
*
* @Finalitat: Cargar las enfermedades desde un archivo y almacenarlas en un array de estructuras.
* @Paràmetres: nombre_archivo: el nombre del archivo que contiene la información de las enfermedades.
* @Retorn: Un struct CargaEnfermedades que contiene un array de estructuras Enfermedad con la información cargada del archivo.
*
************************************************/
CargaEnfermedades cargar_enfermedades(char nombre_archivo[]) {
    CargaEnfermedades resultado;
    resultado.num_enfermedades = 0;
    char linea[MAX_CHAR];
    FILE* archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        printf("ERROR: Disease file not found");
        return resultado;
    }

    while (fgets(linea, MAX_CHAR, archivo) != NULL) {
        Enfermedad enfermedad;
        enfermedad.num_sintomas = 0;
        Sintoma nuevo_sintoma;
        char sintoma[MAX_CHAR];
        int num_sintomas, i, j, len, relevancia;

        // Eliminar el caracter '\n' de la línea leída
        len = strlen(linea);
        if (linea[len - 1] == '\n') {
            linea[len - 1] = '\0';
        }

//        printf("Linea leida: %s\n", linea);
        strcpy(enfermedad.nombre, linea);

        fgets(linea, MAX_CHAR, archivo);

        len = strlen(linea);
        if (linea[len - 1] == '\n') {
            linea[len - 1] = '\0';
        }

        // Leer número de síntomas
        num_sintomas = 0;
        i = 0;
        while (linea[i] != '\0') {
            if (linea[i] >= '0' && linea[i] <= '9') {
                num_sintomas = num_sintomas * 10 + (linea[i] - '0');
            }
            i++;
        }

        // Leer síntomas
        for (i = 0; i < num_sintomas; i++) {
            fgets(linea, MAX_CHAR, archivo);

            len = strlen(linea);
            if (linea[len - 1] == '\n') {
                linea[len - 1] = '\0';
            }

            // Leer sintoma
            j = 0;
            while (linea[j] != '(' && linea[j] != '\0') {
                sintoma[j] = linea[j];
                j++;
            }
            sintoma[j] = '\0';

            // Leer relevancia
            relevancia = 0;
            j++;
            while (linea[j] != ')' && linea[j] != '\0') {
                if (linea[j] >= '0' && linea[j] <= '9') {
                    relevancia = relevancia * 10 + (linea[j] - '0'); //La multiplicación por 10 se realiza para poder
                                                                    // ir acumulando el valor numérico de la relevancia
                }
                j++;
            }

            // Crear nuevo sintoma
            strcpy(nuevo_sintoma.sintoma, sintoma);
            nuevo_sintoma.relevancia = relevancia;

            enfermedad.sintomas[enfermedad.num_sintomas++] = nuevo_sintoma;
        }

        resultado.enfermedades[resultado.num_enfermedades++] = enfermedad;
//        printf("Num enferm: %d\n", resultado.num_enfermedades);
    }

   /* for (int i = 0; i < resultado.num_enfermedades; i++) {
        printf("Enfermedad %d: %s (%d sintomas)\n", i+1, resultado.enfermedades[i].nombre, resultado.enfermedades[i].num_sintomas);
    }*/

    fclose(archivo);
    printf("Welcome to myDoctor!");
    printf("\n");

    return resultado;
}



/***********************************************
*
* @Finalitat: Mostrar la información de todas las enfermedades en el array de enfermedades.
* @Paràmetres: enfermedades: el array de estructuras Enfermedad.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: void.
*
************************************************/
void mostrar_enfermedades(Enfermedad enfermedades[], int num_enfermedades) {
    int i, j;

    for (i = 0; i < num_enfermedades; i++) {
        printf("%s (", enfermedades[i].nombre);
        for (j = 0; j < enfermedades[i].num_sintomas; j++) {
            printf("%s#%d", enfermedades[i].sintomas[j].sintoma, enfermedades[i].sintomas[j].relevancia);
            if (j != enfermedades[i].num_sintomas - 1) {
                printf(" | ");
            }
        }
        printf(")\n");
    }
}

/***********************************************
*
* @Finalitat: Actualizar la información de las enfermedades a partir de un archivo.
* @Paràmetres: nombre_archivo: el nombre del archivo que contiene la información actualizada de los síntomas.
*              enfermedades: el array de estructuras Enfermedad.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: void.
*
************************************************/
void actualizar_enfermedades(char nombre_archivo[], Enfermedad enfermedades[], int num_enfermedades) {
    FILE* archivo = fopen(nombre_archivo, "rb");
    int num_ignoradas = 0;
    int num_actualizadas = 0;
    int num_anadidas = 0;
    int idx_enfermedad = -1;
    int idx_sintoma = -1;
    FileDisease registro;

    if (archivo == NULL) {
        printf("ERROR: Research file not found\n");
    }else{
        while (fread(&registro, sizeof(FileDisease), 1, archivo) == 1) {
            idx_enfermedad = buscar_enfermedad(registro.disease, enfermedades, num_enfermedades);
            if (idx_enfermedad != -1) {
                idx_sintoma = buscar_sintoma(registro.symptom, enfermedades[idx_enfermedad].sintomas, enfermedades[idx_enfermedad].num_sintomas);
                if (idx_sintoma != -1) {
                    if (registro.relevance != enfermedades[idx_enfermedad].sintomas[idx_sintoma].relevancia) {
                        enfermedades[idx_enfermedad].sintomas[idx_sintoma].relevancia = registro.relevance;
                        num_actualizadas++;
                    }
                } else {
                    Sintoma sintoma;
                    strcpy(sintoma.sintoma, registro.symptom);
                    sintoma.relevancia = registro.relevance;
                    enfermedades[idx_enfermedad].sintomas[enfermedades[idx_enfermedad].num_sintomas++] = sintoma;
                    num_anadidas++;
                }
            } else {
                num_ignoradas++;
            }
        }

        fclose(archivo);

        printf("%d diseases ignored\n", num_ignoradas);
        printf("%d symptoms updated\n", num_actualizadas);
        printf("%d symptons added\n", num_anadidas);
        printf("\n");
    }


}

/***********************************************
*
* @Finalitat: Pedir al usuario una lista de síntomas y mostrar las enfermedades posibles según esos síntomas.
* @Paràmetres: enfermedades: el array de estructuras Enfermedad.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: void.
*
************************************************/
void help_me(Enfermedad enfermedades[], int num_enfermedades) {
    
    char sintomas[MAX_CHAR];
    int idx_sintoma = 0;
    int idx_char = 0;
    int num_sintomas = 1;
    int k = 0, j = 0, i = 0, u = 0, a = 0;

    printf("Enter your symptoms:");
    scanf("%s", sintomas);

    // Obtener número de síntomas del usuario
    for (i = 0; sintomas[i] != '\0'; i++) {
        if (sintomas[i] == '+') {
            num_sintomas++;
        }
    }


    // Crear array de síntomas del usuario
    SintomaUsuario usuario_sintomas[num_sintomas];

    //bucle que separa los sintomas en base +
    for (i = 0; sintomas[i] != '\0'; i++) {
        if (sintomas[i] == '+') {
            usuario_sintomas[idx_sintoma].nombre[idx_char] = '\0';
            usuario_sintomas[idx_sintoma].relevancia = 0;
            idx_sintoma++;
            idx_char = 0;
        } else {
            usuario_sintomas[idx_sintoma].nombre[idx_char] = sintomas[i];
            usuario_sintomas[idx_sintoma].relevancia = 0;
            idx_char++;
        }
    }
    //nos asseguramos que el final se ponga \0
    usuario_sintomas[idx_sintoma].nombre[idx_char] = '\0';
    usuario_sintomas[idx_sintoma].relevancia = 0;

//    printf("Primer sintoma: %s\n", usuario_sintomas[0].nombre);
//    printf("Segundo sintoma: %s\n", usuario_sintomas[1].nombre);

    // Obtener puntuación de cada enfermedad
    int puntuaciones[num_enfermedades];
    for (u = 0; u < num_enfermedades; u++) {
        puntuaciones[u] = 0;
//        printf("Enfermedad sistema: %s\n", enfermedades[u].nombre);
        for (j = 0; j < num_sintomas; j++) {
//            printf("Usuario: %s\n",usuario_sintomas[j].nombre);

            for (k = 0; k < enfermedades[u].num_sintomas; k++) {
//                printf("Vuelta %d k Usuario sintoma: %s\n", k,usuario_sintomas[j].nombre);
//                printf("Vuelta %d k - Sistema sintoma: %s\n", k, enfermedades[u].sintomas[k].sintoma);
                int len = strlen(enfermedades[u].sintomas[k].sintoma);
                for (a = 0; a < len; a++) {
                    if (enfermedades[u].sintomas[k].sintoma[a] == ' ') {
                        enfermedades[u].sintomas[k].sintoma[a] = '\0';
                        a = len;
                    }
                }
                if (strcmp(usuario_sintomas[j].nombre, enfermedades[u].sintomas[k].sintoma) == 0) {
//                    printf("\n\nSumo en la vuelta %d\n", k);
//                    printf("%s - %s\n\n", usuario_sintomas[j].nombre,enfermedades[u].sintomas[k].sintoma );
                    puntuaciones[u] += enfermedades[u].sintomas[k].relevancia;
                }
            }
        }
    }

    // Ordenar enfermedades por puntuación (de mayor a menor) [ordenamiento burbuja]
    for (i = 0; i < num_enfermedades - 1; i++) {
        for (j = 0; j < num_enfermedades - i - 1; j++) {
            if (puntuaciones[j+1] > puntuaciones[j]) {

                // Intercambiar puntuaciones
                int temp_puntuacion = puntuaciones[j];
                puntuaciones[j] = puntuaciones[j+1];
                puntuaciones[j+1] = temp_puntuacion;

                // Intercambiar enfermedades
                Enfermedad temp_enfermedad = enfermedades[j];
                enfermedades[j] = enfermedades[j+1];
                enfermedades[j+1] = temp_enfermedad;
            }
        }
    }

    // Mostrar enfermedades con puntuación positiva

    int num_positivas = 0;
    for (i = 0; i < num_enfermedades; i++) {

        if (puntuaciones[i] > 0) {

            num_positivas++;

            if(num_positivas == 1){
                printf("Most probable diseases:\n");
            }

            printf("Total relavance %d: %s\n", puntuaciones[i], enfermedades[i].nombre);
        }
        if (num_positivas == 0) {
            i = num_enfermedades;
            printf("No diseases found!\n");
        }
    }
    printf("\n");
}
