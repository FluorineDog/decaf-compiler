
#include <llvm/IR/Function.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>
namespace {

using namespace llvm;
struct Hello : public FunctionPass {
  static char ID;
  Hello() : FunctionPass(ID) {}
  bool runOnFunction(Function &F) override {
    errs() << "Hellos: " ;
    errs().write_escaped(F.getName()) << '\n';
    return false;
  }
};

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "hw pass", false, false);

}