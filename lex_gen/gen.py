#!/bin/python
def custom_format(string, *args, **kwargs):
    padded = string.replace('{', '{{').replace('}', '}}')
    substituted = padded.replace('@#', '{').replace('#@', '}')
    formatted = substituted.format(*args, **kwargs)
    return formatted


def main():
  template = ""
  with open("lex.template.l") as file:
    template = file.read()

  counter = 100
  enum_list = [] 
  rule_list = []
  with open("keyword.txt") as keyword_file:
    for line in keyword_file.readlines():
      if(line.split() == []):
        continue
      word = line.split()[0]
      enum_list.append('T_{0} = {1}'.format(word, counter))
      rule_list.append('"{0}"{1}   {{ return T_{0}; }}'.format(word, " "*(14 - len(word))))
      counter += 1

  with open("symbols.txt") as keyword_file:
    for line in keyword_file.readlines():
      if(len(line.split()) == 0):
        continue
      assert(len(line.split()) == 2)  
      word, symbol = line.split()
      print(word, symbol) 
      enum_list.append('T_{0} = {1}'.format(word, counter))
      rule_list.append('"{1}"{2}   {{ return T_{0}; }}'.format(word, symbol, " "*(14 - len(symbol))))
      counter += 1
  
  arg1 = ",\n".join(enum_list)
  arg2 = "\n".join(rule_list)
  with open("dog.l", 'w') as file:
    file.write(custom_format(template, arg1, arg2))
    
main()