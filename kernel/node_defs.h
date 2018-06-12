#pragma once
#include "common.h"
#include <string>
using std::string;
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
  node_ptr_t domain_expr;
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

class MemberDot : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  // can be nullptr
  node_ptr_t expr;
  node_ptr_t ident;
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

class Block : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t stmt_list;
};

class If : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t condition;
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


class ClassDecl : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t type;
  node_ptr_t extender;
  node_ptr_t implementor;
  node_ptr_t fields;
};

class FunctionDecl : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t type;
  node_ptr_t identifier;
  node_ptr_t formals; 
  node_ptr_t body;
};

class TypeArray : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t base;
};

class TypeBase : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  int base_type;
};

class TypeUser : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  string type_name;
};

class Identifier : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  string name;
};

class Assign : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t left;
  node_ptr_t right;
};

class TypedVariable : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t type;
  Identifier* id;
};

class Program : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
  node_ptr_t decls;
};

class NoAction : public ASTNodeBase {
 public:
  virtual void accept(Visitor& v) { v.visit(this); }
};

