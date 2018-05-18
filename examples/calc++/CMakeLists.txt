cmake_host_system_information(3.4)
set(PR "calc++-")
set(LEX_DEPS ${CMAKE_CURRENT_SOURCE_DIR}/*)

set(lexer_gen cat)
add_custom_command(
  OUTPUT ${PR}scanner.ll
  COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/${PR}scanner.ll > ${PR}scanner.ll
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PR}scanner.ll
  COMMENT "scanner.ll generate"
)


add_custom_command(
  OUTPUT ${PR}scanner.cc ${PR}scanner.cc
  COMMAND flex++ ${PR}scanner.ll -o ${PR}scanner.cc --header-file=${PR}scanner.hh
  DEPENDS ${PR}scanner.ll
  COMMENT "flex generate"
)


add_custom_command(
  OUTPUT ${PR}parser.yy
  COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/${PR}parser.yy > ${PR}parser.yy
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PR}parser.yy
  COMMENT "parser.yy generate"
)

add_custom_command(
  OUTPUT ${PR}parser.cc ${PR}parser.hh
  COMMAND bison -L c++ -o ${PR}parser.cc --header-file=${PR}parser.hh ${PR}parser.yy
  DEPENDS ${PR}parser.yy
  COMMNET "bison generate"
)
add_executable(main calc++.cc)
add_library(driver ${PR}driver.cc)
add_library(scanner ${PR}scanner.cc)
target_link_libraries(main driver scanner)