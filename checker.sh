make -C build
cd final_build
clang -c runtime.c -emit-llvm
cd ..
./build/main
cd final_build
rm final -f
llc main.ll
gcc main.s runtime.c -o final
./final
echo 'exitcode = ' $?

