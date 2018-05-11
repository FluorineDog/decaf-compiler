set(parser_DEPS ${CMAKE_CURRENT_SOURCE_DIR}/*)
set(parser_input ${CMAKE_CURRENT_SOURCE_DIR}/parser.yxx)
set(parser_gen ${CMAKE_CURRENT_SOURCE_DIR}/lexer_gen.py)
# add_custom_command(
#   OUTPUT parser.tab.cxx parser.tab.hxx
#   COMMAND ${lexer_gen} ${CMAKE_CURRENT_SOURCE_DIR} -o lexer.l
#   DEPENDS ${LEX_DEPS}
#   COMMENT "lexer.l generating"
# )


add_custom_command(
  OUTPUT parser.cpp parser.hxx
  COMMAND bison ${parser_input} -o parser.cpp --defines=parser.hxx
  DEPENDS ${parser_input}
  COMMENT "bison generating"
)


# add_custom_target(
#   lex_gen ALL
#   DEPENDS lexer.cpp
#   COMMENT PHONY
# )

# target_link_libraries(lex_gen fl)


add_library(parser parser.cpp)