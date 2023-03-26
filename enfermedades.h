/***********************************************
* @Propòsit: Implementar las funciones necesarias para cargar y manipular información sobre enfermedades y síntomas.
* @Autor/s: Eric Ocaña Segura
* @Data de creació: 18/03/2023
* @Data de l’última modificació: 26/03/2023
************************************************/
#ifndef MYDOCTOR_ENFERMEDADES_H
#define MYDOCTOR_ENFERMEDADES_H

#define MAX_ENFERMEDADES 30
#define MAX_SINTOMAS 10
#define MAX_CHAR 50

// Estructura para representar una enfermedad
typedef struct {
    char sintoma[MAX_CHAR];
    int relevancia;
} Sintoma;

typedef struct {
    char nombre[MAX_CHAR];
    Sintoma sintomas[MAX_SINTOMAS];
    int num_sintomas;
} Enfermedad;

typedef struct {
    Enfermedad enfermedades[MAX_ENFERMEDADES];
    int num_enfermedades;
} CargaEnfermedades;

typedef struct {
    char disease[MAX_CHAR];
    char symptom[MAX_CHAR];
    int relevance;
} FileDisease;

typedef struct {
    char nombre[MAX_CHAR];
    int relevancia;
} SintomaUsuario;

/***********************************************
*
* @Finalitat: Cargar las enfermedades desde un archivo y almacenarlas en un array de estructuras.
* @Paràmetres: nombre_archivo: el nombre del archivo que contiene la información de las enfermedades.
* @Retorn: Un struct CargaEnfermedades que contiene un array de estructuras Enfermedad con la información cargada del archivo.
*
************************************************/
CargaEnfermedades cargar_enfermedades(char nombre_archivo[]);


/***********************************************
*
* @Finalitat: Mostrar la información de todas las enfermedades en el array de enfermedades.
* @Paràmetres: enfermedades: el array de estructuras Enfermedad.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: void.
*
************************************************/
void mostrar_enfermedades(Enfermedad enfermedades[], int num_enfermedades);

/***********************************************
*
* @Finalitat: Actualizar la información de las enfermedades a partir de un archivo.
* @Paràmetres: nombre_archivo: el nombre del archivo que contiene la información actualizada de los síntomas.
*              enfermedades: el array de estructuras Enfermedad.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: void.
*
************************************************/
void actualizar_enfermedades(char nombre_archivo[], Enfermedad enfermedades[], int num_enfermedades);

/***********************************************
*
* @Finalitat: Pedir al usuario una lista de síntomas y mostrar las enfermedades posibles según esos síntomas.
* @Paràmetres: enfermedades: el array de estructuras Enfermedad.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: void.
*
************************************************/
void help_me(Enfermedad enfermedades[], int num_enfermedades);


#endif //MYDOCTOR_ENFERMEDADES_H
