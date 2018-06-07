#pragma once
class Visitor {
 public:
  virtual void visit(class Integer* node) = 0;
  virtual void visit(class BinaryExpr* node) = 0;
  virtual void visit(class Block* node) = 0;
 // Generated
};
#include "BbVisitor.h"
#include "PrintVisitor.h"
 
