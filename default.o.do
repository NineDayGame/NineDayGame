redo-ifchange $1.cpp

CFLAGS="-O3"
INCLUDE="-I./libraries/libtcod-1.5.0/include -I./lore -I./kobold -I./goblin"

g++ $CFLAGS $INCLUDE -MD -MF $1.d -c -o $3 $1.cpp

read DEPS <$1.d
redo-ifchange ${DEPS#*:}
rm $1.d
