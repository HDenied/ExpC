## Build && run program
cd src
gcc -g -o sorter  ./utils/utils.c ./tst_tree/tst.c ./main.c -I. -Itst_tree -Iutils
./sorter

## Build && run heap tests
cd heap_tree
gcc -g -o unit_test unit_test.c heap.c ../utils/utils.c -I. -I../utils/
./unit_test

## Build && run tst tests
cd tst_tree
gcc -g -o unit_test unit_test.c tst.c ../utils/utils.c -I. -I../utils/
./unit_test

## Build && run utils tests
cd utils
gcc -g -o unit_test unit_test.c utils.c -I.
./unit_test

## GCC VERSION
gcc (GCC) 9.2.0

## Machine: ArchLinux 64
Linux XXXX 5.4.2-arch1-1 #1 SMP PREEMPT Thu, 05 Dec 2019 12:29:40 +0000 x86_64 GNU/Linux