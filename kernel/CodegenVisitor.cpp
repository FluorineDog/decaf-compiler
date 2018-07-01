// Template
#include <llvm_driver/llvm.h>
#include "generated/CodegenVisitor.h"
#include "indent.h"
#include "llvm_driver/llvm_inc.h"
/*
 private:
  class LLVMEngine& eng;
  llvm::Value* rt_value;
  llvm::StructType* rt_type;
  BlockExt* block_aux;
  stack<StateType> call_stack;
  bool right_value;
  const string current_class_name;
  std::optional<llvm::BasicBlock*> current_nextBB;
 public:
  CodegenVisitor& operator<<(node_ptr_t node){
    node->accept(*this);
    return *this;
  }
  CodegenVisitor(class LLVMEngine& eng, BlockExt* block_aux, string class_name);
  llvm::Value* node_value(node_ptr_t node, bool rvalue = true);
  llvm::StructType* node_type(node_ptr_t node);
*/
#define HOLD(t) StateHolder sh(call_stack, StateType::t);
//using namespace llvm;

#include "llvm_driver/llvm.h"
#include "llvm/IR/DataLayout.h"
CodegenVisitor::CodegenVisitor(class LLVMEngine &eng, BlockExt *block_aux, string class_name)
    : eng(eng), block_aux(block_aux), current_class_name(class_name) {
  call_stack.push(StateType::PROGRAM);
}

Value *CodegenVisitor::node_value(node_ptr_t node, bool is_right_value) {
  HOLD(GET_VALUE);
  bool old_flag = right_value;
  right_value = is_right_value;
  rt_value = nullptr;
  *this << node;
  assert(rt_value);
  right_value = old_flag;
  return rt_value;
}
StructType *CodegenVisitor::node_type(node_ptr_t node) {
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
  rt_value = eng.create_nullptr();
}

void CodegenVisitor::visit(Call *node) {
  // TODO
  auto func_name = node->ident_name;
  auto issuer = node->domain_expr ?
                node_value(node->domain_expr.value())
                                  : eng.getArg(-1);
  auto issuer_type = node->domain_expr ?
                     node->domain_expr.value()->token_type : current_class_name;
  auto ptrAddr = eng().CreateGEP(issuer, {eng().getInt32(0), eng().getInt32(0)});
  auto sym_ptr_raw = eng().CreateLoad(ptrAddr, "loadSymPtr");
  auto sym_ptr = eng().CreateBitOrPointerCast(sym_ptr_raw, eng.external.table_type->getPointerTo());
  int fid = eng.fetch_func_name_uid(func_name);
  auto idObj = eng().getInt32(fid);

  auto func_ptr_raw = eng().CreateCall(eng.load_ext_func("load_ptr"), {sym_ptr, idObj});

  auto f_t = eng.get_function_type(issuer_type, func_name);
  auto functor = eng().CreateBitOrPointerCast(func_ptr_raw, f_t->getPointerTo());

  vector<Value *> args;
  auto raw_issuer = eng().CreateBitOrPointerCast(issuer, eng().getInt8PtrTy());
  args.push_back(raw_issuer);
  for (auto ptr: node->actuals->list) {
    args.push_back(node_value(ptr));
  }
  auto ret = eng().CreateCall(functor, args);
  rt_value = ret;
}

void CodegenVisitor::visit(Index *node) {
  // TODO
}

void CodegenVisitor::visit(MemberDot *node) {
  auto value = node_value(node->expr);
  int loc = eng.fetch_variable_uid(node->expr->token_type, node->ident_name);
  auto memAddr = eng().CreateGEP(value, {eng.create_IntObj(0), eng.create_IntObj(loc)});
  if (right_value) {
    rt_value = eng().CreateLoad(memAddr, "ld");
  } else {
    rt_value = memAddr;
  }
}

void CodegenVisitor::visit(NewArray *node) {
  // TODO
}

void CodegenVisitor::visit(New *node) {
  // TODO
  auto type = node_type(node->type);
  int size = eng.get_sizeof(type);
  auto size_obj = eng.create_IntObj(size);
  auto F = eng.load_ext_func("dog_malloc");
  auto raw_value = eng().CreateCall(F, {size_obj}, "dog_malloc");
  auto cast_value = eng().CreatePointerCast(raw_value, type->getPointerTo());
  auto index0 = eng.create_IntObj(0);
  auto memAddr = eng().CreateGEP(cast_value, {index0, index0}, "lenAddr");
  auto sym_ptr = eng.fetch_sym_ptr(node->token_type);
  eng().CreateStore(sym_ptr, memAddr);
  rt_value = cast_value;
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
    auto value = node_value(node->expr);
    assert(set<string>({"int", "double"}).count(node->token_type));
    rt_value = eng().CreateNeg(value);
    break;
  }
  case '!': {
    auto value = node_value(node->expr);
    assert(node->token_type == "bool");
    rt_value = eng().CreateNot(value, "not");
    break;
  }
  }
}

void CodegenVisitor::visit(BinaryExpr *node) {
  auto left = node_value(node->left);
  auto right = node_value(node->right);
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
    if (is_user_type(node->left->token_type)) {
      left = eng().CreatePtrToInt(left, Type::getInt64Ty(eng.getContext()));
      right = eng().CreatePtrToInt(right, Type::getInt64Ty(eng.getContext()));
    }
    if (node->op == T_eq) {
      rt_value = eng().CreateICmpEQ(left, right);
    } else {
      rt_value = eng().CreateICmpNE(left, right);
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
  assert(right_value);
  rt_value = eng.getArg(-1);
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
      auto value = node_value(ptr);
      auto F = eng.load_ext_func("print" + ptr->token_type);
      eng().CreateCall(F, {value});
    }
    break;
  }
  default: assert(false);
  }
}

void CodegenVisitor::visit(Break *node) {
  eng().CreateBr(current_nextBB.value());
  eng.createDummy();
}

void CodegenVisitor::visit(Return *node) {
  eng().CreateRet(node_value(node->expr));
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
  auto cond = node_value(node->conditional_expr);
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
  auto cond = node_value(node->conditional_expr);
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
  auto condition = node_value(node->condition);
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
  assert(false);
}

void CodegenVisitor::visit(TypeUser *node) {
  // TODO
  assert(call_stack.top() == StateType::GET_TYPE);
  rt_type = eng.get_struct(node->token_type);
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
  auto right = node_value(node->right);
  auto left = node_value(node->left, false);

  if (node->right->token_type != node->left->token_type) {
    auto left_type = eng.get_type(node->left->token_type);
    auto tmp = eng().CreatePointerCast(right, left_type);
    eng().CreateStore(tmp, left);
  } else {
    eng().CreateStore(right, left);
  }

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


