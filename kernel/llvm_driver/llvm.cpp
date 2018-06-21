#include "llvm.h"

LLVMEngine::LLVMEngine(ClassEntries &sym_table)
    : builder(theContext), sym_table(sym_table) {
  // init module
  extModule = parseIRFile("final_build/runtime.bc", error, theContext, false);
  theModule = llvm::make_unique<Module>("dog-decaf", theContext);
  assert(extModule);
  assert(theModule);
  // load basic type
  auto str_type = extModule->getTypeByName("struct.string");
  // use pointer deliberately. Use as basic type
  builtin_type_dict["string"] = str_type->getPointerTo();
  builtin_type_dict["int"] = Type::getInt32Ty(theContext);
  builtin_type_dict["double"] = Type::getDoubleTy(theContext);
  builtin_type_dict["bool"] = Type::getInt1Ty(theContext);
  builtin_type_dict["void"] = Type::getVoidTy(theContext);
  builtin_type_dict["nullptr"] = Type::getInt8PtrTy(theContext);

  // load user type
  user_type_dict["string"] = str_type;

  // load external function
  constexpr const char *c_extnames[] = {"readint", "readline", "printint", "printdouble", "printbool",
                                        "printstring", "string_cat", "dog_malloc"};
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
void LLVMEngine::grant_id(string name) {
  int uid = class_ids.size();
  class_ids[name] = uid;
}

int LLVMEngine::fetch_type_uid(string name) {
  assert(class_ids.count(name));
  return class_ids.at(name);
}

void LLVMEngine::insert_type(string name) {
  assert(!user_type_dict.count(name));
  auto t = StructType::create(theContext, name);
  user_type_dict[name] = t;
}

void LLVMEngine::define_local_variable(int uid, string type) {
  assert(!local_table.count(uid));
  auto var = builder.CreateAlloca(get_type(type), nullptr, "local_decl");
  local_table[uid] = var;
}

Value *LLVMEngine::fetch_local_id(int uid) {
  assert(local_table.count(uid));
  return local_table[uid];
}

StructType *LLVMEngine::get_struct(string name) {
  // TODO
  assert(user_type_dict.count(name));
  return user_type_dict[name];
}

Type *LLVMEngine::get_type(string name) {
  // TODO
  if (builtin_type_dict.count(name)) {
    return builtin_type_dict[name];
  }
  assert(user_type_dict.count(name));
  return user_type_dict[name]->getPointerTo();
}

int LLVMEngine::get_sizeof(Type *type) {
  DataLayout layout(theModule.get());
  return layout.getTypeAllocSize(type);
}

void LLVMEngine::create_main(Block *node) {
  auto FT = FunctionType::get(get_type("int"), {}, false);
  auto F = Function::Create(FT, Function::ExternalLinkage, "main", theModule.get());
  BasicBlock *BB = BasicBlock::Create(theContext, "entry", F);
  builder.SetInsertPoint(BB);
  local_table.clear();
  CodegenVisitor visitor(*this, nullptr);
  visitor << node;
  // no concept of block
}

void LLVMEngine::create_func(string class_name, string function, FuncEntry &body) {
  auto ret = get_type(body.return_type);
  vector<Type *> paras;
  for (auto[type, _]: body.parameters) {
    paras.push_back(get_type(type));
  }
  auto FT = FunctionType::get(ret, paras, false);
  auto F = Function::Create(FT, Function::ExternalLinkage, function, theModule.get());
//  builder.CreatePointerCast(F, get_type("nullptr"));
  BasicBlock *BB = BasicBlock::Create(theContext, "entry", F);
  builder.SetInsertPoint(BB);
  local_table.clear();

}
