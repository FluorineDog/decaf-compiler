#!/bin/python3
import sys
import re


def add_rule(parser, name, body):
  for rule in body:
    # print(rule, "$", end='')
    items = rule.split(' ')
    items = [i for i in items if len(i) >= 1]
    rule_c = []
    for item in items:
      if len(item) == 1:
        rule_c.append("'" + item + "'")
        continue
      if item[-1] == '+':
        if len(items) == 1:
          expr = item[0:-1]
          sp = ''
          if expr[-1] == ',':
            sp = "','"
          print(expr)
          # parser.append((name, [[], []]))

  pass


def main():
  lines = re.findall("^(.*)::=(.*)$", sys.stdin.read(), re.M)
  parser = []
  for tmp in lines:
    name = tmp[0]
    body = tmp[1].split("|")
    add_rule(parser, name, body)
if __name__ == "__main__":
  main()
