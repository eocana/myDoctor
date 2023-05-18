/***********************************************
* @Propòsit: Implementar las funciones necesarias para cargar y manipular información sobre enfermedades y síntomas.
* @Autor/s: Eric Ocaña Segura
* @Data de creació: 01/04/2023
* @Data de l’última modificació: 23/04/2023
************************************************/
#ifndef MYDOCTOR_ENFERMEDADES_H
#define MYDOCTOR_ENFERMEDADES_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#define MAX_SINTOMAS 10
#define MAX_CHAR 50

// Estructura para representar una enfermedad

typedef struct {

    char nombre[MAX_CHAR];
    LinkedList  sintomas;
    int num_sintomas;

} Disease;

typedef struct {

    Disease *enfermedades;
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
* @Paràmetres: *totalEnfermedades: structura donde se guardara de forma dinamica
*              nombre_archivo: el nombre del archivo que contiene la información de las enfermedades.
* @Retorn: void
************************************************/
void cargarEnfermedades(CargaEnfermedades *totalEnfermedades, char nombre_archivo[]);

/***********************************************
*
* @Finalitat: Mostrar la información de todas las enfermedades en el array de enfermedades.
* @Paràmetres: *enfermedades: puntero que lleva a la structura donde estan todas las enfermedades.
*              num_enfermedades: el número de elementos en el array de enfermedades.
* @Retorn: void
************************************************/
void mostrarEnfermedades(CargaEnfermedades* enfermedades);

/***********************************************
*
* @Finalitat: Actualizar la información de las enfermedades a partir de un archivo.
* @Paràmetres: nombre_archivo: el nombre del archivo que contiene la información actualizada de los síntomas.
*              *totalEnfermedades: puntero que lleva a la structura donde estan todas las enfermedades.
* @Retorn: void
*
************************************************/
void actualizarEnfermedades(char nombre_archivo[], CargaEnfermedades* totalEnfermedades);

/***********************************************
* Sóc consciente que no varia la funció ja que crec que no es necessari perque ja faig una bona carrega de
 * l'informació i una bona actualització per tant no cal pasar per punter ni fer res de nou a Help me
* @Finalitat: Pedir al usuario una lista de síntomas y mostrar las enfermedades posibles según esos síntomas.
* @Paràmetres: enfermedades: array de todas las enfermedades.
*              nombre_archivo: el nombre del archivo que contiene la información de las enfermedades.
* @Retorn: void
*
************************************************/
//void helpMe(Disease enfermedades[], int num_enfermedades);

#endif //MYDOCTOR_ENFERMEDADES_H
