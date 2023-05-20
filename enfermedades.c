/***********************************************
* @Propòsit: Implementar las funciones necesarias para cargar y manipular información sobre enfermedades y síntomas.
* @Autor/s: Eric Ocaña Segura
* @Data de creació: 01/04/2023
* @Data de l’última modificació: 23/04/2023
************************************************/

#include "enfermedades.h"

#define MAX_ENFERMEDADES 30
#define MAX_SINTOMAS 10
#define MAX_CHAR 50
#define MAX_LINE 100

/**
 * Función tipica de trim para eliminar espacios en blanco al principio y al final de una cadena
 * Porque estaba tenienndo problemas de espacios y el hacer '\0' no me funcionaba
 * @param str
 */
void trim(char* str) {
    int start = 0;
    int end = strlen(str) - 1;

    // Buscar el primer carácter no espaciado desde el inicio
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n') {
        start++;
    }

    // Buscar el último carácter no espaciado desde el final
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }

    // Mover los caracteres no espaciados al inicio de la cadena
    int i;
    for (i = 0; i <= end - start; i++) {
        str[i] = str[start + i];
    }

    // Agregar el carácter nulo al final de la cadena
    str[i] = '\0';
}



/***********************************************
*
* @Finalitat: Buscar una enfermedad en el array de enfermedades.
* @Paràmetres: nombre: el nombre de la enfermedad a buscar.
*              *totalEnfermedades: puntero que lleva a la structura donde estan todas las enfermedades.
* @Retorn: El índice de la enfermedad en el array si se encuentra, -1 en caso contrario.
*
************************************************/
int buscarEnfermedad(char nombre[], CargaEnfermedades* totalEnfermedades) {
    for (int i = 0; i < totalEnfermedades->num_enfermedades; i++) {
        if (strcmp(nombre, totalEnfermedades->enfermedades[i].nombre) == 0) {
            return i;
        }
    }
    return -1;
}

/***********************************************
*
* @Finalitat: Buscar un síntoma en el array de síntomas.
* @Paràmetres: nombre: el nombre del síntoma a buscar.
*              *sintomas: puntero que lleva a la structura donde estan todos los sintomas.
* @Retorn: El índice del síntoma en el array si se encuentra, -1 en caso contrario.
*
************************************************/
int buscarSintoma(char sintoma[], LinkedList* sintomas) {
    LINKEDLIST_goToHead(sintomas);
    while (!LINKEDLIST_isAtEnd(*sintomas)) {

        if (strcmp(LINKEDLIST_get(sintomas).sintoma, sintoma) == 0) {
            return 1;
        }

        LINKEDLIST_next(sintomas);
    }
    return -1;
}


/***********************************************
*
* @Finalitat: Cargar las enfermedades desde un archivo y almacenarlas en un array de estructuras.
* @Paràmetres: *totalEnfermedades: structura donde se guardara de forma dinamica
 *              nombre_archivo: el nombre del archivo que contiene la información de las enfermedades.
* @Retorn: void
*
************************************************/
void cargarEnfermedades(CargaEnfermedades* totalEnfermedades, char nombre_archivo[]) {
    char linea[MAX_CHAR];
    FILE* archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        printf("ERROR: Disease file not found");
        return;
    }

    // Leer número de enfermedades en el archivo
    fgets(linea, MAX_CHAR, archivo);
    int num_enfermedades = atoi(linea);

    // Asignar memoria para el arreglo de enfermedades
    totalEnfermedades->enfermedades = (Disease*)malloc(sizeof(Disease) * num_enfermedades);
    totalEnfermedades->num_enfermedades = num_enfermedades;

    // Leer cada enfermedad del archivo
    for (int i = 0; i < num_enfermedades; i++) {

        Disease enfermedad;
        enfermedad.num_sintomas = 0;
        enfermedad.sintomas = LINKEDLIST_Create(); // Crear la lista de síntomas para la enfermedad actual
        LINKEDLIST_goToHead(&enfermedad.sintomas); // Poner el puntero de la lista al inicio
        // Leer nombre de la enfermedad
        fgets(linea, MAX_CHAR, archivo);
        int len = strlen(linea);

        if (linea[len - 1] == '\n') {
            linea[len - 1] = '\0';
        }

        strcpy(enfermedad.nombre, linea);

        // Leer número de síntomas
        fgets(linea, MAX_CHAR, archivo);
        int num_sintomas = atoi(linea);

        // Leer cada síntoma de la enfermedad
        for (int j = 0; j < num_sintomas; j++) {
            // Leer nombre del síntoma y relevancia
            char sintoma[MAX_CHAR];
            int relevancia;
            fgets(linea, MAX_CHAR, archivo);

            len = strlen(linea);

            if (linea[len - 1] == '\n') {
                linea[len - 1] = '\0';
            }

            sscanf(linea, "%[^()] (%d)", sintoma, &relevancia);

            // Crear nuevo síntoma
            Sintoma symptom;
            strcpy(symptom.sintoma, sintoma);
            trim(symptom.sintoma);
            symptom.relevancia = relevancia;

            // Agregar síntoma a la lista de síntomas de la enfermedad
            LINKEDLIST_add(&(enfermedad.sintomas), symptom);
            enfermedad.num_sintomas++;
        }

        // Agregar enfermedad al arreglo totalEnfermedades
        totalEnfermedades->enfermedades[i] = enfermedad;
    }

    fclose(archivo);
    printf("Welcome to myDoctor!\n\n");

}

/***********************************************
*
* @Finalitat: Mostrar la información de todas las enfermedades en el array de enfermedades.
* @Paràmetres: *totalEnfermedades: puntero que lleva a la structura donde estan todas las enfermedades.
*
* @Retorn: void.
*
************************************************/
void mostrarEnfermedades(CargaEnfermedades* totalEnfermedades) {
    for (int i = 0; i < totalEnfermedades->num_enfermedades; i++) {
        Disease enfermedad = totalEnfermedades->enfermedades[i];
        printf("%s (", enfermedad.nombre);

        LinkedList sintomas = enfermedad.sintomas;
        LINKEDLIST_goToHead(&sintomas);

        while (!LINKEDLIST_isAtEnd(sintomas)) {
            Sintoma sintoma = LINKEDLIST_get(&sintomas);
            printf("%s#%d", sintoma.sintoma, sintoma.relevancia);

            LINKEDLIST_next(&sintomas);
            if (!LINKEDLIST_isAtEnd(sintomas)) {
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
*              *totalEnfermedades: puntero que lleva a la structura donde estan todas las enfermedades.
* @Retorn: void.
*
************************************************/
void actualizarEnfermedades(char nombre_archivo[], CargaEnfermedades* totalEnfermedades) {
    FILE* archivo = fopen(nombre_archivo, "rb");
    int num_ignoradas = 0;
    int num_actualizadas = 0;
    int num_anadidas = 0;
    int idx_enfermedad = -1;
    int idx_sintoma = -1;
    FileDisease registro;

    if (archivo == NULL) {
        printf("ERROR: Research file not found\n");
    } else {
        while (fread(&registro, sizeof(FileDisease), 1, archivo) == 1) {
            idx_enfermedad = buscarEnfermedad(registro.disease, totalEnfermedades);
            if (idx_enfermedad != -1) {
                Disease* enfermedad = &(totalEnfermedades->enfermedades[idx_enfermedad]);
                idx_sintoma = buscarSintoma(registro.symptom, &enfermedad->sintomas);

                if (idx_sintoma != -1) {
                    // Actualizar relevancia del síntoma existente
                    LINKEDLIST_goToHead(&(enfermedad->sintomas));

                    for (int i = 0; i <= idx_sintoma; i++) {
                        LINKEDLIST_next(&(enfermedad->sintomas));
                    }

                    enfermedad->sintomas.previous->next->element.relevancia = registro.relevance;
                    num_actualizadas++;

                } else {
                    // Agregar nuevo síntoma a la enfermedad
                    Sintoma sintoma;
                    strcpy(sintoma.sintoma, registro.symptom);
                    sintoma.relevancia = registro.relevance;
                    LINKEDLIST_add(&(enfermedad->sintomas), sintoma);
                    num_anadidas++;
                }
            } else {
                num_ignoradas++;
            }
        }

        fclose(archivo);

        printf("%d diseases ignored\n", num_ignoradas);
        printf("%d symptoms updated\n", num_actualizadas);
        printf("%d symptoms added\n", num_anadidas);
        printf("\n");
    }
}


/***********************************************
*
* @Finalitat: Pedir al usuario una lista de síntomas y mostrar las enfermedades posibles según esos síntomas.
* @Paràmetres: totalEnfermedades: puntero que lleva a la structura donde estan todas las enfermedades.
*
* @Retorn: void.
*
************************************************/
void helpMe(CargaEnfermedades* totalEnfermedades) {
    char sintomas[MAX_CHAR];
    int num_sintomas = 1;
    int idx_sintoma = 0;
    int idx_char = 0;
    Sintoma nuevo_sintoma;
    LinkedList usuario_sintomas = LINKEDLIST_Create();

    // Pedir síntomas al usuario
    printf("Enter your symptoms: ");
    scanf("%s", sintomas);

    // Obtener número de síntomas del usuario
    for (int i = 0; sintomas[i] != '\0'; i++) {
        if (sintomas[i] == '+') {
            num_sintomas++;
        }
    }


    for (int i = 0; sintomas[i] != '\0'; i++) {
        if (sintomas[i] == '+') {
            nuevo_sintoma.sintoma[idx_char] = '\0';
            nuevo_sintoma.relevancia = 0;
            trim(nuevo_sintoma.sintoma);
            printf("Nuevo síntoma: %s\n", nuevo_sintoma.sintoma);
            LINKEDLIST_add(&usuario_sintomas, nuevo_sintoma);
            idx_char = 0;
        } else {
            nuevo_sintoma.sintoma[idx_char] = sintomas[i];
            idx_char++;
        }
    }

// Añadir el último síntoma después del último '+'
    if (idx_char > 0) {
        nuevo_sintoma.sintoma[idx_char] = '\0';
        nuevo_sintoma.relevancia = 0;
        trim(nuevo_sintoma.sintoma);
        printf("Nuevo síntoma 2: %s\n", nuevo_sintoma.sintoma);
        LINKEDLIST_add(&usuario_sintomas, nuevo_sintoma);
    }


    // Obtener puntuación de cada enfermedad
    int* puntuaciones = (int*)malloc(totalEnfermedades->num_enfermedades * sizeof(int));
    for (int u = 0; u < totalEnfermedades->num_enfermedades; u++) {
        puntuaciones[u] = 0;

        Disease enfermedad = totalEnfermedades->enfermedades[u];
        LINKEDLIST_goToHead(&(enfermedad.sintomas));

        while (!LINKEDLIST_isAtEnd(enfermedad.sintomas)) {
            Sintoma* enfermedad_sintoma = &enfermedad.sintomas.previous->next->element;

            LINKEDLIST_goToHead(&usuario_sintomas);
            while (!LINKEDLIST_isAtEnd(usuario_sintomas)) {
                Sintoma* usuario_sintoma = &usuario_sintomas.previous->next->element;

                if (strcmp(usuario_sintoma->sintoma, enfermedad_sintoma->sintoma) == 0) {
                    puntuaciones[u] += enfermedad_sintoma->relevancia;
                    break;
                }

                LINKEDLIST_next(&usuario_sintomas);
            }

            LINKEDLIST_next(&(enfermedad.sintomas));
        }
    }


    // Ordenar enfermedades por puntuación (de mayor a menor) [ordenamiento burbuja]
    for (int i = 0; i < totalEnfermedades->num_enfermedades - 1; i++) {
        for (int j = 0; j < totalEnfermedades->num_enfermedades - i - 1; j++) {
            if (puntuaciones[j+1] > puntuaciones[j]) {

                // Intercambiar puntuaciones
                int temp_puntuacion = puntuaciones[j];
                puntuaciones[j] = puntuaciones[j+1];
                puntuaciones[j+1] = temp_puntuacion;

                // Intercambiar enfermedades
                Disease temp_enfermedad = totalEnfermedades->enfermedades[j];
                totalEnfermedades->enfermedades[j] = totalEnfermedades->enfermedades[j+1];
                totalEnfermedades->enfermedades[j+1] = temp_enfermedad;
            }
        }
    }

    // Mostrar resultados
    printf("\nMost probable diseases:\n");
    printf("-----------------------\n");
    /*    for (int i = 0; i < sizeof puntuaciones; ++i) {
            printf("%d\n", puntuaciones[i]);
        }*/
    int num_positivas = 0;
    for (int i = 0; i < totalEnfermedades->num_enfermedades -1; i++) {
        if (puntuaciones[i] > 0) {
            num_positivas++;
            printf("Total relevance %d: %s\n", puntuaciones[i], totalEnfermedades->enfermedades[i].nombre);
        }
    }

    if (num_positivas == 0) {
        printf("No diseases found!\n");
    }

    printf("\n");
    free(puntuaciones);

}


