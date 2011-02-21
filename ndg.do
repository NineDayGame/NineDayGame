DEPS="main.o map.o block.o camera.o character.o cube.o entity.o glrenderer.o living.o movable.o mesh.o player.o timer.o vertex.o util.o item.o container.o"

redo-ifchange $DEPS

LIBS="-L./libtcod-1.5.0/ -ltcod -ltcodxx -lGL -lGLU"

g++ $DEPS $LIBS -o $3
