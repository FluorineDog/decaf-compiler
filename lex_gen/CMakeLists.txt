set(LEX_DEPS ${CMAKE_CURRENT_SOURCE_DIR}/*)
set(lexer_gen ${CMAKE_CURRENT_SOURCE_DIR}/lexer_gen.py)
add_custom_command(
  OUTPUT lexer.l 
  COMMAND ${lexer_gen} ${CMAKE_CURRENT_SOURCE_DIR} -o lexer.l
  DEPENDS ${LEX_DEPS}
  COMMENT "lexer.l generating"
)

add_custom_command(
  OUTPUT lexer.cpp
  COMMAND flex++ -o lexer.cpp lexer.l
  DEPENDS lexer.l
  COMMENT "flex generating"
)

# add_custom_target(
#   lex_gen ALL
#   DEPENDS lexer.cpp
#   COMMENT PHONY
# )

add_executable(lex_gen lexer.cpp)
# target_link_libraries(lex_gen fl)
