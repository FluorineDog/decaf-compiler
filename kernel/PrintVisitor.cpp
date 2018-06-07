#include "generated/PrintVisitor.h"
#include "internal.h"
void PrintVisitor::visit(class Integer* node) { 
  cout << node->num; 
}
void PrintVisitor::visit(class BinaryExpr* node) {
  node->left->accept(*this);
  cout << "<"  << node->op << ">";
  node->right->accept(*this);
}
void PrintVisitor::visit(class Block* node) {
  cout << "stmts" << node->stmts.size() << std::endl;
  for (auto& s : node->stmts) {
    s->accept(*this);
    cout << std::endl;
  }
}
