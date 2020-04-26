gamefireman: bin/controller.o bin/files.o bin/colors.o bin/city.o bin/queries.o bin/fireman.o bin/player.o bin/game.o
	gcc -Wall -o fireman bin/controller.o bin/files.o bin/colors.o bin/city.o bin/queries.o bin/fireman.o bin/player.o bin/game.o -lncurses

bin/controller.o: src/controller.c src/headers/files.h src/headers/colors.h src/headers/city.h src/headers/queries.h src/headers/fireman.h src/headers/player.h
	mkdir -p bin
	gcc -c -o bin/controller.o src/controller.c

bin/files.o: src/files.c src/headers/files.h src/headers/player.h
	mkdir -p bin
	gcc -c -o bin/files.o src/files.c

bin/fireman.o: src/fireman.c src/headers/fireman.h src/headers/city.h
	mkdir -p bin
	gcc -c -o bin/fireman.o src/fireman.c

bin/city.o: src/city.c src/headers/city.h
	mkdir -p bin
	gcc -c -o bin/city.o src/city.c

bin/colors.o: src/colors.c src/headers/colors.h
	mkdir -p bin
	gcc -c -o bin/colors.o src/colors.c

bin/queries.o: src/queries.c src/headers/queries.h src/headers/files.h src/headers/player.h
	mkdir -p bin
	gcc -c -o bin/queries.o src/queries.c

bin/player.o: src/player.c src/headers/player.h src/headers/city.h
	mkdir -p bin
	gcc -c -o bin/player.o src/player.c

bin/game.o: src/game.c src/headers/game.h src/headers/files.h src/headers/colors.h
	mkdir -p bin
	gcc -c -o bin/game.o src/game.c

clean:
	rm -f bin/*
	rm -f fireman
	rm -f files/*