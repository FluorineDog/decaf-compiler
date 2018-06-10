#!/bin/python
def gen(lexer_dir):
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
  with open(lexer_dir + "/generated/tokens.yxx", "w") as file:
    special_token_list = "\n".join(special_token_list)
    file.write(special_token_list)

  token_list = "\n".join(token_list)
  lexer_rule_list = "\n".join(lexer_rule_list)
  return (token_list, lexer_rule_list)
