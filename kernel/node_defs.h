#pragma once
#include "common.h"
class Integer : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  int num;
};

class Double : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  double num;
};

class NullPointer : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
};

class Call : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  // can be nullptr
  node_ptr_t expr;
  node_ptr_t ident;
  node_ptr_t actuals;
};

class Index : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  // can be nullptr
  node_ptr_t expr;
  node_ptr_t index_expr;
};

class Member : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  // can be nullptr
  node_ptr_t expr;
  node_ptr_t index_expr;
};

class NewArray : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t expr;
  node_ptr_t type;
};

class New : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  // can be nullptr
  node_ptr_t type;
};

class Read : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  int option;
};

class UnaryExpr : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  int op;
  node_ptr_t expr;
};

class BinaryExpr : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t left;
  int op;
  node_ptr_t right;
};


class This : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
};


class Print : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t args;
};

class List : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  vector<node_ptr_t> list;  // advanced container will be omitted
};


class Break : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
};

class Return : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  // can be empty
  node_ptr_t expr;
};

class For : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  // can be empty
  node_ptr_t init_expr;
  node_ptr_t conditional_expr;
  node_ptr_t step_expr;
  node_ptr_t stmt;
};

class While : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t conditional_expr;
  node_ptr_t stmt;
};

class If : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  int contion;
  node_ptr_t if_stmt;
  node_ptr_t else_stmt;
};

class ProtoType : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t type;
  node_ptr_t identifier;
  node_ptr_t formals; 
};

class Interface : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t type_ident;
  node_ptr_t prototypes;
};

class FUCK : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  int type;
};
