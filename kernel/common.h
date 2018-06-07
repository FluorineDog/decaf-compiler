#pragma once
#include <memory>
#include <string>
#include <vector>
using std::make_shared;
using std::shared_ptr;
using std::vector;
// using Location = int;
class ASTNodeBase {
 public:
  virtual void accept(class Visitor& v) = 0;
  // Location loc_beg;
  // Location loc_end;
};
using node_ptr_t = shared_ptr<ASTNodeBase>;

#include "generated/Visitor.h"
class Integer : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  Integer(int num) : num(num) {}
  int num;
};

class BinaryExpr : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  BinaryExpr(node_ptr_t left, int op, node_ptr_t right)
      : left(left), op(op), right(right) {}
  node_ptr_t left;
  int op;
  node_ptr_t right;
};

class Block : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  vector<node_ptr_t> stmts;
};
