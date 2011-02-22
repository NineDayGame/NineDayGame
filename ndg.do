for file in `find . -name libraries -prune -o -name '*.cpp' -print`; do
	DEPS="$DEPS ${file%.cpp}.o ";
done

redo-ifchange $DEPS

LIBS="-L./libraries/libtcod-1.5.0/ -ltcod -ltcodxx -lGL -lGLU"

g++ $DEPS $LIBS -o $3
