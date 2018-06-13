#pragma once
#include "pure_common.h"
// FUCK
#include "generated/Visitor.h"
#include "internal.h"
#include "node_defs.h"

#include "generated/mknode.h"

template <typename T>
T* extract(node_ptr_t node) {
  return dynamic_cast<T*>(node);
}
