#include "llvm.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

LLVMEngine::LLVMEngine(ClassEntries &sym_table)
    : builder(theContext), sym_table(sym_table) {
  // init module
  extModule = parseIRFile("final_build/runtime.bc", error, theContext, false);
  theModule = llvm::make_unique<Module>("dog-decaf", theContext);
  assert(extModule);
  assert(theModule);
  theModule->setPICLevel(PICLevel::BigPIC);
  // load basic type
  auto str_type = extModule->getTypeByName("struct.string");
  external.entry_type = extModule->getTypeByName("struct.__entry");
  external.table_type = extModule->getTypeByName("struct.__sym_table");

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
                                        "printstring", "string_cat", "dog_malloc", "load_ptr"};
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
//void LLVMEngine::grant_class_id(string name) {
//  int uid = class_ids.size();
//  class_ids[name] = uid;
//}
//
//int LLVMEngine::fetch_class_uid(string name) {
//  assert(class_ids.count(name));
//  return class_ids.at(name);
//}

void LLVMEngine::insert_type(string name) {
  assert(!user_type_dict.count(name));
  auto t = StructType::create(theContext, name);
  user_type_dict[name] = t;
}

void LLVMEngine::define_local_variable(int uid, string type) {
  if (local_table.count(uid)) {
    return;
  }
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
  CodegenVisitor visitor(*this, nullptr, "");
  visitor << node;
  // no concept of block
}

int LLVMEngine::load_class_from(string class_name, Argument &para_void) {
  auto para_ptr = builder.CreateBitOrPointerCast(&para_void, get_type(class_name));
  local_table[-1] = para_ptr;
  auto &body = sym_table.fetch_complete_class(class_name);
  auto len = body.available.variables.size();
  for (int i = 0; i < len; i++) {
    auto val = builder.CreateGEP(para_ptr, {create_IntObj(0), create_IntObj(i + 1)});
    local_table[i] = val;
  }
  return len;
}

void LLVMEngine::declare_func(string class_name, string function, FuncEntry &body, bool is_class) {
  auto ret = get_type(body.return_type);
  vector<Type *> paras;
  paras.push_back(builder.getInt8PtrTy());
  for (auto[type, _]: body.parameters) {
    paras.push_back(get_type(type));
  }
  auto FT = FunctionType::get(ret, paras, false);
  func_type_table[class_name][function] = FT;
  if(is_class){
    auto F = Function::Create(FT, Function::ExternalLinkage, class_name + "__" + function, theModule.get());
    assert(F);
    func_table[class_name][function] = F;
  }
}

void LLVMEngine::define_func(string class_name, string function, FuncEntry &body) {

  auto F = func_table[class_name][function];
  BasicBlock *BB = BasicBlock::Create(theContext, "entry", F);
  builder.SetInsertPoint(BB);
  {
    // set up local_table
    local_table.clear();
    bool thisflag = true;
    int uid = 0;
    int len = F->arg_size();
    for (auto &para: F->args()) {
      if (thisflag) {
        uid = load_class_from(class_name, para);
        thisflag = false;
        continue;
      }
      auto tmp = builder.CreateAlloca(para.getType(), 0, nullptr, "arg_tmp");
      builder.CreateStore(&para, tmp);
      local_table[uid++] = tmp;
    }
  }
  CodegenVisitor visitor(*this, nullptr, class_name);
  visitor << body.body.value();
  if (body.return_type == "void") {
    builder.CreateRetVoid();
  }
};

void LLVMEngine::create_call_table() {
  // let me think

//  auto ele = ConstantStruct::get(external.entry_type, {create_IntObj(1234), create_nullptr()});
//  auto carrt = ArrayType::get(external.entry_type, 2);
//  auto carr = ConstantArray::get(carrt, {ele, ele});
//  auto mid = ConstantExpr::getGetElementPtr(external.entry_type->getPointerTo(), carr, {create_IntObj(0)});
//  auto var = new GlobalVariable(*theModule, carr->getType(),
//                                false, GlobalVariable::InternalLinkage, mid, "good");
//  auto np = create_nullptr(external.entry_type->getPointerTo());
//  auto cv = ConstantStruct::get(external.table_type,
//                                {create_IntObj(123), var});
//  auto vars = new GlobalVariable(*theModule, external.table_type,
//                                false, GlobalVariable::ExternalLinkage, cv, "good");
  int fuid = 0;
//  auto ele_t = ConstantStruct::get(external.entry_type, {});
  auto ele_t = external.entry_type;

  auto intify = [&](size_t i) {
    return builder.getInt64(i);
  };

  for (auto&[cname, func_list]: func_table) {
    map<int, Function *> elements;
    for (auto[fname, F]: func_list) {
      // get func's unique id
      if (!func_name_uid.count(fname)) {
        func_name_uid[fname] = fuid++;
      }
      auto uid = func_name_uid[fname];
      // insert into classes
      elements[uid] = F;
    }
    vector<Constant *> arr;
    cerr << arr.size();

    for (auto[uid, F]: elements) {
      auto ele = ConstantStruct::get(
          ele_t, {builder.getInt64(uid),
                  ConstantExpr::getBitCast(
                      F, Type::getInt8PtrTy(theContext))
          });
      arr.push_back(ele);
    }
    auto arr_t = ArrayType::get(ele_t, arr.size());
    auto arr_c = ConstantArray::get(arr_t, arr);
    auto sym_table_t = StructType::get(
        theContext,
        {Type::getInt64Ty(theContext), arr_t});
    auto sym_table_c = ConstantStruct::get(sym_table_t, {
        builder.getInt64(arr.size()),
        arr_c
    });

    auto gv = new GlobalVariable(
        *theModule,
        sym_table_t,
        true,
        GlobalVariable::PrivateLinkage,
        sym_table_c,
        "__sym_table_" + cname);
    sym_table_per_class[cname] = gv;
  }
}

llvm::Constant* LLVMEngine::fetch_sym_ptr(string class_name) {
  auto gv = sym_table_per_class.at(class_name);
  auto ptr = ConstantExpr::getBitCast(
      gv, external.table_type->getPointerTo());
  return ptr;
}


void LLVMEngine::define_func_empty(string class_name){
  func_table[class_name];
}
