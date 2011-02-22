DEPS="main.o map.o block.o camera.o character.o container.o cube.o entity.o glrenderer.o item.o living.o movable.o mesh.o menu.o main_gamestate.o player.o timer.o vector3f.o vector2f.o util.o menuitem.o"

redo-ifchange $DEPS

LIBS="-L./libtcod-1.5.0/ -ltcod -ltcodxx -lGL -lGLU"

g++ $DEPS $LIBS -o $3
