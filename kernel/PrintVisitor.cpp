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
  int level;
  string list_type;
*/
void PrintVisitor::visit(Integer* node) {
  // TODO
}

void PrintVisitor::visit(Double* node) {
  // TODO
}

void PrintVisitor::visit(NullPointer* node) {
  // TODO
}

void PrintVisitor::visit(Call* node) {
  // TODO
}

void PrintVisitor::visit(Index* node) {
  // TODO
}

void PrintVisitor::visit(Member* node) {
  // TODO
}

void PrintVisitor::visit(NewArray* node) {
  // TODO
}

void PrintVisitor::visit(New* node) {
  // TODO
}

void PrintVisitor::visit(Read* node) {
  // TODO
}

void PrintVisitor::visit(UnaryExpr* node) {
  // TODO
}

void PrintVisitor::visit(BinaryExpr* node) {
  // TODO
}

void PrintVisitor::visit(This* node) {
  // TODO
}

void PrintVisitor::visit(Print* node) {
  // TODO
}

void PrintVisitor::visit(List* node) {
  Indent logger(level);
  for (auto ptr : node->list) {
    logger("ListItem", list_type);
    ptr->accept(*this);
  }
}

void PrintVisitor::visit(Break* node) {
  // TODO
}

void PrintVisitor::visit(Return* node) {
  // TODO
}

void PrintVisitor::visit(For* node) {
  // TODO
}

void PrintVisitor::visit(While* node) {
  // TODO
}

void PrintVisitor::visit(Block* node) {
  // TODO
}

void PrintVisitor::visit(If* node) {
  // TODO
}

void PrintVisitor::visit(ProtoType* node) {
  // TODO
}

void PrintVisitor::visit(Interface* node) {
  // TODO
}

void PrintVisitor::visit(Field* node) {
  // TODO
}

void PrintVisitor::visit(ClassDecl* node) {
  // TODO
}

void PrintVisitor::visit(FunctionDecl* node) {
  // TODO
}

void PrintVisitor::visit(TypeArray* node) {
  // TODO
}

void PrintVisitor::visit(TypeBase* node) {
  // TODO
}

void PrintVisitor::visit(TypeUser* node) {
  // TODO
}

void PrintVisitor::visit(Identifier* node) {
  // TODO
}

void PrintVisitor::visit(Assign* node) {
  // TODO
}

void PrintVisitor::visit(TypedVariable* node) {
  // TODO
}

void PrintVisitor::visit(Program* node) {
  level = 0;
  Indent logger(level);
  logger("Program", 1, 2);
  list_type = "decl";
  node->decls->accept(*this);
}

void PrintVisitor::visit(NoAction* node) {
  // TODO
}


