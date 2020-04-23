juegoBombero: bin/controlador.o bin/archivos.o bin/colores.o bin/ciudad.o bin/consultas.o bin/bombero.o bin/jugador.o bin/juego.o
	gcc -Wall -o juegoBombero bin/controlador.o bin/archivos.o bin/colores.o bin/ciudad.o bin/consultas.o bin/bombero.o bin/jugador.o bin/juego.o -lncurses

bin/controlador.o: src/controlador.c src/headers/archivos.h src/headers/colores.h src/headers/ciudad.h src/headers/consultas.h src/headers/bombero.h src/headers/jugador.h
	mkdir -p bin
	gcc -c -o bin/controlador.o src/controlador.c

bin/archivos.o: src/archivos.c src/headers/archivos.h src/headers/jugador.h
	mkdir -p bin
	gcc -c -o bin/archivos.o src/archivos.c

bin/bombero.o: src/bombero.c src/headers/bombero.h src/headers/ciudad.h
	mkdir -p bin
	gcc -c -o bin/bombero.o src/bombero.c

bin/ciudad.o: src/ciudad.c src/headers/ciudad.h
	mkdir -p bin
	gcc -c -o bin/ciudad.o src/ciudad.c

bin/colores.o: src/colores.c src/headers/colores.h
	mkdir -p bin
	gcc -c -o bin/colores.o src/colores.c

bin/consultas.o: src/consultas.c src/headers/consultas.h src/headers/archivos.h src/headers/jugador.h
	mkdir -p bin
	gcc -c -o bin/consultas.o src/consultas.c

bin/jugador.o: src/jugador.c src/headers/jugador.h src/headers/ciudad.h
	mkdir -p bin
	gcc -c -o bin/jugador.o src/jugador.c

bin/juego.o: src/juego.c src/headers/juego.h src/headers/archivos.h src/headers/colores.h
	mkdir -p bin
	gcc -c -o bin/juego.o src/juego.c

clean:
	rm -f bin/*
	rm -f juegoBombero