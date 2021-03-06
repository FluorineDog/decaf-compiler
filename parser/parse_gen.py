#!/usr/bin/python33
import sys
import re
# ? Optional
# + List
# * ListOptional
# , Comma...

name_list_done = set()


def add_rule_c(rule_c, item, parser):
  if len(item) == 1:
    rule_c.append("'" + item + "'")
    return item

  if item[-1] in ['?', '*']:
    if item[-1] == '*':
      tail = "+"
    else:
      tail = ''
    item_new = item[0:-1] + tail
    rule_c_new = ["%empty"]
    list_name_new = add_rule_c(rule_c_new, item_new, parser)
    list_name = list_name_new + "Optional"
    add_parser(parser, list_name, rule_c_new)
    rule_c.append(list_name)
    return list_name

  if item[-1] == '+':
    expr = item[0:-1]
    sp = ''
    list_name = ''
    if expr[-1] == ',':
      sp = " , "
      expr = expr[0:-1]
      list_name = expr + "CommaList"
    else:
      sp = " "
      expr = expr
      list_name = expr + "List"
    add_parser(parser, list_name, [expr, list_name + sp + expr])
    rule_c.append(list_name)
    return list_name

  rule_c.append(item)
  return item


def add_parser(parser, name, body):
  if name in name_list_done:
    return
  name_list_done.add(name)
  rule_list = []
  print(name)
  for rule in body:
    # print(rule, "$", end='')
    items = rule.split(' ')
    items = [i for i in items if len(i) >= 1]
    # print(items)
    rule_c = []
    for item in items:
      add_rule_c(rule_c, item, parser)
    # print(rule_c, end=' ')
    # rule_c = " ".join(rule_c)
    rule_list.append(rule_c)

  filterchars = "(){},;."
  filterchars = ["'" + ch + "'" for ch in filterchars]

  action = ''

  def joy(x): 
    raw = " ".join(x)
    raw += (22 - len(raw)) *" " + 5*" "
    return raw + "{" + action + "}"
  rule_c_list = [ joy(rule) for rule in rule_list if rule]
  rule_list_c = "\n| ".join(rule_c_list)
  parser.append(name + ":\n  " + rule_list_c + "\n;\n")
  pass

def main():
  with open("bnf.hs") as file:
    input = file.read()
  input = input.replace('\\\n', '')
  lines = re.findall("^(.*)::=(.*)$", input, re.M)
  parser = []
  for full_line in lines:
    # print(full_line)
    name = full_line[0].replace(' ', '')
    body = full_line[1].split("|")
    add_parser(parser, name, body)
    full_line = ''

  content_c = "\n".join(parser)
  with open("generated/rules.gen.yxx", 'w') as file:
    file.write(content_c)

if __name__ == "__main__":
  main()
