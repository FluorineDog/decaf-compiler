#pragma once
#include "../common.h"
inline auto mkInteger(int num) {
  auto node = new Integer;
  node->num = num;
 // Generated
  return node;
}

inline auto mkDouble(double num) {
  auto node = new Double;
  node->num = num;
 // Generated
  return node;
}

inline auto mkNullPointer() {
  auto node = new NullPointer;
 // Generated
  return node;
}

inline auto mkCall(optional_node_ptr_t domain_expr, node_ptr_t ident, node_ptr_t actuals) {
  auto node = new Call;
  node->domain_expr = domain_expr;
  node->ident = ident;
  node->actuals = actuals;
 // Generated
  return node;
}

inline auto mkIndex(node_ptr_t expr, node_ptr_t index_expr) {
  auto node = new Index;
  node->expr = expr;
  node->index_expr = index_expr;
 // Generated
  return node;
}

inline auto mkMemberDot(node_ptr_t expr, node_ptr_t ident) {
  auto node = new MemberDot;
  node->expr = expr;
  node->ident = ident;
 // Generated
  return node;
}

inline auto mkNewArray(node_ptr_t expr, node_ptr_t type) {
  auto node = new NewArray;
  node->expr = expr;
  node->type = type;
 // Generated
  return node;
}

inline auto mkNew(node_ptr_t type) {
  auto node = new New;
  node->type = type;
 // Generated
  return node;
}

inline auto mkRead(int option) {
  auto node = new Read;
  node->option = option;
 // Generated
  return node;
}

inline auto mkUnaryExpr(int op, node_ptr_t expr) {
  auto node = new UnaryExpr;
  node->op = op;
  node->expr = expr;
 // Generated
  return node;
}

inline auto mkBinaryExpr(node_ptr_t left, int op, node_ptr_t right) {
  auto node = new BinaryExpr;
  node->left = left;
  node->op = op;
  node->right = right;
 // Generated
  return node;
}

inline auto mkThis() {
  auto node = new This;
 // Generated
  return node;
}

inline auto mkPrint(node_ptr_t args) {
  auto node = new Print;
  node->args = args;
 // Generated
  return node;
}

inline auto mkList() {
  auto node = new List;
 // Generated
  return node;
}

inline auto mkBreak() {
  auto node = new Break;
 // Generated
  return node;
}

inline auto mkReturn(node_ptr_t expr) {
  auto node = new Return;
  node->expr = expr;
 // Generated
  return node;
}

inline auto mkFor(node_ptr_t init_expr, node_ptr_t conditional_expr, node_ptr_t step_expr, node_ptr_t stmt) {
  auto node = new For;
  node->init_expr = init_expr;
  node->conditional_expr = conditional_expr;
  node->step_expr = step_expr;
  node->stmt = stmt;
 // Generated
  return node;
}

inline auto mkWhile(node_ptr_t conditional_expr, node_ptr_t stmt) {
  auto node = new While;
  node->conditional_expr = conditional_expr;
  node->stmt = stmt;
 // Generated
  return node;
}

inline auto mkBlock(node_ptr_t stmt_list) {
  auto node = new Block;
  node->stmt_list = stmt_list;
 // Generated
  return node;
}

inline auto mkIf(node_ptr_t condition, node_ptr_t if_stmt, node_ptr_t else_stmt) {
  auto node = new If;
  node->condition = condition;
  node->if_stmt = if_stmt;
  node->else_stmt = else_stmt;
 // Generated
  return node;
}

inline auto mkPrototype(node_ptr_t type, node_ptr_t identifier, List* formals) {
  auto node = new Prototype;
  node->type = type;
  node->identifier = identifier;
  node->formals = formals;
 // Generated
  return node;
}

inline auto mkInterface(node_ptr_t type_ident, List* prototypes) {
  auto node = new Interface;
  node->type_ident = type_ident;
  node->prototypes = prototypes;
 // Generated
  return node;
}

inline auto mkClassDecl(node_ptr_t type, optional_node_ptr_t extender, List* implementor, List* fields) {
  auto node = new ClassDecl;
  node->type = type;
  node->extender = extender;
  node->implementor = implementor;
  node->fields = fields;
 // Generated
  return node;
}

inline auto mkFunctionDecl(node_ptr_t type, node_ptr_t identifier, List* formals, Block* body) {
  auto node = new FunctionDecl;
  node->type = type;
  node->identifier = identifier;
  node->formals = formals;
  node->body = body;
 // Generated
  return node;
}

inline auto mkTypeArray(node_ptr_t base) {
  auto node = new TypeArray;
  node->base = base;
 // Generated
  return node;
}

inline auto mkTypeBase(int base_type) {
  auto node = new TypeBase;
  node->base_type = base_type;
 // Generated
  return node;
}

inline auto mkTypeUser(string type_name) {
  auto node = new TypeUser;
  node->type_name = type_name;
 // Generated
  return node;
}

inline auto mkIdentifier(string name) {
  auto node = new Identifier;
  node->name = name;
 // Generated
  return node;
}

inline auto mkAssign(node_ptr_t left, node_ptr_t right) {
  auto node = new Assign;
  node->left = left;
  node->right = right;
 // Generated
  return node;
}

inline auto mkTypedVariable(node_ptr_t type, Identifier* id) {
  auto node = new TypedVariable;
  node->type = type;
  node->id = id;
 // Generated
  return node;
}

inline auto mkProgram(List* decls) {
  auto node = new Program;
  node->decls = decls;
 // Generated
  return node;
}

inline auto mkNoAction() {
  auto node = new NoAction;
 // Generated
  return node;
}
