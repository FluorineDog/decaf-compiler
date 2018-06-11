#!/bin/python
def custom_format(string, *args, **kwargs):
  padded = string.replace('{', '{{').replace('}', '}}')
  substituted = padded.replace('@#', '{').replace('#@', '}')
  formatted = substituted.format(*args, **kwargs)
  return formatted


def gen(parser_dir, token_list): 
  with open(parser_dir + "/rules.hand.yxx") as file:
    parser_rule_list = file.read()
    parser_rule_list = parser_rule_list.replace("%%", "")
    print(parser_rule_list)
  with open(parser_dir + "/token.gen.yxx") as file:
    token_rule_list = file.read()
    token_list = token_rule_list + '\n' + token_list
  with open(parser_dir + "/types.hand.yxx") as file:
    type_list = file.read()

  with open(parser_dir + "/union.hand.yxx") as file:
    union_list = file.read()

  with open(parser_dir + "/parser.template.yxx") as file:
    parser_content = custom_format(file.read(),\
     token_list=token_list,
      parser_rule_list = parser_rule_list,
      type_list = type_list,
      union_list = union_list
      )
  return parser_content

