#include "llvm.h"
#include "../static_analyse_driver/class_decl.h"

void codegen(ClassEntries& sym_table) {
  LLVMEngine eng;
  //
  for(auto [decl_name, decls]: sym_table){
    if(decl_name == "Program"){
      continue;
    }
    eng.insert_type(decl_name);
  }
  for(auto [decl_name, decls]: sym_table){
    if(decl_name == "Program"){
      // assert(decls->list);
    }
  }

}