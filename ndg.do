for file in *.cpp; do
	DEPS+=${file%.cpp}.o" ";
done

redo-ifchange $DEPS

LIBS="-L./libtcod-1.5.0/ -ltcod -ltcodxx -lGL -lGLU"

g++ $DEPS $LIBS -o $3
