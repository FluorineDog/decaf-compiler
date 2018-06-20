# Create target for the parser
cmake_minimum_required(VERSION 3.8)
set(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs support core irreader)



add_custom_command(
  OUTPUT lexer.l parser.yxx
  COMMAND ${ROOT}/gen.py --root_dir ${ROOT} --output_dir .
  DEPENDS ${ROOT}/parser/* ${ROOT}/lexer/* ${ROOT}/gen.py
  COMMENT "generate from template"
)

add_custom_command(
  OUTPUT parser.cpp parser.hxx
  COMMAND bison parser.yxx --defines=parser.hxx --output=parser.cpp  -v 
  DEPENDS parser.yxx
  COMMENT "bison gen"
)

add_custom_command(
  OUTPUT lexer.cpp
  COMMAND flex++ -o lexer.cpp lexer.l 
  DEPENDS lexer.l
  COMMENT "flex gen"
)

SET_SOURCE_FILES_PROPERTIES(parser.hxx GENERATED)
SET_SOURCE_FILES_PROPERTIES(lexer.cpp GENERATED)
SET_SOURCE_FILES_PROPERTIES(parser.cpp GENERATED)

set(CMAKE_CXX_STANDARD 17)

include_directories(kernel)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_custom_target(parser_hxx DEPENDS parser.hxx)

file(GLOB VISITOR_CPPS kernel/PrintVisitor.cpp kernel/LoadSymbolTableVisitor.cpp kernel/StaticAnalyseVisitor.cpp)
add_library(visitors ${VISITOR_CPPS})
add_dependencies(visitors parser_hxx)

file(GLOB STATIC_ANALYSE kernel/static_analyse_driver/*.cpp)
add_library(static_analyse ${STATIC_ANALYSE})
target_link_libraries(static_analyse visitors)

add_library(parser parser.cpp)

add_library(lexer lexer.cpp)
add_dependencies(lexer parser_hxx)

file(GLOB LLVM_DRIVER kernel/llvm_driver/*.cpp kernel/CodegenVisitor.cpp)
add_library(llvm_driver ${LLVM_DRIVER})
target_link_libraries(llvm_driver ${llvm_libs})
add_dependencies(llvm_driver parser_hxx)

add_executable(main kernel/main.cpp)
# target_link_libraries(main visitors)
target_link_libraries(main parser)
target_link_libraries(main lexer)
target_link_libraries(main static_analyse)
target_link_libraries(main llvm_driver)
