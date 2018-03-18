rm ./obj/*
rm ./bin/*


clang++ -std=c++11 -stdlib=libc++ -c -I inc -o ./obj/main.o ./src/main.cpp

clang++ -std=c++11 -stdlib=libc++ -c -I inc -o ./obj/AnimateBullet.o ./src/AnimateBullet.cpp
clang++ -std=c++11 -stdlib=libc++ -c -I inc -o ./obj/EdgeLight.o ./src/EdgeLight.cpp
clang++ -std=c++11 -stdlib=libc++ -c -I inc -o ./obj/Raindrops.o ./src/Raindrops.cpp
clang++ -std=c++11 -stdlib=libc++ -c -I inc -o ./obj/MovingPlane.o ./src/MovingPlane.cpp
clang++ -std=c++11 -stdlib=libc++ -c -I inc -o ./obj/RandomToggle.o ./src/RandomToggle.cpp


clang++ -std=c++11 -stdlib=libc++ ./obj/main.o ./obj/AnimateBullet.o ./obj/EdgeLight.o ./obj/Raindrops.o ./obj/MovingPlane.o ./obj/RandomToggle.o -Llib -I inc -liofunc -o ./bin/ledCube
