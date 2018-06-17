// Template
#include "generated/StaticAnalyseVisitor.h"
#include "indent.h"
#include "drivers/class_decl.h"
/*
  const FuncEntry& binded_function;
  const ClassEntries& sym_table;
  BlockExt* current_block;
 public:
  StaticAnalyseVisitor(const ClassEntries& sym_table, const FuncEntry& binded_function);
*/
StaticAnalyseVisitor::StaticAnalyseVisitor(const ClassEntries &sym_table, const FuncEntry &binded_function)
    : sym_table(sym_table), binded_function(binded_function) {
  current_block = nullptr;
}

void StaticAnalyseVisitor::visit(Integer* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Double* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(NullPointer* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Call* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Index* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(MemberDot* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(NewArray* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(New* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Read* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(UnaryExpr* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(BinaryExpr* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(This* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Print* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(List* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Break* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Return* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(For* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(While* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Block* node) {
  // TODO
  // set parent
  node->aux.parent = current_block;
  // point to here
  current_block = &node->aux;
}

void StaticAnalyseVisitor::visit(If* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Prototype* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Interface* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(ClassDecl* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(FunctionDecl* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(TypeArray* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(TypeBase* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(TypeUser* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Identifier* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Assign* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(TypedVariable* node) {
  // CreateDeclForVariables

}

void StaticAnalyseVisitor::visit(Program* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(NoAction* node) {
  // TODO
}


