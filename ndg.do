DEPS="main.o map.o block.o cube.o entity.o glrenderer.o movable.o mesh.o timer.o vertex.o"

redo-ifchange $DEPS

LIBS="-L./libtcod-1.5.0/ -ltcod -ltcodxx -lGL -lGLU"

g++ $DEPS $LIBS -o $3
