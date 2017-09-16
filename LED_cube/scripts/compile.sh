rm ./obj/*
rm ./bin/*


gcc -c -I inc -o ./obj/main.o ./src/main.c

gcc -c -I inc -o ./obj/animateBullet.o ./src/animateBullet.c
gcc -c -I inc -o ./obj/edgeLight.o ./src/edgeLight.c
gcc -c -I inc -o ./obj/generateLife.o ./src/generateLife.c
gcc -c -I inc -o ./obj/raindrops.o ./src/raindrops.c
gcc -c -I inc -o ./obj/movingPlane.o ./src/movingPlane.c
gcc -c -I inc -o ./obj/randomToggle.o ./src/randomToggle.c


gcc ./obj/main.o ./obj/animateBullet.o ./obj/edgeLight.o ./obj/generateLife.o ./obj/raindrops.o ./obj/movingPlane.o ./obj/randomToggle.o -Llib -I inc -liofunc -o ./bin/ledCube
