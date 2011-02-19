redo-ifchange $1.cpp

CFLAGS=""

g++ $CFLAGS -MD -MF $3.deps.tmp -c -o $3 $1.cpp

# Checks implicit dependencies
DEPS=$(sed -e "s/^$3://" -e 's/\\//g' <$3.deps.tmp)
rm -f $3.deps.tmp
redo-ifchange $DEPS
