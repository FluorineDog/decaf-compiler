A Naive Decaf Compiler 
---------------
ACM1501 U201514613 苟桂霖

# introduction
This project implements a Java-like language called decaf,
which compiles .decaf code into LLVM middle code(.ll).  
It features:

1. use Flex as tokenizier;
2. use Bison as Praser;
3. support limited static analysis;
4. use LLVM Builder to generate final middle code.

# requirement
This project requires 
0. Linux distribution
1. GCC and Clang supporting C++17. 
2. latest bison and flex
3. LLVM 
4. zlib1g-dev (to solve "-lz not found")
5. /usr/bin/python3

# usage
To run it, first run ./init.sh to generate necessary directory structure, and fix any error infomation if exists


After installing the tools above, run ./init.sh to generate necessary directory structure.

Then, run ./checker.sh to compile and link programs. You can modify ./checker.sh to test other program, or manually do it at your wish.
