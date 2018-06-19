#include "external.h"
#include "drivers/class_decl.h"
#include "drivers/static_analyse.h"
node_ptr_t root;

int main() {
  freopen("/home/mike/compiler/data/naive.decaf", "r", stdin);
  yyparse();


  ClassEntries ce;
  {
    LoadSymbolTableVisitor v;
    root->accept(v);
    ce = std::move(v.top_pool);
  }
  print_sym_table(ce);
  static_analyse(ce);
  if (true) {
    PrintVisitor v;
    root->accept(v);
  }
}
