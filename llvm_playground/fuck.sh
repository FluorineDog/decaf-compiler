clang -emit-llvm -c runtime.c -o runtime.bc &&
gcc -c runtime.c -o runtime.o &&
pwd
make 
./imitation 2> imi.ll
llc imi.ll 
gcc imi.s -o fuckall

