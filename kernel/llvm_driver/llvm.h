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

  void create_call_table();

  void insert_type(string name);
  void grant_class_id(string name);
  int fetch_class_uid(string name);
  void create_main(Block *);
//  BasicBlock* getBasicBlock();
  void define_local_variable(int uid, string type);
  Value *fetch_local_id(int uid);
  Type *get_type(string name);
  StructType *get_struct(string name);
  void declare_func(string class_name, string function, FuncEntry &entry);
  void define_func(string class_name, string function, FuncEntry &entry);

  auto create_nullptr(PointerType* type){
    return ConstantPointerNull::get(type);
  }
  auto create_nullptr(){
    auto type = Type::getInt8PtrTy(theContext);
    return ConstantPointerNull::get(type);
  }
  auto create_IntObj(int val){
    return ConstantInt::get(theContext, APInt(32, val, true));
  }
  int fetch_variable_uid(string class_name, string ident){
    return 1 + sym_table.fetch_variable_uid(class_name, ident);
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

  struct {
    StructType* entry_type;
    StructType* table_type;
  }external;
private:

  int load_class_from(string class_name, Argument& para);
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
  std::map<string, std::map<string, Function*>> func_table;
  std::map<int, Value *> local_table;
  std::map<string, int> func_name_uid;
  std::map<string, GlobalVariable*> sym_table_per_class;
  IRBuilder<> builder;
};
