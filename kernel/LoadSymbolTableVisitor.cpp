// Template
#include "generated/LoadSymbolTableVisitor.h"
#include "internal.h"
#include "symbol_table/class_decl.h"
/*
 public:
  ClassBody class_body;
  string current_class;
  string current_func;
*/
void LoadSymbolTableVisitor::visit(Integer* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Double* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(NullPointer* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Call* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Index* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(MemberDot* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(NewArray* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(New* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Read* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(UnaryExpr* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(BinaryExpr* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(This* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Print* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(List* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Break* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Return* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(For* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(While* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Block* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(If* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(ProtoType* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Interface* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(ClassDecl* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(FunctionDecl* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(TypeArray* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(TypeBase* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(TypeUser* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Identifier* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Assign* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(TypedVariable* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Program* node) {
  // TODO
  node->accept(*this); // goto functions
}

void LoadSymbolTableVisitor::visit(NoAction* node) {
  // TODO
}


