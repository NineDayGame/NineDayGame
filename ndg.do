DEPS="main.o"
redo-ifchange $DEPS

LIBS="-L./libtcod-1.5.0/ -ltcod -ltcodxx"

g++ $DEPS $LIBS -o $3
