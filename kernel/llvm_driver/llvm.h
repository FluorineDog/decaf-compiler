#pragma once
#include "llvm_inc.h"
#include "../generated/CodegenVisitor.h"
using namespace llvm;
using std::string;

class LLVMEngine {
 public:
  LLVMEngine();
   
  void insert_type(string name);
  void create_main(Block*);
//  BasicBlock* getBasicBlock();
  void define_local_variable(int uid, string type);
  Value* fetch_local_id(int uid);
  PointerType* get_user_type(string name);

  IRBuilder<>& operator()(){
    return builder;
  }

  LLVMContext& getContext(){
    return theContext;
  }
  void final_print(){
    theModule->print(errs(), nullptr);
  }

 private:
  Function* load_extfunc(string name);
  LLVMContext theContext;
  SMDiagnostic error;
  std::unique_ptr<Module> extModule;
  std::unique_ptr<Module> theModule;
  std::map<string, Function*> util_func;
  std::map<string, Type*> type_dict;
  std::map<int, Value*> local_table;
  IRBuilder<> builder;
};
