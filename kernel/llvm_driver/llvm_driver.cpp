#include "llvm.h"
void codegen(ClassEntries& sym_table) {
  LLVMEngine eng;
  //
  for(auto [decl_name, decl_x]: sym_table){
    if(decl_name == "Main"){
      continue;
    }
    eng.insert_type(decl_name);
  }
  for(auto [decl_name, decl_x]: sym_table){
    if(decl_name == "Main"){
      assert(std::holds_alternative<ClassBody>(decl_x));
      auto& decl = std::get<ClassBody>(decl_x);
      // only main is permitted
      assert(decl.functions.size() == 1);
      assert(decl.variables.size() == 0);
      auto& [main_name, main_func] = decl.functions[0];
      assert(main_name == "main");
      assert(main_func.return_type == "int");
      assert(main_func.parameters.size() == 0);
//      std::cerr << "main checked" << std::endl;
//      visitor << main_func.body;
//      visitor.
      assert(main_func.body);
      eng.create_main(main_func.body.value());
    }
  }
  eng.final_print();
}