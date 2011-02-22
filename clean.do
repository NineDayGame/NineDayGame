for f in `find . -name libraries -prune -o -name '*.o' -print`; do
    rm $f;
done
rm -f ndg
