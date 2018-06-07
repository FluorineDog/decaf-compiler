#include "generated/BbVisitor.h"
#include "internal.h"
void BbVisitor::visit(class Integer* node){
  cout << "1";
}
void BbVisitor::visit(class BinaryExpr* node){
  cout << "2";
}
void BbVisitor::visit(class Block* node){
  cout << "3";
}
