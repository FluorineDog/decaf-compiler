#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../build/parser.hxx"
using std::unique_ptr;
using std::vector;
// using Location = int;

class ASTNodeBase {
  virtual void accept(class Visitor& v) = 0;
  // Location loc_beg;
  // Location loc_end;
};
using node_ptr_t = unique_ptr<ASTNodeBase>;

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
      : left(std::move(left)), op(op), right(std::move(right)) {}
  node_ptr_t left;
  int op;
  node_ptr_t right;
};

class Sentence : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  vector<node_ptr_t> collection;
};
