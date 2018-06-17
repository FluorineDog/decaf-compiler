#pragma once
// #include <memory>
#include <string>
#include <vector>
#include <optional>
// using std::make_shared;
using std::vector;
// using Location = int;
class ASTNodeBase {
public:
  virtual void accept(class Visitor &v) = 0;
  ASTNodeBase() { token_type = "@undefined"; }
private:
  std::string token_type;
  // Location loc_beg;
  // Location loc_end;
};
using node_ptr_t = ASTNodeBase *;
using optional_node_ptr_t = std::optional<node_ptr_t>;

