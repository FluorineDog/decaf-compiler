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
 public:
  StaticAnalyseVisitor(const ClassEntries& sym_table, const FuncEntry& binded_function);
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

StaticAnalyseVisitor::StaticAnalyseVisitor(const ClassEntries &sym_table, const FuncEntry &binded_function)
    : sym_table(sym_table), binded_function(binded_function) {
  current_block = nullptr;
  call_stack.push(StateType::FUNCTION);
}

void StaticAnalyseVisitor::visit(Integer* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Double* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(NullPointer* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Call* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Index* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(MemberDot* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(NewArray* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(New* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Read* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(UnaryExpr* node) {
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

void StaticAnalyseVisitor::visit(BinaryExpr* node) {
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

void StaticAnalyseVisitor::visit(This* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(Print* node) {
  // TODO
}

void StaticAnalyseVisitor::visit(List* node) {
  // TODO
  
}

void StaticAnalyseVisitor::visit(Break* node) {
  assert(loop_point);
  node->loop_point = loop_point.value();
}

void StaticAnalyseVisitor::visit(Return* node) {
  auto type = get_type(node->expr);
  assert(type == binded_function.return_type);
}

void StaticAnalyseVisitor::visit(For* node) {
  auto parent_loop = loop_point;
  loop_point = node;
  *this << node->init_expr;
  auto cond = get_type(node->conditional_expr);
  assert(cond == "bool");
  *this << node->step_expr;
  *this << node->stmt;
  loop_point = parent_loop;
}

void StaticAnalyseVisitor::visit(While* node) {
  auto parent_loop = loop_point;
  loop_point = node;
  auto cond = get_type(node->conditional_expr);
  assert(cond == "bool");
  *this << node->stmt;
  loop_point = parent_loop;
}

void StaticAnalyseVisitor::visit(Block* node) {
  // set parent
  node->aux.parent = current_block;
  // point to here
  current_block = &node->aux;
}

void StaticAnalyseVisitor::visit(If* node) {
  auto cond = get_type(node->condition);
  assert(cond == "bool");
  *this << node->if_stmt;
  *this << node->else_stmt;
}

void StaticAnalyseVisitor::visit(Prototype* node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(Interface* node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(ClassDecl* node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(FunctionDecl* node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(TypeArray* node) {
  assert(call_stack.top() == StateType::GET_ID);
  auto base = get_id(node->base);
  assert(base != "void");
  current_id = base + "[]";
}

void StaticAnalyseVisitor::visit(TypeBase* node) {
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

void StaticAnalyseVisitor::visit(TypeUser* node) {
  assert(call_stack.top() == StateType::GET_ID);
  current_id = node->type_name;
}

void StaticAnalyseVisitor::visit(Identifier* node) {
  switch (call_stack.top()) {
  case StateType::GET_ID: {
    current_id = node->name;
  }
  case StateType::GET_TYPE: {
    // as an expr;
    auto symbol = current_block->get_symbol(node->name);
    assert(symbol);
    auto[uid, type] = symbol.value();
    assert(type != "void");
    node->uid = uid;
    node->token_type = type;
  }
  default:assert(false);
  }
}

void StaticAnalyseVisitor::visit(Assign* node) {
  // SKIP
  auto lv_type = get_type(node->left);
  auto expr_type = get_type(node->right);
  assert(lv_type == expr_type);
  node->token_type = lv_type;
}

void StaticAnalyseVisitor::visit(TypedVariable* node) {
  // CreateDeclForVariables
  current_block->insert(get_id(node->type), get_id(node->id));
}

void StaticAnalyseVisitor::visit(Program* node) {
  // SKIP
}

void StaticAnalyseVisitor::visit(NoAction* node) {
  node->token_type = "void";
}


