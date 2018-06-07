#include "generated/PrintVisitor.h"
#include "internal.h"
void PrintVisitor::visit(class Integer* node){
  cout << "1";
}
void PrintVisitor::visit(class BinaryExpr* node){
  cout << "2";
}
void PrintVisitor::visit(class Block* node){
  cout << "3";
}
