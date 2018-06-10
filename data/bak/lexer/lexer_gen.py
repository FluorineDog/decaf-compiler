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
  parser.add_argument("src_dir", help="flex++ template and useful data")
  parser.add_argument("-o", dest="output", nargs='?', help="output file")
  K = parser.parse_args()
  src_dir = K.src_dir
  output_file = K.output
  # print(K.src_dir, K.output)
  # return

  with open(src_dir + "/lexer.template.l") as file:
    template = file.read()

  counter = 100
  enum_list = []
  rule_list = []
  with open(src_dir + "/keyword.txt") as keyword_file:
    for line in keyword_file.readlines():
      if(line.split() == []):
        continue
      word = line.split()[0]
      symbol = word
      enum_list.append('  T_{word} = {counter}'.format(
          word=word, counter=counter))
      rule_list.append('"{symbol}"{indent}{{ return T_{word}; }}'.format(
          symbol=symbol, word=word, indent=" "*(14 - len(symbol))))
      counter += 1

  with open(src_dir + "/symbols.txt") as keyword_file:
    for line in keyword_file.readlines():
      if(len(line.split()) == 0):
        continue
      assert(len(line.split()) == 2)
      word, symbol = line.split()
      enum_list.append('  T_{word} = {counter}'.format(
          word=word, counter=counter))
      rule_list.append('"{symbol}"{indent}{{ return T_{word}; }}'.format(
          symbol=symbol, word=word, indent=" "*(14 - len(symbol))))
      counter += 1

  arg1 = ",\n".join(enum_list)
  arg2 = "\n".join(rule_list)
  if(output_file):
    with open(output_file, 'w') as file:
      file.write(custom_format(template, arg1, arg2))
  else:
    print(custom_format(template, arg1, arg2))


main(sys.argv)
