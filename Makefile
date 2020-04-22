juegoBombero: bin/controlador.o bin/archivos.o bin/colores.o bin/ciudad.o bin/consultas.o bin/bombero.o bin/jugador.o bin/juego.o
	gcc -Wall -o juegoBombero bin/controlador.o bin/archivos.o bin/colores.o bin/ciudad.o bin/consultas.o bin/bombero.o bin/jugador.o bin/juego.o -lncurses

bin/controlador.o: src/controlador.c src/archivos.h src/colores.h src/ciudad.h src/consultas.h src/bombero.h src/jugador.h
	mkdir -p bin
	gcc -c -o bin/controlador.o src/controlador.c

bin/archivos.o: src/archivos.c src/archivos.h src/jugador.h
	mkdir -p bin
	gcc -c -o bin/archivos.o src/archivos.c

bin/bombero.o: src/bombero.c src/bombero.h src/ciudad.h
	mkdir -p bin
	gcc -c -o bin/bombero.o src/bombero.c

bin/ciudad.o: src/ciudad.c src/ciudad.h
	mkdir -p bin
	gcc -c -o bin/ciudad.o src/ciudad.c

bin/colores.o: src/colores.c src/colores.h
	mkdir -p bin
	gcc -c -o bin/colores.o src/colores.c

bin/consultas.o: src/consultas.c src/consultas.h src/archivos.h src/jugador.h
	mkdir -p bin
	gcc -c -o bin/consultas.o src/consultas.c

bin/jugador.o: src/jugador.c src/jugador.h src/ciudad.h
	mkdir -p bin
	gcc -c -o bin/jugador.o src/jugador.c

bin/juego.o: src/juego.c src/juego.h src/archivos.h src/colores.h
	mkdir -p bin
	gcc -c -o bin/juego.o src/juego.c

clean:
	rm -f bin/*
	rm -f juegoBombero