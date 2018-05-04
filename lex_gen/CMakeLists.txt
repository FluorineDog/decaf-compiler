

add_custom_command(
  OUTPUT lexer.cpp
  COMMAND flex++ lexer.l > lexer.cpp
  DEPENDS lexer.l
  COMMENT "flex++ generating"
)

add_custom_command(
  OUTPUT lexer.l 
  COMMAND gen.py
)

add_custom_target(
  lex_gen ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

