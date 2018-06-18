#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
using namespace llvm;

int main() {
  LLVMContext TheContext;
  IRBuilder<> Builder(TheContext);
  std::unique_ptr<Module> TheModule;
  // std::map<std::string, Value *> NamedValues;
  std::vector<Type *> Paras;
  FunctionType *FT =
      FunctionType::get(Type::getInt32Ty(TheContext), Paras, false);

  Function *F = Function::Create(FT, Function::ExternalLinkage,
                                 "main", TheModule.get());

  BasicBlock *BB = BasicBlock::Create(TheContext, "god_see", F);
  Builder.SetInsertPoint(BB);

  auto s = ConstantInt::get(TheContext, APInt(32, 42, true));
  Builder.CreateRet(s);
  F->print(errs()); 
  // TheModule->print(errs(), nullptr);
}