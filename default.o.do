redo-ifchange $1.cpp

CFLAGS=""
INCLUDE="-I./libraries/libtcod-1.5.0/include -I./lore -I./kobold -I./goblin"

g++ $CFLAGS $INCLUDE -MD -MF $3.deps.tmp -c -o $3 $1.cpp

# Checks implicit dependencies
ESCAPED_FILE=$(echo "$3" | sed -e 's/\//\\\//g')
DEPS=$(sed -e "s/^$ESCAPED_FILE://" -e 's/\\//g' <$3.deps.tmp)
rm -f $3.deps.tmp
redo-ifchange $DEPS
