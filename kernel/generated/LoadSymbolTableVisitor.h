#pragma once
#include "common.h"
#include "Visitor.h"
#include "node_defs.h"
#include "generated/LoadSymbolTableVisitor.h"
#include "indent.h"
#include "drivers/class_decl.h"
class LoadSymbolTableVisitor : public Visitor {
  virtual void visit(class Integer* node) override;
  virtual void visit(class Double* node) override;
  virtual void visit(class NullPointer* node) override;
  virtual void visit(class Call* node) override;
  virtual void visit(class Index* node) override;
  virtual void visit(class MemberDot* node) override;
  virtual void visit(class NewArray* node) override;
  virtual void visit(class New* node) override;
  virtual void visit(class Read* node) override;
  virtual void visit(class UnaryExpr* node) override;
  virtual void visit(class BinaryExpr* node) override;
  virtual void visit(class This* node) override;
  virtual void visit(class Print* node) override;
  virtual void visit(class List* node) override;
  virtual void visit(class Break* node) override;
  virtual void visit(class Return* node) override;
  virtual void visit(class For* node) override;
  virtual void visit(class While* node) override;
  virtual void visit(class Block* node) override;
  virtual void visit(class If* node) override;
  virtual void visit(class Prototype* node) override;
  virtual void visit(class Interface* node) override;
  virtual void visit(class ClassDecl* node) override;
  virtual void visit(class FunctionDecl* node) override;
  virtual void visit(class TypeArray* node) override;
  virtual void visit(class TypeBase* node) override;
  virtual void visit(class TypeUser* node) override;
  virtual void visit(class Identifier* node) override;
  virtual void visit(class Assign* node) override;
  virtual void visit(class TypedVariable* node) override;
  virtual void visit(class Program* node) override;
  virtual void visit(class NoAction* node) override;
 public:
  stack<StateType> call_stack;
  ClassEntries top_pool;
  ClassBody current_class;
  InterfaceBody current_interface;
  FuncEntry current_func;
  string current_id;
 private:
  string get_id(node_ptr_t);
 public:
};
