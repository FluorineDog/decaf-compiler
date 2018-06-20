#pragma once
#include "llvm_inc.h"
#include "llvm/Support/raw_ostream.h"
#include "../generated/CodegenVisitor.h"

#include "llvm/Support/FileSystem.h"

using namespace llvm;
using std::string;

class LLVMEngine {
public:
  LLVMEngine();

  void insert_type(string name);
  void create_main(Block *);
//  BasicBlock* getBasicBlock();
  void define_local_variable(int uid, string type);
  Value *fetch_local_id(int uid);
  PointerType *get_user_type(string name);
  Type* get_basic_type(string name);

  IRBuilder<> &operator()() {
    return builder;
  }

  Function* load_ext_func(string name){
    assert(util_func.count(name));
    return util_func[name];
  }

  LLVMContext &getContext() {
    return theContext;
  }
  void final_print() {
    std::error_code err;
    llvm::raw_fd_ostream file("final_build/main.ll", err, sys::fs::F_RW);
    theModule->print(file, nullptr);
  }

private:
  Function *load_extfunc(string name);
  LLVMContext theContext;
  SMDiagnostic error;
  std::unique_ptr<Module> extModule;
  std::unique_ptr<Module> theModule;
  std::map<string, Function *> util_func;
  std::map<string, Type *> type_dict;
  std::map<int, Value *> local_table;
  IRBuilder<> builder;
};
