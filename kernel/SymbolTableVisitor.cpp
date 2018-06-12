// Template
#include "generated/SymbolTableVisitor.h"
#include "../build/parser.hxx"
#include "generated/SymbolTableVisitor.h"
#include "internal.h"
#include "node_defs.h"
class SymTableIndent {
 public:
  SymTableIndent(int& level) : level(level) { level++; }
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
      switch (i % 3) {
        case 0:
          cout << ". ";
          break;
        case 1:
          cout << "| ";
          break;
        case 2:
          cout << "* ";
          break;
      }
    }
    std::cout << "<";
    printer_helper(args...);
    cout << ">" << endl;
  }
  ~SymTableIndent() { level--; }

 private:
  int& level;
};
/*
  SymbolTableVisitor& operator<<(ASTNodeBase* node){
    if(node != nullptr){
      node->accept(*this);
    } else {
      NoAction no;
      no.accept(*this);
    }
    return *this;
  }
  int level;
  string list_type;
*/
void SymbolTableVisitor::visit(Integer* node) {
  SymTableIndent logger(level);
  logger("Integer", node->num);
}

void SymbolTableVisitor::visit(Double* node) {
  SymTableIndent logger(level);
  logger("Double", node->num);
}

void SymbolTableVisitor::visit(NullPointer* node) {
  SymTableIndent logger(level);
  logger("NullPointer");
}

void SymbolTableVisitor::visit(Call* node) {
  SymTableIndent logger(level);
  logger("Call");
  list_type = "expr";
  *this << node->domain_expr;
  *this << node->ident;
  list_type = "actuals";
  *this << node->actuals;
}

void SymbolTableVisitor::visit(Index* node) {
  SymTableIndent logger(level);
  logger("Index");
  *this << node->expr;
  *this << node->index_expr;
}

void SymbolTableVisitor::visit(MemberDot* node) {
  SymTableIndent logger(level);
  logger("MemberDot");
  *this << node->expr;
  *this << node->ident;
}

void SymbolTableVisitor::visit(NewArray* node) {
  SymTableIndent logger(level);
  logger("NewArray");
  *this << node->type;
  *this << node->expr;
}

void SymbolTableVisitor::visit(New* node) {
  SymTableIndent logger(level);
  logger("New");
  *this << node->type;
}

void SymbolTableVisitor::visit(Read* node) {
  SymTableIndent logger(level);
  string str = "UB";
  switch (node->option) {
    case T_ReadInteger:
      str = "Integer";
      break;
    case T_ReadLine:
      str = "Line";
      break;
  }
  logger("Read", str);
}

void SymbolTableVisitor::visit(UnaryExpr* node) {
  SymTableIndent logger(level);
  logger("Unary Expr", (char)node->op);
  *this << node->expr;
}

void SymbolTableVisitor::visit(BinaryExpr* node) {
  SymTableIndent logger(level);
  string str;
  if (node->op <= 255) {
    str = "\"" + string(1, node->op) + "\"";
  } else {
    switch (node->op) {
      case T_or:
        str = "\"||\"";
        break;
      case T_and:
        str = "\"&&\"";
        break;
      case T_less_eq:
        str = "\"<=\"";
        break;
      case T_greater_eq:
        str = "\">=\"";
        break;
      case T_eq:
        str = "\"==\"";
        break;
      case T_not_eq:
        str = "\"!=\"";
        break;
    }
  }

  logger("BinaryExpr", str);
  *this << node->left;
  *this << node->right;
}

void SymbolTableVisitor::visit(This* node) {
  SymTableIndent logger(level);
  logger("This");
}

void SymbolTableVisitor::visit(Print* node) {
  // TODO
}

void SymbolTableVisitor::visit(List* node) {
  SymTableIndent logger(level);
  logger("ListItems", list_type);
  list_type = "undefined";
  for (auto ptr : node->list) {
    ptr->accept(*this);
  }
}

void SymbolTableVisitor::visit(Break* node) {
  SymTableIndent logger(level);
  logger("Break");
}

void SymbolTableVisitor::visit(Return* node) {
  SymTableIndent logger(level);
  logger("Return");
  *this << node->expr;
}

void SymbolTableVisitor::visit(For* node) {
  SymTableIndent logger(level);
  logger("For");
  *this << node->init_expr;
  *this << node->conditional_expr;
  *this << node->step_expr;
  *this << node->stmt;
}

void SymbolTableVisitor::visit(While* node) {
  SymTableIndent logger(level);
  logger("While");
  *this << node->conditional_expr;
  *this << node->stmt;
}

void SymbolTableVisitor::visit(Block* node) {
  SymTableIndent logger(level);
  logger("Block");
  list_type = "block";
  *this << node->stmt_list;
}

void SymbolTableVisitor::visit(If* node) {
  SymTableIndent logger(level);
  *this << node->condition;
}

void SymbolTableVisitor::visit(ProtoType* node) {
  SymTableIndent logger(level);
  if (node->type != nullptr) {
    *this << node->type;
  } else {
    SymTableIndent logger(level);
    logger("void");
  }
  *this << node->identifier;
  list_type = "Parameters";
  *this << node->formals;
}

void SymbolTableVisitor::visit(Interface* node) {
  SymTableIndent logger(level);
  logger("Interface");
  *this << node->type_ident;
  list_type = "Prototype";
  *this << node->prototypes;
}

void SymbolTableVisitor::visit(ClassDecl* node) {
  SymTableIndent logger(level);
  logger("ClassDecl");
  *this << node->type;
  if (node->extender) {
    SymTableIndent logger(level);
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

void SymbolTableVisitor::visit(FunctionDecl* node) {
  SymTableIndent logger(level);
  logger("FunctionDecl", "return");
  if (node->type) {
    *this << node->type;
  } else {
    SymTableIndent logger(level);
    logger("void");
  }
  *this << node->identifier;
  list_type = "Parameters";
  *this << node->formals;
  list_type = "FunctionBody";
  *this << node->body;
}

void SymbolTableVisitor::visit(TypeArray* node) {
  SymTableIndent logger(level);
  logger("ArrayOf");
  *this << node->base;
}

void SymbolTableVisitor::visit(TypeBase* node) {
  SymTableIndent logger(level);
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
  logger("TypeBase", name);
}

void SymbolTableVisitor::visit(TypeUser* node) {
  SymTableIndent logger(level);
  logger("type_id", node->type_name);
}

void SymbolTableVisitor::visit(Identifier* node) {
  SymTableIndent logger(level);
  logger("Identifier", node->name);
}

void SymbolTableVisitor::visit(Assign* node) {
  SymTableIndent logger(level);
  logger("Assign");
  *this << node->left;
  *this << node->right;
}

void SymbolTableVisitor::visit(TypedVariable* node) {
  SymTableIndent logger(level);
  logger("TypedVariable");
  *this << node->type;
  *this << node->id;
}

void SymbolTableVisitor::visit(Program* node) {
  level = 0;
  list_type = "init";
  SymTableIndent logger(level);
  logger("Program");
  list_type = "decl";
  node->decls->accept(*this);
}

void SymbolTableVisitor::visit(NoAction* node) {
  SymTableIndent logger(level);
  logger("skip");
}


