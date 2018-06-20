// Template
#include "generated/CodegenVisitor.h"
#include "indent.h"
#include "llvm_driver/llvm_inc.h"
/*
 private:
  class LLVMEngine& eng;
  llvm::Value* rt_value;
  llvm::Type* rt_type;
  BlockExt* block_aux;
  stack<StateType> call_stack;
  bool right_value;
  std::optional<llvm::BasicBlock*> current_nextBB;
 public:
  CodegenVisitor& operator<<(node_ptr_t node){
    node->accept(*this);
    return *this;
  }
  CodegenVisitor(class LLVMEngine& eng, BlockExt* block_aux);
  llvm::Value* get_value(node_ptr_t node, bool rvalue = true);
  llvm::Type* get_type(node_ptr_t node);
*/
#define HOLD(t) StateHolder sh(call_stack, StateType::t);
//using namespace llvm;
#include "llvm_driver/llvm.h"
CodegenVisitor::CodegenVisitor(LLVMEngine &eng, BlockExt *block_aux)
    : eng(eng), block_aux(block_aux) {
  call_stack.push(StateType::PROGRAM);
}

Value *CodegenVisitor::get_value(node_ptr_t node, bool is_right_value) {
  HOLD(GET_VALUE);
  right_value = is_right_value;
  rt_value = nullptr;
  *this << node;
  assert(rt_value);
  return rt_value;
}
Type *CodegenVisitor::get_type(node_ptr_t node) {
  HOLD(GET_TYPE);
  rt_type = nullptr;
  *this << node;
  assert(rt_type);
  return rt_type;
}

void CodegenVisitor::visit(Integer *node) {
  assert(right_value);
  assert(call_stack.top() == StateType::GET_VALUE);
  rt_value = ConstantInt::get(eng.getContext(), APInt(32, node->num, true));
}

void CodegenVisitor::visit(Double *node) {
  assert(right_value);
  assert(call_stack.top() == StateType::GET_VALUE);
  rt_value = ConstantFP::get(Type::getDoubleTy(eng.getContext()), node->num);
}

void CodegenVisitor::visit(NullPointer *node) {
  // TODO
  auto type = eng.get_user_type(node->token_type);
  rt_value = ConstantPointerNull::get(type);
}

void CodegenVisitor::visit(Call *node) {
  // TODO
}

void CodegenVisitor::visit(Index *node) {
  // TODO
}

void CodegenVisitor::visit(MemberDot *node) {
  // TODO
}

void CodegenVisitor::visit(NewArray *node) {
  // TODO
}

void CodegenVisitor::visit(New *node) {
  // TODO
}

void CodegenVisitor::visit(Read *node) {
  switch (node->option) {
  case T_ReadLine: {
    auto F = eng.load_ext_func("readline");
    rt_value = eng().CreateCall(F);
    break;
  }
  case T_ReadInteger: {
    auto F = eng.load_ext_func("readint");
    rt_value = eng().CreateCall(F);
  }
  }
}

void CodegenVisitor::visit(UnaryExpr *node) {
  switch (node->op) {
  case '-': {
    auto value = get_value(node->expr);
    assert(set<string>({"int", "double"}).count(node->token_type));
    rt_value = eng().CreateNeg(value);
    break;
  }
  case '!': {
    auto value = get_value(node->expr);
    assert(node->token_type == "bool");
    rt_value = eng().CreateNot(value, "not");
    break;
  }
  }
}

void CodegenVisitor::visit(BinaryExpr *node) {
  auto left = get_value(node->left);
  auto right = get_value(node->right);
  switch (node->op) {
  case '+': {
//    assert(set<string>({"double", "int", "string"}).count(left_type));
    assert(node->left->token_type == node->right->token_type);
    if (node->left->token_type != "string") {
      rt_value = eng().CreateAdd(left, right);
    } else {
      auto F = eng.load_ext_func("string_cat");
      rt_value = eng().CreateCall(F, {left, right});
    }
    break;
  }
  case '%': {
    rt_value = eng().CreateSRem(left, right);
    break;
  }
  case '-': {
    rt_value = eng().CreateSub(left, right);
    break;
  }
  case '*': {
    rt_value = eng().CreateMul(left, right);
    break;
  }
  case '/': {
    rt_value = eng().CreateSDiv(left, right);
    break;
  }
  case '<': {
    rt_value = eng().CreateICmpSLT(left, right);
    break;
  }
  case '>': {
    rt_value = eng().CreateICmpSGT(left, right);
    break;
  }
  case T_less_eq: {
    rt_value = eng().CreateICmpSLE(left, right);
    break;
  }

  case T_greater_eq: {
    rt_value = eng().CreateICmpSGE(left, right);
    break;
  }

  case T_eq:
  case T_not_eq: {
    auto left_stp = eng().CreatePtrToInt(left, Type::getInt64Ty(eng.getContext()));
    auto right_stp = eng().CreatePtrToInt(right, Type::getInt64Ty(eng.getContext()));
    if (node->op == T_eq) {
      rt_value = eng().CreateICmpEQ(left_stp, right_stp);
    } else {
      rt_value = eng().CreateICmpNE(left_stp, right_stp);
    }
    break;
  }

  case T_and: {
    rt_value = eng().CreateAnd(left, right);
    break;
  }
  case T_or: {
    rt_value = eng().CreateOr(left, right);
    break;
  }
  }
}

void CodegenVisitor::visit(This *node) {
  // TODO
}

void CodegenVisitor::visit(Print *node) {
  HOLD(PRINT);
  *this << node->args;
}

void CodegenVisitor::visit(List *node) {
  // TODO
  switch (call_stack.top()) {
  case StateType::BLOCK: {
    for (auto ptr: node->list) {
      *this << ptr;
    }
    break;
  }
  case StateType::PRINT: {
    for (auto ptr: node->list) {
      auto value = get_value(ptr);
      auto F = eng.load_ext_func("print" + ptr->token_type);
      eng().CreateCall(F, {value});
    }
    break;
  }
  default: assert(false);
  }
}

void CodegenVisitor::visit(Break *node) {
  // TODO
  eng().CreateBr(current_nextBB.value());
  Function *tf = eng().GetInsertBlock()->getParent();
  auto dummyBB = BasicBlock::Create(eng().getContext(), "dummy", tf);
  eng().SetInsertPoint(dummyBB);
}

void CodegenVisitor::visit(Return *node) {
  eng().CreateRet(get_value(node->expr));
}

void CodegenVisitor::visit(For *node) {
  *this << node->init_expr;
  auto parent_nxBB = current_nextBB;
  Function *tf = eng().GetInsertBlock()->getParent();
  auto condBB = BasicBlock::Create(eng().getContext(), "cond", tf);
  auto loopBB = BasicBlock::Create(eng().getContext(), "whileloop");
  auto nextBB = BasicBlock::Create(eng().getContext(), "next");
  current_nextBB = nextBB;
  // init
  eng().CreateBr(condBB);

  // cond
  eng().SetInsertPoint(condBB);
  auto cond = get_value(node->conditional_expr);
  eng().CreateCondBr(cond, loopBB, nextBB);

  // loop
  tf->getBasicBlockList().push_back(loopBB);
  eng().SetInsertPoint(loopBB);
  *this << node->stmt;
  *this << node->step_expr;
  eng().CreateBr(condBB);

  // next
  tf->getBasicBlockList().push_back(nextBB);
  eng().SetInsertPoint(nextBB);
  current_nextBB = parent_nxBB;
}

void CodegenVisitor::visit(While *node) {
  auto parent_nxBB = current_nextBB;
  Function *tf = eng().GetInsertBlock()->getParent();
  auto condBB = BasicBlock::Create(eng().getContext(), "cond", tf);
  auto loopBB = BasicBlock::Create(eng().getContext(), "whileloop");
  auto nextBB = BasicBlock::Create(eng().getContext(), "next");
  current_nextBB = nextBB;
  eng().CreateBr(condBB);
  // cond
  eng().SetInsertPoint(condBB);
  auto cond = get_value(node->conditional_expr);
  eng().CreateCondBr(cond, loopBB, nextBB);

  // loop
  tf->getBasicBlockList().push_back(loopBB);
  eng().SetInsertPoint(loopBB);
  *this << node->stmt;
  eng().CreateBr(condBB);

  // next
  tf->getBasicBlockList().push_back(nextBB);
  eng().SetInsertPoint(nextBB);
  current_nextBB = parent_nxBB;
}

void CodegenVisitor::visit(Block *node) {
  HOLD(BLOCK);
  for (auto&[name, variable]: node->aux.local_uid) {
    auto&[uid, type] = variable;
    eng.define_local_variable(uid, type);
  }
  *this << node->stmt_list;
}

void CodegenVisitor::visit(If *node) {

  Function *tf = eng().GetInsertBlock()->getParent();
  auto condition = get_value(node->condition);
  auto thenBB = BasicBlock::Create(eng().getContext(), "then", tf);
  auto elseBB = BasicBlock::Create(eng().getContext(), "else");
  auto nextBB = BasicBlock::Create(eng().getContext(), "cont");
  eng().CreateCondBr(condition, thenBB, elseBB);

  // if block
  eng().SetInsertPoint(thenBB);
  *this << node->if_stmt;
  eng().CreateBr(nextBB);

  // else block
  tf->getBasicBlockList().push_back(elseBB);
  eng().SetInsertPoint(elseBB);
  *this << node->else_stmt;
  eng().CreateBr(nextBB);

  // emit else block
  tf->getBasicBlockList().push_back(nextBB);
  eng().SetInsertPoint(nextBB);
}

void CodegenVisitor::visit(Prototype *node) {
  // SKIP
}

void CodegenVisitor::visit(Interface *node) {
  // SKIP
}

void CodegenVisitor::visit(ClassDecl *node) {
  // SKIP
}

void CodegenVisitor::visit(FunctionDecl *node) {
  // SKIP
}

void CodegenVisitor::visit(TypeArray *node) {
  // TODO
}

void CodegenVisitor::visit(TypeBase *node) {
  // TODO
}

void CodegenVisitor::visit(TypeUser *node) {
  // TODO
}

void CodegenVisitor::visit(Identifier *node) {
  // TODO
  switch (call_stack.top()) {
  case StateType::GET_VALUE: {
    rt_value = eng.fetch_local_id(node->uid);
    if (right_value) {
      rt_value = eng().CreateLoad(rt_value, "ld");
    }
    break;
  }
  }
}

void CodegenVisitor::visit(Assign *node) {
  node->right->token_type = node->left->token_type;
  auto right = get_value(node->right);
  auto left = get_value(node->left, false);
  eng().CreateStore(right, left);
  rt_value = left;
}

void CodegenVisitor::visit(TypedVariable *node) {
  // SKIP
}

void CodegenVisitor::visit(Program *node) {
  // SKIP
}

void CodegenVisitor::visit(NoAction *node) {
  // SKIP
}

