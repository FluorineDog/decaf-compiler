#pragma once
class Visitor {
 public:
  virtual void visit(class Integer* node) = 0;
  virtual void visit(class Double* node) = 0;
  virtual void visit(class NullPointer* node) = 0;
  virtual void visit(class Call* node) = 0;
  virtual void visit(class Index* node) = 0;
  virtual void visit(class MemberDot* node) = 0;
  virtual void visit(class NewArray* node) = 0;
  virtual void visit(class New* node) = 0;
  virtual void visit(class Read* node) = 0;
  virtual void visit(class UnaryExpr* node) = 0;
  virtual void visit(class BinaryExpr* node) = 0;
  virtual void visit(class This* node) = 0;
  virtual void visit(class Print* node) = 0;
  virtual void visit(class List* node) = 0;
  virtual void visit(class Break* node) = 0;
  virtual void visit(class Return* node) = 0;
  virtual void visit(class For* node) = 0;
  virtual void visit(class While* node) = 0;
  virtual void visit(class Block* node) = 0;
  virtual void visit(class If* node) = 0;
  virtual void visit(class Prototype* node) = 0;
  virtual void visit(class Interface* node) = 0;
  virtual void visit(class ClassDecl* node) = 0;
  virtual void visit(class FunctionDecl* node) = 0;
  virtual void visit(class TypeArray* node) = 0;
  virtual void visit(class TypeBase* node) = 0;
  virtual void visit(class TypeUser* node) = 0;
  virtual void visit(class Identifier* node) = 0;
  virtual void visit(class Assign* node) = 0;
  virtual void visit(class TypedVariable* node) = 0;
  virtual void visit(class Program* node) = 0;
  virtual void visit(class NoAction* node) = 0;
 // Generated
 public:
  Visitor& operator<<(node_ptr_t node){
    node->accept(*this);
    return *this;
  }
  Visitor& operator<<(optional_node_ptr_t node){
    if(node) node.value()->accept(*this);
    return *this;
  }
};
