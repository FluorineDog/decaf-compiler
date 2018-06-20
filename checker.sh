make -C build
./build/main
cd final_build
rm final
llc main.ll
gcc main.s runtime.c -o final
./final
echo 'exitcode = ' $?

