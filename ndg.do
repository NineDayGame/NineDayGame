DEPS="main.o"
redo-ifchange $DEPS

LIBS=""

g++ $DEPS $LIBS -o $3
