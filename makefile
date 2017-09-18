OBJECTS = obj/main.o \
        obj/animateBullet.o \
        obj/edgeLight.o \
        obj/generateLife.o \
        obj/raindrops.o \
        obj/movingPlane.o \
        obj/randomToggle.o

bin/ledCube : $(OBJECTS)
	gcc  $(OBJECTS) -Llib -I inc -liofunc -o bin/ledCube

obj/main.o : src/main.c inc/common.h inc/edgeLight.h inc/generateLife.h inc/raindrops.h inc/movingPlane.h inc/randomToggle.h
	gcc -c -I inc -o obj/main.o src/main.c

obj/animateBullet.o : src/animateBullet.c inc/common.h inc/animateBullet.h
	gcc -c -I inc -o obj/animateBullet.o src/animateBullet.c

obj/edgeLight.o : src/edgeLight.c inc/common.h inc/edgeLight.h
	gcc -c -I inc -o obj/edgeLight.o src/edgeLight.c

obj/generateLife.o : src/generateLife.c inc/common.h inc/generateLife.h
	gcc -c -I inc -o obj/generateLife.o src/generateLife.c

obj/raindrops.o : src/raindrops.c inc/common.h inc/raindrops.h
	gcc -c -I inc -o obj/raindrops.o src/raindrops.c

obj/movingPlane.o : src/movingPlane.c inc/common.h inc/movingPlane.h
	gcc -c -I inc -o obj/movingPlane.o src/movingPlane.c

obj/randomToggle.o : src/randomToggle.c inc/common.h inc/randomToggle.h
	gcc -c -I inc -o obj/randomToggle.o src/randomToggle.c

.PHONY: clean

clean:
	-rm obj/*
	-rm bin/*
