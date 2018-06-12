#!/bin/python
import re
import os

class_tmp = "class (\w+) *: *public ASTNodeBase.*?virtual.*?\a(.*?)};"
entry_tmp = "(^|\a)[ ]*?(\w+) (\w+);"

wt_mknode = '''
inline auto mk{name}({comma_list}) {{
  auto node = new {name};
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
#include "node_defs.h"
class {name}Visitor : public Visitor {{
{0}
}};
'''
wt_source_aux = '''// Template
#include "generated/{vis}Visitor.h"
#include "internal.h"
/*
*/
'''

wt_source = '''{aux_list}{func_list}
'''

wt_source_func = \
'''void {vis}Visitor::visit({type}* node) {{
{body}
}}

'''

def parse(content, visitors):
  class_eng = re.compile(class_tmp)
  entry_eng = re.compile(entry_tmp)
  result = class_eng.findall(content)
  nodes = [name for (name, _) in result]
  mknode_c = '#include "../common.h"'

  print(visitors)
  pure_list = "".join([
    "  virtual void visit(class {0}* node) = 0;\n"
    .format(name) for name in nodes])
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

  def mkRule(name): return "  {n} {l}*u{n};".format(n=name, l = " "*(16-len(name)))
  with open("../parser/generated/union.gen.yxx", 'w') as file:
    content_c = '\n'.join([mkRule(name) for name in nodes])
    file.write(content_c)

  with open('generated/mknode.h', 'w') as file:
    file.write(mknode_c)
  genVisCpp(visitors, nodes)


def fetch(content):
  start = content.find("/*")
  end = content.find("*/")
  if start == -1:
    return ''
  content = content[start:end + 2]
  cc = "\n".join(content.splitlines()[1:-1])
  return cc

def genTable(content, vis):
  table_tmp = '''void {vis}Visitor::visit\((\w+).*?({{.*?\n\}})'''.format(vis=vis)
  print(table_tmp)
  func = re.findall(table_tmp, content, re.DOTALL)
  def fuck(cc): return "\n".join(cc.splitlines()[1:-1])
  table = dict()
  for name, body in func:
    table[name] =  fuck(body) 
  # print(table) 
  # print(' ' in table)
  # print('Integer' in table)
  return table

def genAux(content, vis):
  end = content.find("void {vis}Visitor::visit(".format(vis=vis))
  if end == -1:
    return wt_source_aux.format(vis=vis)
  return content[0:end]
   
  
def genVisCpp(visitors, nodes):
  for vis in visitors:
    declare_list = "".join([\
      '  virtual void visit(class {0}* node);\n'\
      .format(t) for t in nodes
    ])
    with open(vis + "Visitor.cpp") as file:
      content = file.read()
      variable_list = fetch(content)
      refer = genTable(content, vis)

    header_c = wt_headers.format(declare_list + variable_list, 
        name = vis)
    with open("generated/" + vis + "Visitor.h", 'w') as file:
      file.write(header_c)
    
    pass
    def gen_body(t): return refer[t] if t in refer else "  // TODO" 
    def gen_func(t): return wt_source_func.format(vis=vis, type=t, body=gen_body(t)) 
    func_list = "".join([\
      gen_func(t) for t in nodes
    ])
    aux_list = genAux(content, vis)
    source_c = wt_source.format(vis=vis, 
        func_list=func_list,
        aux_list=aux_list
    )
    pass
    with open("generated/template/" + vis + "Visitor.cpp", 'w') as file:
      file.write(source_c)
    
    with open("" + vis + "Visitor.cpp", 'w') as file:
      file.write(source_c)

def main():
  visitors = []
  for filename in os.listdir("."):
    result = re.match("(.*)Visitor.cpp", filename)
    if result:
      visitors.append(result.groups()[0])

  with open("node_defs.h") as file:
    comment_eng = re.compile("^(.*?)(//|$)")
    con = file.read()
    new_con = ""
    for line in con.splitlines():
      # print(comment_eng.match(line).groups())
      new_con += comment_eng.match(line).groups()[0] + '\a'
    # print(new_con)
    parse(new_con, visitors)
main()
