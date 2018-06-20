// Template
#include "generated/PrintVisitor.h"
#include "parser.hxx"
#include "indent.h"
#include "node_defs.h"
/*
  string list_type;
 public:
  int level;
  PrintVisitor(): level(0){}
*/

void PrintVisitor::visit(Integer *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Integer", node->num);
}

void PrintVisitor::visit(Double *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Double", node->num);
}

void PrintVisitor::visit(NullPointer *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("NullPointer");
}

void PrintVisitor::visit(Call *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Call");
  list_type = "expr";
  *this << node->domain_expr;
  *this << node->ident;
  list_type = "actuals";
  *this << node->actuals;
}

void PrintVisitor::visit(Index *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Index");
  *this << node->expr;
  *this << node->index_expr;
}

void PrintVisitor::visit(MemberDot *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("MemberDot");
  *this << node->expr;
  *this << node->ident;
}

void PrintVisitor::visit(NewArray *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("NewArray");
  *this << node->type;
  *this << node->expr;
}

void PrintVisitor::visit(New *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("New");
  *this << node->type;
}

void PrintVisitor::visit(Read *node) {
  Indent logger(level, __LINE__, node->token_type);
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

void PrintVisitor::visit(UnaryExpr *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Unary Expr", (char)node->op);
  *this << node->expr;
}

void PrintVisitor::visit(BinaryExpr *node) {
  Indent logger(level, __LINE__, node->token_type);
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

void PrintVisitor::visit(This *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("This");
}

void PrintVisitor::visit(Print *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Print");
  list_type = "PrintArgs";
  *this << node->args;
}

void PrintVisitor::visit(List *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("ListItems", list_type);
  list_type = "undefined";
  for (auto ptr : node->list) {
    ptr->accept(*this);
  }
}

void PrintVisitor::visit(Break *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Break");
}

void PrintVisitor::visit(Return *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Return");
  *this << node->expr;
}

void PrintVisitor::visit(For *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("For");
  *this << node->init_expr;
  *this << node->conditional_expr;
  *this << node->step_expr;
  *this << node->stmt;
}

void PrintVisitor::visit(While *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("While");
  *this << node->conditional_expr;
  *this << node->stmt;
}

void PrintVisitor::visit(Block *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Block");
  list_type = "block";
  *this << node->stmt_list;
}

void PrintVisitor::visit(If *node) {
  Indent logger(level, __LINE__, node->token_type);
  *this << node->condition;
}

void PrintVisitor::visit(Prototype *node) {
  Indent logger(level, __LINE__, node->token_type);
  if(node->type != nullptr){
    *this << node->type;
  } else {
    Indent logger(level, __LINE__, node->token_type);
    logger("void");
  }
  *this << node->identifier;
  list_type = "Parameters";
  *this << node->formals;
}

void PrintVisitor::visit(Interface *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Interface");
  *this << node->type_ident;
  list_type = "Prototype";
  *this << node->prototypes;
}

void PrintVisitor::visit(ClassDecl *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("ClassDecl");
  *this << node->type;
  if (node->extender) {
    Indent logger(level, __LINE__, node->token_type);
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

void PrintVisitor::visit(FunctionDecl *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("FunctionDecl", "return");
  if (node->type) {
    *this << node->type;
  } else {
    Indent logger(level, __LINE__, node->token_type);
    logger("void");
  }
  *this << node->identifier;
  list_type = "Parameters";
  *this << node->formals;
  list_type = "FunctionBody";
  *this << node->body;
}

void PrintVisitor::visit(TypeArray *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("ArrayOf");
  *this << node->base;
}

void PrintVisitor::visit(TypeBase *node) {
  Indent logger(level, __LINE__, node->token_type);
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
    case T_void:
      name = "void";
      break;
    case T_string:
      name = "string";
      break;
    default:
      name = "WTF";
  }
  logger("TypeBase", name);
}

void PrintVisitor::visit(TypeUser *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("type_id", node->type_name);
}

void PrintVisitor::visit(Identifier *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Identifier", node->name);
}

void PrintVisitor::visit(Assign *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("Assign");
  *this << node->left;
  *this << node->right;
}

void PrintVisitor::visit(TypedVariable *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("TypedVariable");
  *this << node->type;
  *this << node->id;
}

void PrintVisitor::visit(Program *node) {
  level = 0;
  list_type = "init";
  Indent logger(level, __LINE__, node->token_type);
  logger("Program");
  list_type = "decl";
  node->decls->accept(*this);
}

void PrintVisitor::visit(NoAction *node) {
  Indent logger(level, __LINE__, node->token_type);
  logger("skip");
}


