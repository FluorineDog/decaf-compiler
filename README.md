Decaf Compiler
---------------
This project requires 
0. Linux distribution
1. GCC and Clang supporting C++17. 
2. latest bison and flex
3. LLVM 
4. zlib1g-dev (to solve "-lz not found")
5. /usr/bin/python3
After installing the tools above, run ./init.sh to generate necessary directory structure.

Then, run ./checker.sh to compile and link programs. 

You may modify ./checker.sh to test other programs, or manually do it at your wish.

