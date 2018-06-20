// Template
#include "generated/CodegenVisitor.h"
#include "indent.h"
#include "llvm_driver/llvm_inc.h"
/*
 private:
  class LLVMEngine& eng;
  llvm::Value* rt_value;
  llvm::Type* rt_type;
  CodegenVisitor& operator<<(node_ptr_t node){
    node->accept(*this);
    return *this;
  }
 public:
  CodegenVisitor(class LLVMEngine& eng);
  llvm::Value* get_value(node_ptr_t node);
  llvm::Type* get_type(node_ptr_t node);
*/
using namespace llvm;
#include "llvm_driver/llvm.h"
CodegenVisitor::CodegenVisitor(LLVMEngine& eng)
  :eng(eng)
{
}

Value* CodegenVisitor::get_value(node_ptr_t node){
  rt_value = nullptr;
  *this << node;
  assert(rt_value);
  return rt_value;
}
Type* CodegenVisitor::get_type(node_ptr_t node){
  rt_type = nullptr;
  *this << node;
  assert(rt_type);
  return rt_type;
}

void CodegenVisitor::visit(Integer* node) {
  // TODO
}

void CodegenVisitor::visit(Double* node) {
  // TODO
}

void CodegenVisitor::visit(NullPointer* node) {
  // TODO
}

void CodegenVisitor::visit(Call* node) {
  // TODO
}

void CodegenVisitor::visit(Index* node) {
  // TODO
}

void CodegenVisitor::visit(MemberDot* node) {
  // TODO
}

void CodegenVisitor::visit(NewArray* node) {
  // TODO
}

void CodegenVisitor::visit(New* node) {
  // TODO
}

void CodegenVisitor::visit(Read* node) {
  // TODO
}

void CodegenVisitor::visit(UnaryExpr* node) {
  // TODO
}

void CodegenVisitor::visit(BinaryExpr* node) {
  // TODO
}

void CodegenVisitor::visit(This* node) {
  // TODO
}

void CodegenVisitor::visit(Print* node) {
  // TODO
}

void CodegenVisitor::visit(List* node) {
  // TODO
}

void CodegenVisitor::visit(Break* node) {
  // TODO
}

void CodegenVisitor::visit(Return* node) {
  // TODO
}

void CodegenVisitor::visit(For* node) {
  // TODO
}

void CodegenVisitor::visit(While* node) {
  // TODO
}

void CodegenVisitor::visit(Block* node) {
  // TODO
}

void CodegenVisitor::visit(If* node) {
  // TODO
}

void CodegenVisitor::visit(Prototype* node) {
  // TODO
}

void CodegenVisitor::visit(Interface* node) {
  // TODO
}

void CodegenVisitor::visit(ClassDecl* node) {
  // TODO
}

void CodegenVisitor::visit(FunctionDecl* node) {
  // TODO
}

void CodegenVisitor::visit(TypeArray* node) {
  // TODO
}

void CodegenVisitor::visit(TypeBase* node) {
  // TODO
}

void CodegenVisitor::visit(TypeUser* node) {
  // TODO
}

void CodegenVisitor::visit(Identifier* node) {
  // TODO
}

void CodegenVisitor::visit(Assign* node) {
  // TODO
}

void CodegenVisitor::visit(TypedVariable* node) {
  // TODO
}

void CodegenVisitor::visit(Program* node) {
  // TODO
}

void CodegenVisitor::visit(NoAction* node) {
  // TODO
}


