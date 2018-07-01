#include "external.h"
#include "static_analyse_driver/class_decl.h"
#include "static_analyse_driver/static_analyse.h"
node_ptr_t root;
#include "llvm_driver/llvm_external.h"

int main(int argc, char* argv[]) {
  assert(argc == 2);
  freopen(argv[1], "r", stdin);
  yyparse();
  assert(root);

  ClassEntries ce;
  {
    LoadSymbolTableVisitor v;
    root->accept(v);
    ce = std::move(v.top_pool);
  }

//  print_sym_table(ce);
  static_analyse(ce);
  if (true) {
    PrintVisitor v;
    root->accept(v);
  }

  codegen(ce);
}
