#include "llvm.h"


LLVMEngine::LLVMEngine() {
  // init module
  extModule = parseIRFile("llvm/runtime.bc", error, theContext, false);
  theModule = llvm::make_unique<Module>("dog-decaf", theContext);

  // load basic type
  auto str_type = extModule->getTypeByName("struct.string");
  type_dict["string"] = str_type->getPointerTo();
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