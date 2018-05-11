# Create target for the parser
cmake_minimum_required(VERSION 3.8)
add_subdirectory(lexer)
add_subdirectory(parser)

# Create custom command for flex/lex (note the outputs)
# ADD_CUSTOM_COMMAND(
#   SOURCE ${LEX_SOURCE_DIR}/src/lexer.l
#   COMMAND flex++ 
#   ARGS -o lexer.cpp
#        ${LEX_SOURCE_DIR}/src/lexer.l
#   TARGET FooParser
#   OUTPUTS lexer.cpp)

# Create custom command for bison/yacc (note the DEPENDS)
# ADD_CUSTOM_COMMAND(
#   SOURCE ${Foo_SOURCE_DIR}/src/parser.y
#   COMMAND ${BISON_EXECUTABLE} 
#   ARGS -y ${Foo_SOURCE_DIR}/src/parser.y
#        -o ${Foo_BINARY_DIR}/src/parser.c
#   TARGET FooParser
#   DEPENDS ${Foo_BINARY_DIR}/src/lexer.c
#   OUTPUTS ${Foo_BINARY_DIR}/src/parser.c)

# Add parser.c to the list of sources
# SET(Foo_SRCS ${Foo_SRCS} ${Foo_BINARY_DIR}/src/parser.c)

# Since parser.c does not exists yet when cmake is run, mark
# it as generated
# SET_SOURCE_FILES_PROPERTIES(${Foo_BINARY_DIR}/src/parser.c GENERATED)

# SET_SOURCE_FILES_PROPERTIES(lexer.cpp GENERATED)
# add_executable(lexer lexer.cpp)

# Include binary directory to include lexer.c in parser.c

