compile() {
    for i in $@; do
        clang -I. -Wall -O2 -c $i.c -o $(basename $i).o
    done
}

link() {
    clang -Wall -O2 -Wno-unused-function *.o -o a.exe
    rm -f *.o
}

compile iheap graph Single-Agent/IDAstar main
link