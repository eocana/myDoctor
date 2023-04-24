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

/***********************************************
*
* @Finalitat: Buscar una enfermedad en el array de enfermedades.
* @Paràmetres: nombre: el nombre de la enfermedad a buscar.
*              *enfermedades: puntero que lleva a la structura donde estan todas las enfermedades.
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
*              sintomas: el array de estructuras Sintoma.
*              num_sintomas: el número de elementos en el array de sintomas.
* @Retorn: El índice del síntoma en el array si se encuentra, -1 en caso contrario.
*
************************************************/
int buscarSintoma(char sintoma[], Sintoma sintomas[], int num_sintomas) {
    for (int i = 0; i < num_sintomas; i++) {
        if (strcmp(sintomas[i].sintoma, sintoma) == 0) {
            return i;
        }
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
void cargarEnfermedades( CargaEnfermedades *totalEnfermedades, char nombre_archivo[]) {

    char linea[MAX_CHAR];
    FILE* archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        printf("ERROR: Disease file not found");
    }

    // Leer número de enfermedades en el fichero
    fgets(linea, MAX_CHAR, archivo);
    totalEnfermedades->num_enfermedades = atoi(linea);
    totalEnfermedades->enfermedades = malloc(sizeof (Enfermedad)*totalEnfermedades->num_enfermedades);

    // Leer cada enfermedad del fichero
    for (int i = 0; i < totalEnfermedades->num_enfermedades; i++) {
        Enfermedad enfermedad;
        enfermedad.num_sintomas = 0;
        Sintoma nuevo_sintoma;
        char sintoma[MAX_CHAR];
        int num_sintomas, j, len, relevancia;

        // Leer nombre de la enfermedad
        fgets(linea, MAX_CHAR, archivo);

        // Eliminar el caracter '\n' de la línea leída
        len = strlen(linea);
        if (linea[len - 1] == '\n') {
            linea[len - 1] = '\0';
        }

        strcpy(enfermedad.nombre, linea);

        // Leer número de síntomas
        fgets(linea, MAX_CHAR, archivo);
        num_sintomas = atoi(linea);
        enfermedad.sintomas = malloc(sizeof (Sintoma)*num_sintomas);

        // Leer cada síntoma de la enfermedad
        for (j = 0; j < num_sintomas; j++) {
            fgets(linea, MAX_CHAR, archivo);
            len = strlen(linea);
            if (linea[len - 1] == '\n') {
                linea[len - 1] = '\0';
            }

            // Leer nombre del síntoma
            sscanf(linea, "%[^()] (%d)", sintoma, &relevancia);

            // Crear nuevo síntoma
            strcpy(nuevo_sintoma.sintoma, sintoma);
            nuevo_sintoma.relevancia = relevancia;

            // Agregar síntoma a la enfermedad
            enfermedad.sintomas[enfermedad.num_sintomas++] = nuevo_sintoma;
        }

        // Agregar enfermedad a la estructura resultado
        totalEnfermedades->enfermedades[i] = enfermedad;
    }

    fclose(archivo);
    printf("Welcome to myDoctor!");
    printf("\n");
}
/***********************************************
*
* @Finalitat: Mostrar la información de todas las enfermedades en el array de enfermedades.
* @Paràmetres: *enfermedades: puntero que lleva a la structura donde estan todas las enfermedades.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: void.
*
************************************************/
void mostrarEnfermedades(CargaEnfermedades* enfermedades) {
    for (int i = 0; i < enfermedades->num_enfermedades; i++) {
        printf("%s (", enfermedades->enfermedades[i].nombre);
        for (int j = 0; j < enfermedades->enfermedades[i].num_sintomas; j++) {
            printf("%s#%d", enfermedades->enfermedades[i].sintomas[j].sintoma, enfermedades->enfermedades[i].sintomas[j].relevancia);
            if (j < enfermedades->enfermedades[i].num_sintomas - 1) {
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
                idx_sintoma = buscarSintoma(registro.symptom, totalEnfermedades->enfermedades[idx_enfermedad].sintomas, totalEnfermedades->enfermedades[idx_enfermedad].num_sintomas);
                if (idx_sintoma != -1) {
                    if (registro.relevance != totalEnfermedades->enfermedades[idx_enfermedad].sintomas[idx_sintoma].relevancia) {
                        totalEnfermedades->enfermedades[idx_enfermedad].sintomas[idx_sintoma].relevancia = registro.relevance;
                        num_actualizadas++;
                    }
                } else {
                    // Agregar nuevo síntoma a la enfermedad
                    if (totalEnfermedades->enfermedades[idx_enfermedad].num_sintomas == 0) {
                        totalEnfermedades->enfermedades[idx_enfermedad].sintomas = malloc(sizeof(Sintoma));
                    } else {
                        totalEnfermedades->enfermedades[idx_enfermedad].sintomas = realloc(totalEnfermedades->enfermedades[idx_enfermedad].sintomas, (totalEnfermedades->enfermedades[idx_enfermedad].num_sintomas + 1) * sizeof(Sintoma));
                    }
                    if (totalEnfermedades->enfermedades[idx_enfermedad].sintomas == NULL) {
                        printf("ERROR: Allocation of 'enfermedades[idx_enfermedad].sintomas' failed []");
                        fclose(archivo);
                        return;
                    }
                    Sintoma sintoma;
                    strcpy(sintoma.sintoma, registro.symptom);
                    sintoma.relevancia = registro.relevance;
                    totalEnfermedades->enfermedades[idx_enfermedad].sintomas[totalEnfermedades->enfermedades[idx_enfermedad].num_sintomas++] = sintoma;
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
void helpMe(Enfermedad enfermedades[], int num_enfermedades) {

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

    // nos aseguramos que el final se ponga \0
    usuario_sintomas[idx_sintoma].nombre[idx_char] = '\0';
    usuario_sintomas[idx_sintoma].relevancia = 0;

    // Obtener puntuación de cada enfermedad
    int *puntuaciones = (int*)malloc(num_enfermedades * sizeof(int));
    for (u = 0; u < num_enfermedades; u++) {
        puntuaciones[u] = 0;
        for (j = 0; j < num_sintomas; j++) {
            for (k = 0; k < enfermedades[u].num_sintomas; k++) {
                int len = strlen(enfermedades[u].sintomas[k].sintoma);
                for (a = 0; a < len; a++) {
                    if (enfermedades[u].sintomas[k].sintoma[a] == ' ') {
                        enfermedades[u].sintomas[k].sintoma[a] = '\0';
                        a = len;
                    }
                }
                if (strcmp(usuario_sintomas[j].nombre, enfermedades[u].sintomas[k].sintoma) == 0) {
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


//Al final no lo hago servir pero lo mantego por si en
void liberarCargaEnfermedades(CargaEnfermedades* totalEnfermedades) {
    for (int i = 0; i < totalEnfermedades->num_enfermedades; i++) {
        free(totalEnfermedades->enfermedades[i].sintomas);
    }
    free(totalEnfermedades->enfermedades);
}
