// Template
#include "generated/LoadSymbolTableVisitor.h"
#include "internal.h"
#include "symbol_table/class_decl.h"
/*
 public:
  LoadSymbolTableVisitor& operator<<(node_ptr_t node){
    node->accept(*this);
    return *this;
  }
  LoadSymbolTableVisitor& operator<<(optional_node_ptr_t node){
    if(node) node.value()->accept(*this);
    return *this;
  }
  stack<StateType> call_stack;
  ClassEntries class_body;
  string current_class;
  string current_func;
  string current_id;
 private:
  string get_id(node_ptr_t);
*/
string LoadSymbolTableVisitor::get_id(node_ptr_t node) {
  current_id = "@undefined";
  *this << node;
  return current_id;
}
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
  // auto id = node->type
}

void LoadSymbolTableVisitor::visit(Interface* node) {
  // TODO
  HOLD(Interface);
  auto prototype_name = get_id(node->type_ident);
  current_class = prototype_name;
  for(auto entry: node->prototypes->list){
     
  }
}

void LoadSymbolTableVisitor::visit(ClassDecl* node) {
  // TODO
  HOLD(Class);
  auto class_name = get_id(node->type);
  current_class = current_id;

  if (class_body.find(class_name) == class_body.end()) {
    cerr << "Redeclear of " << class_name << endl;
    exit(-1);
  }

  auto& object = class_body[class_name];
  if (node->extender) {
    HOLD(Extender);
    object.extender = get_id(node->extender.value());
  }

  if (node->implementor) {
    HOLD(Implementor);
    auto list = node->implementor->list;
    for (auto id_entry : list) {
      object.implementors.insert(get_id(id_entry));
    }
  }

  if (node->fields) {
    HOLD(Field);
    auto list = node->fields->list;
    for (auto decl_entry : list) {
      *this << decl_entry;
    }
  }
  class_name = "@undefined";
}

void LoadSymbolTableVisitor::visit(FunctionDecl* node) {
  // TODO
  
}

void LoadSymbolTableVisitor::visit(TypeArray* node) {
  // TODO
  current_id = get_id(node->base) + "[]";
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
      name = "@WTF";
  }
  current_id = name;
}

void LoadSymbolTableVisitor::visit(TypeUser* node) {
  // TODO
  current_id = node->type_name;
}

void LoadSymbolTableVisitor::visit(Identifier* node) {
  // TODO
  current_id = node->name;
}

void LoadSymbolTableVisitor::visit(Assign* node) {
  // TODO
}

void LoadSymbolTableVisitor::visit(TypedVariable* node) {
  // TODO
  switch (call_stack.top()) {
    case StateType::Field: {
      auto& object = class_body[current_class];
      auto type = get_id(node->type);
      auto id = get_id(node->id);
      if(object.variables.find(id) == object.variables.end()){
        cerr << "id conflicts: " << id << endl;
        exit(-1);
      }
      object.variables[id] = type;
      break;
    }
  }
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


