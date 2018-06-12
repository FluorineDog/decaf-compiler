// Template
#include "generated/PrintVisitor.h"
#include "../build/parser.hxx"
#include "internal.h"
class Indent {
 public:
  Indent(int& level) : level(level) { level++; }

  void printer_helper() {}
  template <typename T>
  void printer_helper(T a) {
    cout << a;
  }
  template <typename T, typename... Args>
  void printer_helper(T a, Args&&... args) {
    cout << a << ", ";
    printer_helper(args...);
  }
  template <typename... Args>
  void operator()(Args&&... args) {
    for (int i = 0; i < level - 1; ++i) {
      switch(i % 3){
        case 0: cout << ". "; break; 
        case 1: cout << "| "; break; 
        case 2: cout << "* "; break; 
      }
    }
    std::cout << "<";
    printer_helper(args...);
    cout << ">" << endl;
  }
  ~Indent() { level--; }

 private:
  int& level;
};
/*
  PrintVisitor& operator<<(ASTNodeBase* node){
    if(node != nullptr){
      node->accept(*this);
    }
    return *this;
  }
  int level;
  string list_type;
*/
void PrintVisitor::visit(Integer* node) {
  Indent logger(level);
  logger("Integer");
}

void PrintVisitor::visit(Double* node) {
  Indent logger(level);
  logger("Double");
}

void PrintVisitor::visit(NullPointer* node) {
  Indent logger(level);
  logger("NullPointer");
}

void PrintVisitor::visit(Call* node) {
  Indent logger(level);
  logger("Call");
  list_type = "expr";
  *this << node->domain_expr;
  *this << node->ident;
  list_type = "actuals";
  *this << node->actuals;
}

void PrintVisitor::visit(Index* node) {
  Indent logger(level);
  logger("Index");
}

void PrintVisitor::visit(Member* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(NewArray* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(New* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(Read* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(UnaryExpr* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(BinaryExpr* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(This* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(Print* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(List* node) {
  Indent logger(level);
  logger("ListItems", list_type);
  list_type = "undefined";
  for (auto ptr : node->list) {
    ptr->accept(*this);
  }
}

void PrintVisitor::visit(Break* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(Return* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(For* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(While* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(Block* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(If* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(ProtoType* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(Interface* node) {
  Indent logger(level);
  logger("Interface");
  *this << node->type_ident;
  list_type = "Prototype";
  *this << node->prototypes;
}

void PrintVisitor::visit(Field* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(ClassDecl* node) {
  Indent logger(level);
  logger("ClassDecl");
  *this << node->type;
  if (node->extender) {
    Indent logger(level);
    logger("Extender");
    *this << node->extender;
  }
  if (node->implementor) {
    list_type = "Implementor";
    *this << node->implementor;
  }

  list_type = "Fields";
  *this << node->fields;
}

void PrintVisitor::visit(FunctionDecl* node) {
  Indent logger(level);
  logger("FunctionDecl", "return");
  if(node->type){
    *this << node->type;
  } else{
    Indent logger(level);
    logger("void");
  }
  *this << node->identifier;
  list_type = "Formals";
  *this << node->formals;
  list_type = "FunctionBody";
  *this << node->body;
}

void PrintVisitor::visit(TypeArray* node) {
  Indent logger(level);
  logger("ArrayOf");
  *this << node->base;
}

void PrintVisitor::visit(TypeBase* node) {
  Indent logger(level);
  string name;
  switch (node->base_type) {
    case T_int: {
      name = "int";
      break;
    }
    case T_double: {
      name = "double";
      break;
    }
    case T_bool: {
      name = "bool";
      break;
    }
    case T_string: {
      name = "string";
      break;
    }
    default:
      name = "WTF";
  }
  logger("TypeBase", name);
}

void PrintVisitor::visit(TypeUser* node) {
  Indent logger(level);
  logger("type_id", node->type_name);
}

void PrintVisitor::visit(Identifier* node) {
  Indent logger(level);
  logger("Identifier", node->name);
}

void PrintVisitor::visit(Assign* node) {
  Indent logger(level);
  logger("Assign");
  *this << node->left;
  *this << node->right;
}

void PrintVisitor::visit(TypedVariable* node) {
  Indent logger(level);
  logger("TypedVariable");
  *this << node->type;
  *this << node->id;
}

void PrintVisitor::visit(Program* node) {
  level = 0;
  list_type = "init";
  Indent logger(level);
  logger("Program");
  list_type = "decl";
  node->decls->accept(*this);
}

void PrintVisitor::visit(NoAction* node) {
  Indent logger(level);
  logger("NoAction");
}
