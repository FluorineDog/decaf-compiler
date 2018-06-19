#pragma once
#include <algorithm>
#include <map>
#include <optional>
#include <cassert>
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
using std::pair;

// #include "../common.h"
// #include "indent.h"
using TypeEntry = std::string;
using VariableEntry = std::pair<string, string>;

struct FuncEntry {
  TypeEntry return_type;
  vector<VariableEntry> parameters;
  optional<class Block*> body;  // fake for prototype
  bool operator==(const FuncEntry &f) const;
  bool operator!=(const FuncEntry &f) const { return *this != f; }
};

struct ClassBody {
  optional<string> extender;
  std::set<string> implementors;
  SeqMap<string, TypeEntry> variables;
  SeqMap<string, FuncEntry> functions;

  struct Available {
    SeqMap<string, TypeEntry> variables;
    map<string, string> functors;
    set<string> interfaces;
  } available;

  // nullable
  TypeEntry *get_variable(string id) {
    return variables.find(id);
  }
  void insert_variable(string id, TypeEntry type) {}

  // nullable
  FuncEntry *get_function(string id) {
    auto iter = functions.find(id);
    return iter;
  }
};

struct InterfaceBody {
  SeqMap<string, FuncEntry> functions;
  const FuncEntry *get_function(const string &id) const {
    // auto iter = functions.find(id);
    // return iter == functions.end() ? nullptr : &iter->second;
    return functions.find(id);
  }
};

using DeclEntry = std::variant<ClassBody, InterfaceBody>;
//using ClassEntries = SeqMap<string, DeclEntry>;
// using InterfaceEntries = map<string, InterfaceBody>;
class ClassEntries : public SeqMap<string, DeclEntry> {
public:
  using SeqMap<string, DeclEntry>::SeqMap;
  TypeEntry fetch_complete_variable(string class_name, string id) const{
    auto cls = fetch_complete_class(class_name);
    auto variable_ptr = cls.get_variable(id);
    assert(variable_ptr);
    return *variable_ptr;
  }
  const InterfaceBody &fetch_complete_interface(string name) const{
    auto body_ptr = this->find(name);
    assert(body_ptr != nullptr);
    assert(std::holds_alternative<InterfaceBody>(*body_ptr));
    auto &body = std::get<InterfaceBody>(*body_ptr);
    return body;
  }

  const ClassBody &fetch_complete_class(string name) const{
    auto body_ptr = this->find(name);
    assert(body_ptr != nullptr);
    assert(std::holds_alternative<ClassBody>(*body_ptr));
    auto &body = std::get<ClassBody>(*body_ptr);
    return body;
  }

  const FuncEntry &fetch_complete_function(string class_name, string func_name) const{
    auto &class_body = fetch_complete_class(class_name);
    auto ptr = class_body.functions.find(func_name);
    assert(ptr);
    return *ptr;
  }
};

enum class StateType {
  CLASS,
  EXTENDER,
  IMPLEMENTOR,
  INTERFACE,
  FIELD,
  FUNCTION,
  PROTOTYPE,
  PROGRAM,
  GET_ID,
  GET_TYPE,
  PRINT
};

class StateHolder {
  stack<StateType> &list_call_stack;

public:
  StateHolder(stack<StateType> &list_call_stack, StateType t)
      : list_call_stack(list_call_stack) {
    list_call_stack.push(t);
    // std::cerr << "(" << (int)t;
  }
  ~StateHolder() {
    // std::cerr << (int)list_call_stack.top() << ")";
    list_call_stack.pop();
  }
};

void print_sym_table(const ClassEntries &sym_table);
