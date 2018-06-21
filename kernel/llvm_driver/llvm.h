#pragma once
#include "llvm_inc.h"
#include "llvm/Support/raw_ostream.h"
#include "../generated/CodegenVisitor.h"

#include "llvm/Support/FileSystem.h"

using namespace llvm;
using std::string;

class LLVMEngine {
public:
  LLVMEngine(ClassEntries& sym_table);

  void insert_type(string name);
  void grant_id(string name);
  int fetch_type_uid(string name);
  void create_main(Block *);
//  BasicBlock* getBasicBlock();
  void define_local_variable(int uid, string type);
  Value *fetch_local_id(int uid);
  Type *get_type(string name);
  StructType *get_struct(string name);
  void create_func(FuncEntry &entry);
  auto create_IntObj(int val){
    return ConstantInt::get(theContext, APInt(32, val, true));
  }
  int fetch_variable_uid(string class_name, string ident){
    return sym_table.fetch_variable_uid(class_name, ident);
  }

  IRBuilder<> &operator()() {
    return builder;
  }

  int get_sizeof(Type*);

  Function *load_ext_func(string name) {
    assert(util_func.count(name));
    return util_func[name];
  }

  LLVMContext &getContext() {
    return theContext;
  }

  void createDummy() {
    Function *tf = builder.GetInsertBlock()->getParent();
    auto dummyBB = BasicBlock::Create(theContext, "dummy", tf);
    builder.SetInsertPoint(dummyBB);
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
  ClassEntries& sym_table;
  std::unique_ptr<Module> extModule;
  std::unique_ptr<Module> theModule;
  std::map<string, Function *> util_func;
  std::map<string, Type *> builtin_type_dict;
  std::map<string, StructType *> user_type_dict;
  std::map<string, int> class_ids;
  std::map<int, Value *> local_table;
  IRBuilder<> builder;
};
