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

  with open("keyword.txt") as keyword_file:
    pass
  print(custom_format(template, 11111, 22222))
main()