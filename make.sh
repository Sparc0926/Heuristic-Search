compile() {
    for i in $@; do
        clang -I. -Wall -O2 -c $i.c -o $i.o
    done
}

link() {
    clang -Wall -O2 -Wno-unused-function *.o -o a.exe
    rm -f *.o
}

compile iheap graph main
link