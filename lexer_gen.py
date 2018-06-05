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
  parser.add_argument("root_dir", help="flex++ template and useful data")
  parser.add_argument("output_dir", dest="output", nargs='?', help="output file")
  K = parser.parse_args()
  lexer_dir = K.root_dir + "/lexer"
  output_dir = K.output_dir
  # print(K.lexer_dir, K.output)
  # return

  
  # counter = 100
  # enum_list = []
  token_list = []
  rule_list = []
  with open(lexer_dir + "/keyword.txt") as keyword_file:
    for line in keyword_file.readlines():
      if(line.split() == []):
        continue
      word = line.split()[0]
      symbol = word
      enum_list.append('%token '.format(
          word=word))
      # enum_list.append('  T_{word} = {counter}'.format(
          # word=word, counter=counter))
      token_list = ''
      rule_list.append('"{symbol}"{indent}{{ return T_{word}; }}'.format(
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
      rule_list.append('"{symbol}"{indent}{{ return T_{word}; }}'.format(
          symbol=symbol, word=word, indent=" "*(14 - len(symbol))))
      # counter += 1

  arg1 = "\n".join(token_list)
  arg2 = "\n".join(rule_list)
  # del

  with open(lexer_dir + "/lexer.template.l") as file:
    template = file.read()

  lexel_content = custom_format(template, arg1, arg2)
  praser_content = custom_format(template, arg1, arg2)

  contents = {"lexel.l": lexel_content, "parser.yxx": praser_content}
  if(output_dir):
    for [name, content] in contents:
      with open(output_dir + name) as file:
        file.write(content)
  else:
    for [name, content] in contents:
      print("\n-------------------------")
      print(name)
      print(content)
main(sys.argv)
