#include "llvm.h"
#include <variant>
void codegen(ClassEntries &sym_table) {
  LLVMEngine eng(sym_table);
  // insert types
  for (auto&[decl_name, decl_x]: sym_table) {
    if (decl_name == "Main") {
      continue;
    }
    eng.insert_type(decl_name);
//    if (std::holds_alternative<ClassBody>(decl_x)) {
//      eng.grant_class_id(decl_name);
//    }
  }

  for (auto&[decl_name, decl_x]: sym_table) {
    if (decl_name == "Main") {
      continue;
    }
    // no interface, sir
    if (std::holds_alternative<InterfaceBody>(decl_x)) {
      continue;
    }

    auto &decl = std::get<ClassBody>(decl_x);
    auto struct_type = eng.get_struct(decl_name);
    // build type
    {
      vector<Type *> body;
      // use as type_uid
      stack<string> wtf;

      body.push_back(eng.external.table_type->getPointerTo());

      for (auto&[var_name, var_type]: decl.available.variables) {
        body.push_back(eng.get_type(var_type));
      }
      struct_type->setBody(body);
    }
    // declare function
    {
      for(auto& [func_name, func_body]:decl.functions){
        eng.declare_func(decl_name, func_name, func_body);
      }
    }
  }

  eng.create_call_table();
  for (auto&[decl_name, decl_x]: sym_table) {
    if (decl_name == "Main") {
      assert(std::holds_alternative<ClassBody>(decl_x));
      auto &decl = std::get<ClassBody>(decl_x);
      // only main is permitted
      assert(decl.functions.size() == 1);
      assert(decl.variables.size() == 0);
      auto&[main_name, main_func] = decl.functions[0];
      assert(main_name == "main");
      assert(main_func.return_type == "int");
      assert(main_func.parameters.size() == 0);
//      std::cerr << "main checked" << std::endl;
//      visitor << main_func.body;
//      visitor.
      assert(main_func.body);
      eng.create_main(main_func.body.value());
      continue;
    }

    if (std::holds_alternative<ClassBody>(decl_x)) {
      auto& decl = std::get<ClassBody>(decl_x);
      for(auto& [func_name, func_body]:decl.functions){
        eng.define_func(decl_name, func_name, func_body);
      }
    } else {

    }

  }
  eng.final_print();
}