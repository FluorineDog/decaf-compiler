#!/bin/sh
python3 lexer_gen.py --root_dir . --output_dir handout || exit
bison handout/parser.yxx --defines=handout/parser.hxx --output=handout/parser.cpp || exit
flex++ -o handout/lexer.cpp handout/lexer.l || exit
g++ handout/*.cpp --std=c++17 -Wall -Wno-unused || exit
