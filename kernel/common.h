#pragma once
// #include <memory>
#include <string>
#include <vector>
// using std::make_shared;
using std::vector;
// using Location = int;
class ASTNodeBase {
 public:
  virtual void accept(class Visitor& v) = 0;
  // Location loc_beg;
  // Location loc_end;
};
using node_ptr_t = ASTNodeBase*;

#include "generated/Visitor.h"
#include "node_defs.h"


#include "generated/mknode.h"

template <typename T>
T* extract(node_ptr_t node){
  return dynamic_cast<T*>(node);
}
