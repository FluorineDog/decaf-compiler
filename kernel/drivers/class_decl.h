#pragma once
#include <algorithm>
#include <map>
#include <optional>
#include "driver_helper.h"
#include <set>
#include <stack>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include "pure_common.h"
using std::map;
using std::optional;
using std::set;
using std::stack;
using std::string;
using std::tuple;
using std::vector;

// #include "../common.h"
// #include "indent.h"
using TypeEntry = std::string;
using VariableEntry = std::pair<string, string>;

struct FuncEntry {
  TypeEntry type;
  vector<VariableEntry> parameters;
  optional_node_ptr_t body;  // fake for prototype
  bool operator==(const FuncEntry& f) const;
  bool operator!=(const FuncEntry& f) const { return *this != f; }
};

struct ClassBody {
  optional<string> extender;
  std::set<string> implementors;
  SeqMap<string, TypeEntry> variables;
  SeqMap<string, FuncEntry> functions;
  node_ptr_t body;

  // nullable
  TypeEntry* get_variable(string id) {
    return variables.find(id);
  }
  void insert_variable(string id, TypeEntry type) {}

  // nullable
  FuncEntry* get_function(string id) {
    auto iter = functions.find(id);
    return iter;
  }
};

struct InterfaceBody {
  SeqMap<string, FuncEntry> functions;
  const FuncEntry* get_function(const string& id) const {
    // auto iter = functions.find(id);
    // return iter == functions.end() ? nullptr : &iter->second;
    return functions.find(id);
  }
};

using DeclEntry = std::variant<ClassBody, InterfaceBody>;
using ClassEntries = SeqMap<string, DeclEntry>;
// using InterfaceEntries = map<string, InterfaceBody>;








enum class StateType {
  Class,
  Extender,
  Implementor,
  Interface,
  Field,
  Function,
  Prototype,
  Program
};

class StateHolder {
  stack<StateType>& list_call_stack;

 public:
  StateHolder(stack<StateType>& list_call_stack, StateType t)
      : list_call_stack(list_call_stack) {
    list_call_stack.push(t);
    // std::cerr << "(" << (int)t;
  }
  ~StateHolder() {
    // std::cerr << (int)list_call_stack.top() << ")";
    list_call_stack.pop();
  }
};

void print_sym_table(const ClassEntries& sym_table);
