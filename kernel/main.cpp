#include "external.h"
#include "static_analyse_driver/class_decl.h"
#include "static_analyse_driver/static_analyse.h"
node_ptr_t root;
#include "llvm_driver/llvm_external.h"

int main() {
  freopen("/home/mike/compiler/data/naive.decaf", "r", stdin);
  yyparse();
  assert(root);

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

  codegen(ce);
}
