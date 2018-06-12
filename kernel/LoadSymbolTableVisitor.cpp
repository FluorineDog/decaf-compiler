// Template
#include "generated/LoadSymbolTableVisitor.h"
#include "internal.h"
#include "symbol_table/class_decl.h"
/*
 public:
  LoadSymbolTableVisitor& operator<<(ASTNodeBase* node){
    if(node != nullptr){
      node->accept(*this);
    }
    return *this;
  }
  stack<StateType>& call_stack;
  ClassEntries class_body;
  string current_class;
  string current_func;
  string current_id;
*/
#define HOLD(t) StateHolder sh(call_stack, StateType::t);
void LoadSymbolTableVisitor::visit(Integer* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Double* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(NullPointer* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Call* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Index* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(MemberDot* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(NewArray* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(New* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Read* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(UnaryExpr* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(BinaryExpr* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(This* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Print* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(List* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Break* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Return* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(For* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(While* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Block* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(If* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(ProtoType* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Interface* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(ClassDecl* node) {
  // TODO
  HOLD(Class);
  *this << node->type;
  auto class_name = current_id;
  current_id = "@undefined";

  if (class_body.find(class_name) == class_body.end()) {
    cerr << "Redeclear of " << class_name << endl;
    exit(-1);
  }

  auto& object = class_body[class_name];
  if (node->extender) {
    *this << node->extender;
    object.extender = current_id;
    current_id = "@undefined";
  }

  if (node->implementor) {
    HOLD(Implementor);
    *this << node->implementor;
    object.implementors.insert(current_id);
    current_id = "@undefined";
  }

  *this << node->fields;
}

void LoadSymbolTableVisitor::visit(FunctionDecl* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(TypeArray* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(TypeBase* node) {
  // TODO
  string name;
  switch (node->base_type) {
    case T_int:
      name = "int";
      break;
    case T_double:
      name = "double";
      break;
    case T_bool:
      name = "bool";
      break;
    case T_string:
      name = "string";
      break;
    default:
      name = "WTF";
  }
  current_id = name;
}

void LoadSymbolTableVisitor::visit(TypeUser* node) {
  // TODO
  current_id = node->type_name;
}

void LoadSymbolTableVisitor::visit(Identifier* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Assign* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(TypedVariable* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(Program* node) {
  // TODO
  current_id = "@undefined";
  current_class = "@undefined";
  current_func = "@undefined";
  node->accept(*this);  // goto functions
}

void LoadSymbolTableVisitor::visit(NoAction* node) {
  // TODO
}


