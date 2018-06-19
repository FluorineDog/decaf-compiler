#pragma once
#include "llvm_inc.h"
using namespace llvm;
using std::string;

class LLVMEngine {
 public:
  LLVMEngine();
   
  void insert_type(string name); 
 private:
  Function* load_extfunc(string name);
  LLVMContext theContext;
  SMDiagnostic error;
  std::unique_ptr<Module> extModule;
  std::unique_ptr<Module> theModule;
  std::map<string, Function*> util_func;
  std::map<string, Type*> type_dict;
};
