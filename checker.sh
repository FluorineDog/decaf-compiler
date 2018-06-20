cd final_build
llc main.ll
gcc main.s runtime.c -o final
./final

