#!/bin/python
import re

class_tmp = "class (\w+) *: *public ASTNodeBase.*?virtual.*?\a(.*?)};"
entry_tmp = "(^|\a)[^/]*?(\w+) (\w+);"

wt_mknode = '''
inline auto mk{name}({comma_list}) {{
  auto node = make_shared<{name}>();
{arrow_list}  // Generated
  return node;
}}
'''

def parse(content):
  class_eng = re.compile(class_tmp)
  entry_eng = re.compile(entry_tmp)
  result = class_eng.findall(content)
  mknode_c = '' 
  for name, values in result:
    entries = [(t, v) for _, t, v in entry_eng.findall(values)]
    comma_list = ", ".join(["{0} {1}".format(t, v) for (t, v) in entries])
    arrow_list = "".join(["  node->{1} = {1};\n".format(t, v) for (t, v) in entries])
    class_c = wt_mknode.format(name=name, comma_list=comma_list, arrow_list=arrow_list) 
    mknode_c += class_c
  with open('generated/mknode.h', 'w') as file:
    file.write(mknode_c)
  

def main():
  with open("common.h") as file:
    comment_eng = re.compile("^(.*?)(//|$)")
    con = file.read()
    new_con = ""
    for line in con.splitlines():
      # print(comment_eng.match(line).groups())
      new_con += comment_eng.match(line).groups()[0] + '\a'
    # print(new_con)
    parse(new_con)


main()
