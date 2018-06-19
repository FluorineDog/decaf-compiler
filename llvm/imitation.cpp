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
#include "llvm/IR/TypeBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"

#include <fstream>
using std::string;
using namespace llvm;

int main() {
  LLVMContext TheContext;
  SMDiagnostic error;
  // std::ifstream
  // fin("/home/mike/workspace/compiler/llvm_playground/lib/runtime.h.gch",
  // std::ios::binary);
  auto ExtModule = parseIRFile("runtime.bc", error, TheContext, false);
  auto TheModule = llvm::make_unique<Module>("my cool jit", TheContext);
  // TheModule->setPICLevel(PICLevel::NotPIC);
  assert(TheModule);
  assert(ExtModule);
  auto loadfc = [&](string name) {
    auto callee = ExtModule->getFunction(name);
    Function::Create(callee->getFunctionType(), Function::ExternalLinkage,
                     callee->getName(), TheModule.get());
    return callee;
  };
  auto CalleeF1 = loadfc("readint");
  auto CalleeF2 = loadfc("refint");
  auto CalleeF3 = loadfc("readline");
  auto CalleeF4 = loadfc("printss");
  assert(CalleeF3);
  assert(CalleeF4);
  // auto CalleeF2 = ExtModule->getFunction("refint");
  // TheModule->getOrInsertFunction(CalleeF2->getName(),
  //  CalleeF2->getFunctionType());

  // Function::Create(CalleeF2->getFunctionType(), Function::ExternalLinkage,
  //  "refint", TheModule.get());

  // TheModule->setPICLevel(PICLevel::BigPIC);
  // std::map<std::string, Value *> NamedValues;
  {
    std::vector<Type *> Paras;
    auto IntType = Type::getInt32Ty(TheContext);
    FunctionType *FT = FunctionType::get(IntType, Paras, false);

    Function *F = Function::Create(FT, Function::ExternalLinkage, "main",
                                   TheModule.get());

    BasicBlock *BB = BasicBlock::Create(TheContext, "god_see", F);
    IRBuilder<> Builder(TheContext);
    Builder.SetInsertPoint(BB);

    {
      // auto t = StructType::create(
          // {},
          //  {Type::getInt32Ty(TheContext), Type::getInt8PtrTy(TheContext)},
          // "struct.string");
      // auto t2 = ExtModule->getTypeByName("struct.string");
      auto t = StructType::create(TheContext, "struct.string");
      assert(t);
      auto pt = t->getPointerTo();
      t->setBody(
          {Type::getInt32Ty(TheContext), Type::getInt8PtrTy(TheContext)} );
      // auto pt =
      auto ai = Builder.CreateAlloca(pt, nullptr, "node");
      // auto ai2 = Builder.CreateAlloca(t2, nullptr, "node2");
      auto call = Builder.CreateCall(CalleeF3, {}, "calltmp");
      auto st = Builder.CreateStore(call, ai);
      auto ld = Builder.CreateLoad(ai, "ld");
      // {
      //   auto index = ConstantInt::get(TheContext, APInt(32, 0, true));
      //   auto memAddr = Builder.CreateGEP(ld, {index, index}, "lenAddr");
      //   auto mem = Builder.CreateLoad(memAddr, "len");
      //   auto mem2 = Builder.CreateAdd(mem, mem, "mem2");
      //   auto st2 = Builder.CreateStore(mem2, memAddr);
      // }
      auto call2 = Builder.CreateCall(CalleeF4, {ld}, "");
    }
    {
      auto ai = Builder.CreateAlloca(Type::getInt32Ty(TheContext), 0, "tmp");
      auto const66 = ConstantInt::get(TheContext, APInt(32, 100, true));
      auto st = Builder.CreateStore(const66, ai);
      auto ld = Builder.CreateLoad(ai, "ld");
      auto call = Builder.CreateCall(CalleeF1, {}, "calltmp");
      auto add = Builder.CreateAdd(ld, call, "addtmp");
      auto s2 = Builder.CreateCall(CalleeF2, {add}, "calltmp");
      Builder.CreateRet(s2);
    }
    // F->print(errs());
  }
  // ExtModule->print(errs(), nullptr);
  TheModule->print(errs(), nullptr);
}