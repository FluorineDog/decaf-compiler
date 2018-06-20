#include "llvm.h"

LLVMEngine::LLVMEngine()
  :visitor(*this)
{
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
  constexpr const char* c_extnames[] = {"readint", "refint", "readline",
                                        "printss"};
  for (auto str : c_extnames) {
    util_func[str] = load_extfunc(str);
  }
}

Function* LLVMEngine::load_extfunc(string name) {
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

void LLVMEngine::create_main(Block* node){
  auto FT = FunctionType::get(type_dict["int"], {}, false);
  auto main_f = Function::Create(FT, Function::ExternalLinkage, "main", theModule.get());
  IRBuilder<> builder(theContext);

}

