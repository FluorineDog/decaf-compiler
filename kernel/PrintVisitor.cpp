// Template
#include "generated/PrintVisitor.h"
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
      cout << "  ";
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
  logger();
}

void PrintVisitor::visit(Field* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(ClassDecl* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(FunctionDecl* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(TypeArray* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(TypeBase* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(TypeUser* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(Identifier* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(Assign* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(TypedVariable* node) {
  Indent logger(level);
  logger();
}

void PrintVisitor::visit(Program* node) {
  level = 0;
  Indent logger(level);
  logger("Program", 1, 2);
  list_type = "decl";
  node->decls->accept(*this);
}

void PrintVisitor::visit(NoAction* node) {
  Indent logger(level);
  logger();
}


