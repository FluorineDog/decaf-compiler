// Template
#include "generated/StaticAnalyseVisitor.h"
#include "indent.h"
#include "drivers/class_decl.h"
/*
  const FuncEntry& binded_function;
  const ClassEntries& sym_table;
  BlockExt* current_block;
  string current_id;

  string get_id(node_ptr_t node);
  TypeEntry get_type(node_ptr_t node);
  std::optional<std::variant<While*, For*>> loop_point;
  stack<StateType> call_stack;
  const ClassBody& class_decl;
  const string class_name;
  BlockExt superblock;
 public:
  StaticAnalyseVisitor(const ClassEntries& sym_table, std::string class_name, const ClassBody& class_decl, const FuncEntry& binded_function);
*/

#define HOLD(t) StateHolder sh(call_stack, StateType::t);
string StaticAnalyseVisitor::get_id(node_ptr_t node) {
  HOLD(GET_ID);
  current_id = "@undefined";
  *this << node;
  return current_id;
}

TypeEntry StaticAnalyseVisitor::get_type(node_ptr_t node) {
  HOLD(GET_TYPE);
  *this << node;
  return node->token_type;
}

StaticAnalyseVisitor::StaticAnalyseVisitor(const ClassEntries &sym_table,
                     string class_name,
                     const ClassBody &class_decl,
                     const FuncEntry &binded_function)
    : sym_table(sym_table),
      class_name(class_name),
      class_decl(class_decl),
      binded_function(binded_function) {
  current_block = &superblock;
  superblock.load_class(class_decl);
  binded_function.body.value()->aux.load_function(binded_function);
  call_stack.push(StateType::FUNCTION);
}

void StaticAnalyseVisitor::visit(Integer *node) {
  // TODO
  node->token_type = "int";
}

void StaticAnalyseVisitor::visit(Double *node) {
  // TODO
  node->token_type = "double";
}

void StaticAnalyseVisitor::visit(NullPointer *node) {
  node->token_type = "nullptr";
}

void StaticAnalyseVisitor::visit(Call *node) {
  string type = class_name;
  if(node->domain_expr){
    type = get_type(node->domain_expr.value());
  }
  auto& func = sym_table.fetch_complete_function(class_name, get_id(node->ident));
  // TODO check args
  node->token_type = func.return_type;
}

void StaticAnalyseVisitor::visit(Index *node) {
  auto type = get_type(node->expr);
  auto index_type = get_type(node->expr);
  assert(index_type == "int");
  assert(type.size() >= 2 && type.substr(type.size() - 2, 2) == "[]");
  node->token_type = type.substr(type.size() - 2, 2);
}

void StaticAnalyseVisitor::visit(MemberDot *node) {
  auto class_name = get_type(node->expr);
  node->token_type = sym_table.fetch_complete_variable(class_name, get_id(node->ident));
}

void StaticAnalyseVisitor::visit(NewArray *node) {
  auto count = get_type(node->expr);
  assert(count == "int");
  node->token_type = get_type(node->type);
}

void StaticAnalyseVisitor::visit(New *node) {
  node->token_type = get_type(node->type);
}

void StaticAnalyseVisitor::visit(Read *node) {
  if (node->option == T_ReadInteger) {
    node->token_type = "int";
  } else {
    node->token_type = "string";
  }
}

void StaticAnalyseVisitor::visit(UnaryExpr *node) {
  switch (node->op) {
  case '-': {
    auto expr_type = get_type(node->expr);
    assert(set<string>({"double", "int"}).count(expr_type));
    node->token_type = expr_type;
    break;
  }
  case '!': {
    auto expr_type = get_type(node->expr);
    assert(set<string>({"bool", "int"}).count(expr_type));
    node->token_type = "bool";
    break;
  }
  }
}

void StaticAnalyseVisitor::visit(BinaryExpr *node) {
  auto left_type = get_type(node->left);
  auto right_type = get_type(node->left);
  switch (node->op) {
  case '+': {
    assert(set<string>({"double", "int", "string"}).count(left_type));
    assert(left_type == right_type);
    node->token_type = left_type;
    break;
  }
  case '%':
  case '-':
  case '*':
  case '/': {
    assert(set<string>({"double", "int"}).count(left_type));
    assert(left_type == right_type);
    node->token_type = left_type;
    break;
  }
  case '<':
  case '>':
  case T_eq:
  case T_not_eq:
  case T_greater_eq:
  case T_less_eq: {
    assert(set<string>({"double", "int"}).count(left_type));
    assert(left_type == right_type);
    node->token_type = "bool";
    break;
  }
  case T_and:
  case T_or: {
    assert(set<string>({"bool"}).count(left_type));
    assert(left_type == right_type);
    node->token_type = "bool";
    break;
  }
  }
}

void StaticAnalyseVisitor::visit(This *node) {
  node->token_type = class_name;
}

void StaticAnalyseVisitor::visit(Print *node) {
  HOLD(PRINT);
  *this << node->args;
}

void StaticAnalyseVisitor::visit(List *node) {
  switch (call_stack.top()) {
  case StateType::FUNCTION : {
    // top level, should be stmts;
    for (auto ptr: node->list) {
      *this << ptr;
    }
  }
  case StateType::PRINT: {
    for (auto ptr: node->list) {
      auto type = get_type(ptr);
      assert(set<std::string>({"int", "double", "bool", "string"}).count(type));
    }
  }
  }
}

void StaticAnalyseVisitor::visit(Break *node) {
  assert(loop_point);
  node->loop_point = loop_point.value();
}

void StaticAnalyseVisitor::visit(Return *node) {
  auto type = get_type(node->expr);
  assert(type == binded_function.return_type);
}

void StaticAnalyseVisitor::visit(For *node) {
  auto parent_loop = loop_point;
  loop_point = node;
  *this << node->init_expr;
  auto cond = get_type(node->conditional_expr);
  assert(cond == "bool");
  *this << node->step_expr;
  *this << node->stmt;
  loop_point = parent_loop;
}

void StaticAnalyseVisitor::visit(While *node) {
  auto parent_loop = loop_point;
  loop_point = node;
  auto cond = get_type(node->conditional_expr);
  assert(cond == "bool");
  *this << node->stmt;
  loop_point = parent_loop;
}

void StaticAnalyseVisitor::visit(Block *node) {
  // set parent
  node->aux.parent = current_block;
  // point to here
  current_block = &node->aux;
  *this << node->stmt_list;
}

void StaticAnalyseVisitor::visit(If *node) {
  auto cond = get_type(node->condition);
  assert(cond == "bool");
  *this << node->if_stmt;
  *this << node->else_stmt;
}

void StaticAnalyseVisitor::visit(Prototype *node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(Interface *node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(ClassDecl *node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(FunctionDecl *node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(TypeArray *node) {
  assert(call_stack.top() == StateType::GET_ID);
  auto base = get_id(node->base);
  assert(base != "void");
  current_id = base + "[]";
}

void StaticAnalyseVisitor::visit(TypeBase *node) {
  assert(call_stack.top() == StateType::GET_ID);
  string name;
  switch (node->base_type) {
  case T_int:name = "int";
    break;
  case T_double:name = "double";
    break;
  case T_bool:name = "bool";
    break;
  case T_string:name = "string";
    break;
  case T_void:name = "void";
    break;
  default:cerr << "[" << node->base_type << "]";
    name = "@WTF";
  }
  current_id = name;
}

void StaticAnalyseVisitor::visit(TypeUser *node) {
  assert(call_stack.top() == StateType::GET_ID);
  current_id = node->type_name;
}

void StaticAnalyseVisitor::visit(Identifier *node) {
  switch (call_stack.top()) {
  case StateType::GET_ID: {
    current_id = node->name;
  }
  default: {
    // as an expr;
    auto symbol = current_block->get_symbol(node->name);
    assert(symbol);
    auto&[uid, type] = symbol.value();
    assert(type != "void");
    node->uid = uid;
    node->token_type = type;
  }
  }
}

void StaticAnalyseVisitor::visit(Assign *node) {
  // SKIP
  auto lv_type = get_type(node->left);
  auto expr_type = get_type(node->right);
  if (expr_type == "nullptr") {
    assert(!set<string>({"int", "bool", "double", "void"}).count(lv_type));
  } else {
    assert(lv_type == expr_type);
  }
  node->token_type = lv_type;
}

void StaticAnalyseVisitor::visit(TypedVariable *node) {
  // CreateDeclForVariables
  current_block->insert(get_id(node->type), get_id(node->id));
}

void StaticAnalyseVisitor::visit(Program *node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(NoAction *node) {
  node->token_type = "void";
}


