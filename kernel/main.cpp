#include "external.h"
node_ptr_t root;

int main(){
  freopen("/home/mike/compiler/data/list.decaf", "r", stdin);
  yyparse();
  if (true) {
    PrintVisitor v;
    root->accept(v);
  } 
  LoadSymbolTableVisitor v;
  root->accept(v);
  print(v.top_pool);
}
