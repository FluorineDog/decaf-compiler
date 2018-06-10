#pragma once
#include "common.h"
class Integer : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  int num;
};

class BinaryExpr : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t left;
  int op;
  node_ptr_t right;
};

class Block : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  vector<node_ptr_t> stmts;  // advanced container will be omitted
};

class Type : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  int type;
};
