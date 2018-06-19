#include "llvm.h"
void codegen(ClassEntries& sym_table) {
  LLVMEngine eng;
  //
  for(auto [decl_name, decl_x]: sym_table){
    if(decl_name == "Program"){
      continue;
    }
    eng.insert_type(decl_name);
  }
  for(auto [decl_name, decl_x]: sym_table){
    if(decl_name == "Program"){
      assert(std::holds_alternative<ClassBody>(decl_x));
      auto& decl = std::get<ClassBody>(decl_x);
      // only main is permitted
      assert(decl.functions.size() == 1);
      assert(decl.variables.size() == 0);
      auto& [main_name, main_func] = decl.functions[0];
      assert(main_name == "main");
      assert(main_func.return_type == "int");
      assert(main_func.parameters.size() == 0);
      std::cerr << "main checked" << std::endl;
    }
  }

}