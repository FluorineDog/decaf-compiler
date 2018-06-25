make -C build
cd final_build
clang -fPIC -c runtime.c -emit-llvm
cd ..
./build/main
cd final_build
rm final -f
llc main.ll -relocation-model=pic
gcc -fPIC main.s runtime.c -o final
echo
echo
cat ../data/naive.decaf
./final
echo 'exitcode = ' $?

