#include "../common.h"
auto mkInteger(int num) {
  auto node = make_shared<Integer>();
  node->num = num;
  return node;
}

auto mkBinaryExpr(node_ptr_t left, int op, node_ptr_t right) {
  auto node = make_shared<BinaryExpr>();
  node->left = left;
  node->op = op;
  node->right = right;
  return node;
}

auto mkBlock() {
  auto node = make_shared<Block>();
  return node;
}
