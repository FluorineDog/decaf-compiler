#pragma once
#include <map>
#include <optional>
#include <set>
#include <string>
#include <type_traits>
#include <variant>
#include <stack>
#include <vector>
#include "pure_common.h"
using std::stack;
using std::map;
using std::optional;
using std::set;
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
  map<string, TypeEntry> variables;
  map<string, FuncEntry> functions;
  node_ptr_t body;
};

struct InterfaceBody {
  map<string, FuncEntry> functions;
};

using Entry = std::variant<ClassBody, InterfaceBody>;
using ClassEntries = map<string, Entry>;
// using InterfaceEntries = map<string, InterfaceBody>;

void print(const ClassEntries& sym_table);

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