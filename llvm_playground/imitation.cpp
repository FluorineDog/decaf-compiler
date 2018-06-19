#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"

#include <fstream>
using namespace llvm;

int main() {
  LLVMContext TheContext;
  SMDiagnostic error;
  // std::ifstream
  // fin("/home/mike/workspace/compiler/llvm_playground/lib/runtime.h.gch",
  // std::ios::binary);
  auto ExtModule = parseIRFile("runtime.bc", error, TheContext);
  auto TheModule = llvm::make_unique<Module>("my cool jit", TheContext);
  // TheModule->setPICLevel(PICLevel::NotPIC);
  assert(TheModule);
  assert(ExtModule);

  auto CalleeF1 = ExtModule->getFunction("readint");
  Function::Create(CalleeF1->getFunctionType(), Function::ExternalLinkage,
                   "readint", TheModule.get());
  auto CalleeF2 = ExtModule->getFunction("refint");
  TheModule->getOrInsertFunction(CalleeF2->getName(),
                                 CalleeF2->getFunctionType());
  // Function::Create(CalleeF2->getFunctionType(), Function::ExternalLinkage,
  //  "refint", TheModule.get());

  // TheModule->setPICLevel(PICLevel::BigPIC);
  // std::map<std::string, Value *> NamedValues;
  {
    std::vector<Type *> Paras;
    FunctionType *FT =
        FunctionType::get(Type::getInt32Ty(TheContext), Paras, false);

    Function *F = Function::Create(FT, Function::ExternalLinkage, "main",
                                   TheModule.get());

    BasicBlock *BB = BasicBlock::Create(TheContext, "god_see", F);
    IRBuilder<> Builder(TheContext);
    Builder.SetInsertPoint(BB);
    {
      auto ai = Builder.CreateAlloca(Type::getInt32Ty(TheContext), 0, "tmp");
      auto const66 = ConstantInt::get(TheContext, APInt(32, 100, true));
      auto st = Builder.CreateStore(const66, ai);
      auto ld = Builder.CreateLoad(ai, "ld");
      auto s = Builder.CreateCall(CalleeF1, {}, "calltmp");
      auto add = Builder.CreateAdd(ld, s, "addtmp");
      auto s2 = Builder.CreateCall(CalleeF2, {add}, "calltmp");

      Builder.CreateRet(s);
    }
    // F->print(errs());
  }
  // ExtModule->print(errs(), nullptr);
  TheModule->print(errs(), nullptr);
}