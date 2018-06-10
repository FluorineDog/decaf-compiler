cmake_minimum_required(VERSION 3.4)
set(PR "calc++-")
set(LEX_DEPS ${CMAKE_CURRENT_SOURCE_DIR}/*)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


add_custom_command(
  OUTPUT ${PR}parser.yy
  COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/${PR}parser.yy > ${PR}parser.yy
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PR}parser.yy 
  COMMENT "parser.yy generate"
)

add_custom_command(
  OUTPUT ${PR}parser.cc ${PR}parser.hh
  COMMAND bison -L c++ -o ${PR}parser.cc --defines=${PR}parser.hh ${PR}parser.yy
  DEPENDS ${PR}parser.yy
  COMMENT "bison generate"
)

add_custom_command(
  OUTPUT ${PR}scanner-mk.ll
  COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/${PR}scanner.ll > ${PR}scanner-mk.ll
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PR}scanner.ll 
  COMMENT "scanner.ll generate"
)

add_custom_command(
  OUTPUT ${PR}scanner.cc ${PR}scanner.hh
  COMMAND flex -o ${PR}scanner.cc --header-file=${PR}scanner.hh  ${PR}scanner-mk.ll 
  DEPENDS ${PR}scanner-mk.ll ${PR}parser.hh
  COMMENT "flex generated"
)

# add_custom_command(
#   COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/*.cc -t .
#   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
#   COMMEND "cp cc"
# )

# add_custom_command(
#   COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/*.hh -t .
#   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.hh
#   COMMEND "cp hh"
# )

add_library(parser ${PR}parser.cc)
add_library(driver ${PR}driver.cc)
add_library(scanner ${PR}scanner.cc)
# dep(calc++ "${PR}scanner.hh" "${PR}parser.hh")
add_executable(main calc++.cc)

target_link_libraries(main driver scanner parser)
