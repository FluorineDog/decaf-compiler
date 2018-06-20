#include "llvm.h"

LLVMEngine::LLVMEngine()
    : builder(theContext) {
  // init module
  extModule = parseIRFile("llvm/runtime.bc", error, theContext, false);
  theModule = llvm::make_unique<Module>("dog-decaf", theContext);
  assert(extModule);
  assert(theModule);
  // load basic type
  auto str_type = extModule->getTypeByName("struct.string")->getPointerTo();
  // use pointer deliberately. Use as basic type
  type_dict["string"] = str_type;
  type_dict["int"] = Type::getInt32Ty(theContext);
  type_dict["double"] = Type::getDoubleTy(theContext);
  type_dict["bool"] = Type::getInt1Ty(theContext);
  type_dict["void"] = Type::getVoidTy(theContext);

  // load external function
  constexpr const char *c_extnames[] = {"readint", "refint", "readline",
                                        "printss"};
  for (auto str : c_extnames) {
    util_func[str] = load_extfunc(str);
  }
}

Function *LLVMEngine::load_extfunc(string name) {
  assert(extModule);
  auto callee = extModule->getFunction(name);
  Function::Create(callee->getFunctionType(), Function::ExternalLinkage,
                   callee->getName(), theModule.get());
  return callee;
}

void LLVMEngine::insert_type(string name) {
  auto t = StructType::create(theContext, name);
  type_dict[name] = t;
}

void LLVMEngine::create_main(Block *node) {
  auto FT = FunctionType::get(type_dict["int"], {}, false);
  auto F = Function::Create(FT, Function::ExternalLinkage, "main", theModule.get());
  BasicBlock *BB = BasicBlock::Create(theContext, "entry", F);
  builder.SetInsertPoint(BB);
  local_table.clear();
  CodegenVisitor visitor(*this, nullptr);
  visitor << node;
  // no concept of block
}

void LLVMEngine::define_local_variable(int uid, string type) {
  assert(!local_table.count(uid));
  auto var = builder.CreateAlloca(type_dict[type], nullptr, "local_decl");
  local_table[uid] = var;
}

Value* LLVMEngine::fetch_local_id(int uid){
  assert(local_table.count(uid));
  return local_table[uid];
}


PointerType* LLVMEngine::get_user_type(string name){
  // TODO
  return nullptr;
}
