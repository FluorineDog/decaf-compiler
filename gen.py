#!/bin/python
import sys
import argparse
import lexer.gen

def custom_format(string, *args, **kwargs):
  padded = string.replace('{', '{{').replace('}', '}}')
  substituted = padded.replace('@#', '{').replace('#@', '}')
  formatted = substituted.format(*args, **kwargs)
  return formatted

def main(*argv):
  parser = argparse.ArgumentParser(
    description="this is a generator of lexer.l"
  )
  parser.add_argument("--root_dir", dest="root_dir", nargs='?', help="root folder")
  parser.add_argument("--output_dir", dest="output_dir", nargs='?', help="output folder")

  K = parser.parse_args()
  lexer_dir = K.root_dir + "/lexer"
  parser_dir = K.root_dir + "/parser"
  output_dir = K.output_dir


  token_list, lexer_rule_list = lexer.gen.gen(lexer_dir)
  with open(parser_dir + "/generated/rules.gen.yxx") as file:
    parser_rule_list = file.read()

  with open(parser_dir + "/token.gen.yxx") as file:
    token_rule_list = file.read()
  token_list = token_rule_list + '\n' + token_list
  with open(lexer_dir + "/lexer.template.l") as file:
    lexer_content = custom_format(file.read(), lexer_rule_list=lexer_rule_list)

  with open(parser_dir + "/parser.template.yxx") as file:
    parser_content = custom_format(file.read(), token_list=token_list, parser_rule_list = parser_rule_list)

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
