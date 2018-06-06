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
  # print(K.lexer_dir, K.output)
  # return

  
  # counter = 100
  # enum_list = []
  token_list = []
  lexer_rule_list = []
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
      # enum_list.append('  T_{word} = {counter}'.format(
          # word=word, counter=counter))
      token_list.append('%token T_{word}'.format(
          word=word))
      lexer_rule_list.append('"{symbol}"{indent}{{ return T_{word}; }}'.format(
          symbol=symbol, word=word, indent=" "*(14 - len(symbol))))
      # counter += 1

  token_list = "\n".join(token_list)
  lexer_rule_list = "\n".join(lexer_rule_list)

  with open(lexer_dir + "/lexer.template.l") as file:
    lexel_content = custom_format(file.read(), lexer_rule_list)

  with open(parser_dir + "/parser.template.yxx") as file:
    parser_content = custom_format(file.read(), token_list)

  contents = {"/lexel.l": lexel_content, "/parser.yxx": parser_content}
  if(output_dir):
    for name, content in contents.items():
      with open(output_dir + name, 'w') as file:
        file.write(content)
  else:
    for name, content in contents.items():
      print("\n-------------------------")
      print(name)
      print(content)
main(sys.argv)
