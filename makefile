OBJECTS = obj/main.o \
        obj/animateBullet.o \
        obj/edgeLight.o \
        obj/generateLife.o \
        obj/raindrops.o \
        obj/movingPlane.o \
        obj/randomToggle.o

bin/ledCube : $(OBJECTS)
	gcc  $(OBJECTS) -Llib -I inc -liofunc -o bin/ledCube

obj/main.o : src/main.c
	gcc -c -I inc -o obj/main.o src/main.c

obj/animateBullet.o : src/animateBullet.c
	gcc -c -I inc -o obj/animateBullet.o src/animateBullet.c

obj/edgeLight.o : src/edgeLight.c
	gcc -c -I inc -o obj/edgeLight.o src/edgeLight.c

obj/generateLife.o : src/generateLife.c
	gcc -c -I inc -o obj/generateLife.o src/generateLife.c

obj/raindrops.o : src/raindrops.c
	gcc -c -I inc -o obj/raindrops.o src/raindrops.c

obj/movingPlane.o : src/movingPlane.c
	gcc -c -I inc -o obj/movingPlane.o src/movingPlane.c

obj/randomToggle.o : src/randomToggle.c
	gcc -c -I inc -o obj/randomToggle.o src/randomToggle.c

clean :
	-rm obj/*
	-rm bin/*
