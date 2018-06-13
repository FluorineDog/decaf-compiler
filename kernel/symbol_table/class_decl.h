#pragma once
#include <map>
#include <optional>
#include <set>
#include <string>
#include <variant>
#include "../common.h"

using std::map;
using std::optional;
using std::set;
using std::string;
using std::tuple;
using std::vector;
using TypeEntry = std::string;
using VariableEntry = std::pair<string, string>;

struct FuncEntry {
  TypeEntry type;
  vector<VariableEntry> parameters;
  optional_node_ptr_t body;  // fake for prototype
  bool operator==(const FuncEntry& f) const {
    if (type != f.type) return false;
    bool is_equal =
        std::equal(parameters.begin(),    //
                   parameters.end(),      //
                   f.parameters.begin(),  //
                   f.parameters.end(),    //
                   [](const VariableEntry& a, const VariableEntry& b) {
                     return a.first == b.first;
                   });
    return is_equal;
  }
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

enum class StateType {
  Class,
  Extender,
  Implementor,
  Interface,
  Field,
  Function,
  Program
};
#include <stack>
using std::stack;
class StateHolder {
  stack<StateType>& list_call_stack;

 public:
  StateHolder(stack<StateType>& list_call_stack, StateType t)
      : list_call_stack(list_call_stack) {
    list_call_stack.push(t);
  }
  ~StateHolder() { list_call_stack.pop(); }
};
