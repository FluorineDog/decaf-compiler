#pragma once
#include "common.h"
class PrintVisitor : public Visitor{
  virtual void visit(class Integer* node);
  virtual void visit(class BinaryExpr* node);
  virtual void visit(class Sentence* node);
};
