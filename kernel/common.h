#pragma once
#include <memory>
#include <string>
#include <vector>
using std::make_shared;
using std::shared_ptr;
using std::vector;
// using Location = int;
class ASTNodeBase {
 public:
  virtual void accept(class Visitor& v) = 0;
  // Location loc_beg;
  // Location loc_end;
};
using node_ptr_t = shared_ptr<ASTNodeBase>;

#include "generated/Visitor.h"
#include "node_defs.h"


#include "generated/mknode.h"
