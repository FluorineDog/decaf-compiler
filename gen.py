#!/bin/python
import sys
import argparse


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

  token_list = []
  lexer_rule_list = []
  special_token_list = []
  with open(lexer_dir + "/keyword.txt") as keyword_file:
    for line in keyword_file.readlines():
      if(line.split() == []):
        continue
      word = line.split()[0]
      symbol = word
      # enum_list.append('  T_{word} = {counter}'.format(
          # word=word, counter=counter))
      token_list.append('%token T_{word}'.format(
          word=word))
      lexer_rule_list.append('"{symbol}"{indent}{{ return T_{word}; }}'.format(
          symbol=symbol, word=word, indent=" "*(14 - len(symbol))))
      # counter += 1

  with open(lexer_dir + "/symbols.txt") as keyword_file:
    for line in keyword_file.readlines():
      if(len(line.split()) == 0):
        continue
      assert(len(line.split()) == 2)
      word, symbol = line.split()
      word = "T_" + word
      # enum_list.append('  T_{word} = {counter}'.format(
          # word=word, counter=counter))
      if len(symbol) == 1:
        word = "'" + symbol + "'"
      special_token_list.append('%token {word}'.format(
          word=word))
      lexer_rule_list.append('"{symbol}"{indent}{{ return {word}; }}'.format(
          symbol=symbol, word=word, indent=" "*(14 - len(symbol))))
      # counter += 1

  lexer_rule_list = "\n".join(lexer_rule_list)
  with open(output_dir + "/hand_parser_tokens.yxx" , "w") as file:
    special_token_list = "\n".join(special_token_list)
    file.write(special_token_list)

  token_list = "\n".join(token_list)
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
