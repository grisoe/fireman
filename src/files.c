#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "headers/files.h"

//Ruta y nombre del archivo en el que se registran las puntuaciones.
//Cambiarse a una ruta existente en la computadora donde se compile este código.
//Es global porque se usa en varias funciones.
//char *RUTA_A_ARCHIVO = "/home/srg/Desktop/ProyectoFinal/files/puntosJugadores";

char *rutaArchivo(){

    char cwd[150];
    

        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            
            char *result = malloc(strlen("/files/puntosJugadores") + strlen(cwd) + 1);

            strcpy(result, cwd);
            strcat(result, "/files/puntosJugadores");

            return result;

        } else {
            perror("getcwd() error");
            return NULL;
        }

}

void escribirEnArchivo(Jugador *js, int contJs){

    //Se abre el archivo en modo lectura.
    //Más información en la función abrirArchivo().
    FILE *fd = abrirArchivo(1);

    //Se saca al último jugador almacenado.
    Jugador jug = js[contJs - 1];

    //Nos vamos hasta el final del archivo.
    fseek(fd, 0, SEEK_END);
    //Se escribe el jugador.
    fwrite(&jug, sizeof(Jugador), 1, fd);

    //Se cierra el archivo.
    fclose(fd);

}

//Si al iniciar el programa no existe el archivo de puntos, lo crea.
void crearArchivo(){

    FILE *fd = fopen(rutaArchivo(), "ab+");

	//Cuando no se puede abrir o crear nu archivo, open() regresa un -1.
	if(fd == NULL){

        clear();

        endwin();

		//Función para imprimir errores del sistema.
		//Se puede usar printf, pero el no poder crear archivos es a veces error interno.
        perror("Error al crear el archivo");

        exit(1);

    }

    fclose(fd);

}

//Se abre el archivo para leerlo o para escribir en él.
//modo 0 es lectura, modo != 0 es escritura.
FILE* abrirArchivo(int modo){

    FILE *fd;

    if(modo == 0){
		fd = fopen(rutaArchivo(), "r");
	}else if(modo == 1){
		fd = fopen(rutaArchivo(), "aw");
	}else if(modo == 2){
        fd = fopen(rutaArchivo(), "r+");
    }

    if(fd == NULL){

        clear();

        endwin();

        perror("Error al abrir el archivo");

        exit(1);

    }

	return fd;

}