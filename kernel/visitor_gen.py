#!/bin/python
import re
import os

class_tmp = "class (\w+) *: *public ASTNodeBase.*?virtual.*?\a(.*?)};"
entry_tmp = "(^|\a)[ ]*?(\w+) (\w+);"

wt_mknode = '''
inline auto mk{name}({comma_list}) {{
  auto node = make_shared<{name}>();
{arrow_list} // Generated
  return node;
}}
'''
wt_visitor = '''#pragma once
class Visitor {{
 public:
{0} // Generated
}};
{1} 
'''

wt_headers = '''#pragma once
#include "common.h"
#include "Visitor.h"
class {name}Visitor : public Visitor{{
{0}
}};
'''

def parse(content, visitors):
  class_eng = re.compile(class_tmp)
  entry_eng = re.compile(entry_tmp)
  result = class_eng.findall(content)
  mknode_c = '#include "../common.h"'

  print(visitors)
  pure_list = "".join([
    "  virtual void visit(class {0}* node) = 0;\n"
    .format(name) for (name, _) in result])
  include_list = "".join([
    '#include "{0}Visitor.h"\n'
    .format(vis) for (vis) in visitors])
  visitor_c = wt_visitor.format(pure_list, include_list)
  with open('generated/Visitor.h', 'w') as file:
    file.write(visitor_c)

  for name, values in result:
    entries = [(t, v) for _, t, v in entry_eng.findall(values)]
    comma_list = ", ".join(["{0} {1}".format(t, v) for (t, v) in entries])
    arrow_list = "".join(["  node->{1} = {1};\n".format(t, v) for (t, v) in entries])
    class_c = wt_mknode.format(name=name, comma_list=comma_list, arrow_list=arrow_list) 
    mknode_c += class_c
  with open('generated/mknode.h', 'w') as file:
    file.write(mknode_c)
  
  for vis in visitors:
    declare_list = "".join([\
      '  virtual void visit(class {0}* node);\n'\
      .format(t) for (t, _) in result
    ])
    header_c = wt_headers.format(declare_list, name = vis)
    with open("generated/" + vis + "Visitor.h", 'w') as file:
      file.write(header_c)


def main():
  visitors = []
  for filename in os.listdir("."):
    result = re.match("(.*)Visitor.cpp", filename)
    if result:
      visitors.append(result.groups()[0])

  with open("common.h") as file:
    comment_eng = re.compile("^(.*?)(//|$)")
    con = file.read()
    new_con = ""
    for line in con.splitlines():
      # print(comment_eng.match(line).groups())
      new_con += comment_eng.match(line).groups()[0] + '\a'
    # print(new_con)
    parse(new_con, visitors)

main()
