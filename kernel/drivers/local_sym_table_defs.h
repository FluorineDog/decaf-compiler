#pragma once
#include "driver_helper.h"
#include "class_decl.h"
struct BlockExt {
  using TypeLocal = pair<int, TypeEntry>;
  map<string, TypeLocal> local_uid;
  BlockExt *parent = nullptr;

  optional<TypeLocal> get_symbol(string id) const {
    const BlockExt *iter = this;
    while (iter) {
      if (iter->local_uid.count(id)) {
        return iter->local_uid.at(id);
      }
      iter = iter->parent;
    }
    return std::nullopt;
  }

  void load(FuncEntry &entry) {
    assert(local_uid.empty());
    for (auto& [type, id] : entry.parameters) {
      insert(type, id);
    }
  }

  void insert(TypeEntry type, string id){
    assert(local_uid.count(id) == 0);
    local_uid[id] = std::make_pair(get_uid(), type);
  }

  static int get_uid() { return global_uid++; }
private:
  static int global_uid;
};
