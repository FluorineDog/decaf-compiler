#!/usr/bin/python3
import sys
import argparse
import lexer.engine
import parser.engine
from lexer.engine import custom_format

def main(*argv):
  parserArg = argparse.ArgumentParser(
    description="this is a generator of lexer.l"
  )
  parserArg.add_argument("--root_dir", dest="root_dir", nargs='?', help="root folder")
  parserArg.add_argument("--output_dir", dest="output_dir", nargs='?', help="output folder")

  K = parserArg.parse_args()
  lexer_dir = K.root_dir + "/lexer"
  parser_dir = K.root_dir + "/parser"
  output_dir = K.output_dir

  # lexer.gen
  token_list, lexer_rule_list = lexer.engine.gen(lexer_dir)

  lexer_content = lexer.engine.lexer_l_gen(lexer_rule_list, lexer_dir)
  parser_content = parser.engine.gen(parser_dir, token_list)

  contents = {"/lexer.l": lexer_content, "/parser.yxx": parser_content}
  if(output_dir):
    for name, content in contents.items():
      with open(output_dir + name, 'w') as file:
        file.write(content)
  else:
    for name, content in contents.items():
      print("\n-------------------------")
      print(name)
      print(content)

if __name__ == "__main__":
  main(sys.argv)
