/*****************
*
* @Propòsit: Todos los menus del programa
* @Autor/s: Eric Ocaña Segura
* @Data de creació: 14/03/2023
* @Data de l’última modificació: 25/04/2023
*
****************/

#ifndef MYDOCTOR_MENU_H
#define MYDOCTOR_MENU_H
/*****************
*
* @Finalitat: Muestra el menú principal cuando ya se ha cargado
* @Paràmetres:
* @Retorn: Retorna la opción del menu que el usuario ha escogido
*
****************/
int mostrar_menu();

/*****************
*
* @Finalitat: Pide el nombre del archivo
* @Paràmetres: nombre_archivo: el nombre del archivo que contiene la información de las enfermedades
* @Retorn: void
*
****************/
void pedir_nombre_archivo(char nombre_archivo[]);
#endif //MYDOCTOR_MENU_H
