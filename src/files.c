#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "headers/files.h"

//Ruta y nombre del archivo en el que se registran las puntuaciones.
//Cambiarse a una ruta existente en la computadora donde se compile este código.
//Es global porque se usa en varias funciones.
//char *RUTA_A_ARCHIVO = "/home/srg/Desktop/ProyectoFinal/files/playersRecords";

char *recordsPath(){

    char cwd[150];
    

        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            
            char *result = malloc(strlen("/files/playersRecords") + strlen(cwd) + 1);

            strcpy(result, cwd);
            strcat(result, "/files/playersRecords");

            return result;

        } else {
            perror("getcwd() error");
            return NULL;
        }

}

void writeRecords(Player *player, int playersCounter){

    //Se abre el archivo en mode lectura.
    //Más información en la función abrirArchivo().
    FILE *fd = openRecords(1);

    //Se saca al último Player almacenado.
    Player p = player[playersCounter - 1];

    //Nos vamos hasta el final del archivo.
    fseek(fd, 0, SEEK_END);
    //Se escribe el Player.
    fwrite(&p, sizeof(Player), 1, fd);

    //Se cierra el archivo.
    fclose(fd);

}

//Si al iniciar el programa no existe el archivo de puntos, lo crea.
void createRecords(){

    FILE *fd = fopen(recordsPath(), "ab+");

	//Cuando no se puede abrir o crear nu archivo, open() regresa un -1.
	if(fd == NULL){

        clear();

        endwin();

		//Función para imprimir errores del sistema.
		//Se puede usar printf, pero el no poder crear archivos es a veces error interno.
        perror("Error: can't create file");

        exit(1);

    }

    fclose(fd);

}

//Se abre el archivo para leerlo o para escribir en él.
//mode 0 es lectura, mode != 0 es escritura.
FILE* openRecords(int mode){

    FILE *fd;

    if(mode == 0){
		fd = fopen(recordsPath(), "r");
	}else if(mode == 1){
		fd = fopen(recordsPath(), "aw");
	}else if(mode == 2){
        fd = fopen(recordsPath(), "r+");
    }

    if(fd == NULL){

        clear();

        endwin();

        perror("Error: can't open file");

        exit(1);

    }

	return fd;

}