add_custom_command(
  OUTPUT lexer.cpp
  COMMAND flex++ lexer.l && mv lex.yy.cc lexer.cpp
  DEPENDS lexer.l
  COMMENT "flex++ generating"
)


set(LEX_DEPS ${CMAKE_CURRENT_SOURCE_DIR}/*)
set(lexer_gen ${CMAKE_CURRENT_SOURCE_DIR}/lexer_gen.py)
add_custom_command(
  OUTPUT lexer.l 
  COMMAND ${lexer_gen} ${CMAKE_CURRENT_SOURCE_DIR} -o lexer.l
  DEPENDS ${LEX_DEPS}
  COMMENT "lexer.l generating"
)
# set_target_properties(lexer.cpp GENERATED)
# set_target_properties(lexer.l GENERATED)

# add_custom_target(
#   lex_gen ALL
#   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
# )

add_executable(lex_gen lexer.cpp)
target_link_libraries(lex_gen fl)