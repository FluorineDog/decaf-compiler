#pragma once
#include <map>
#include <optional>
#include <set>
#include <string>
#include <type_traits>
#include <variant>
#include "../common.h"
#include "internal.h"

using std::map;
using std::optional;
using std::set;
using std::string;
using std::tuple;
using std::vector;

using TypeEntry = std::string;
using VariableEntry = std::pair<string, string>;
template<class T> struct always_false : std::false_type {};

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

inline void print(const ClassEntries& sym_table) {
  int level = 0;
  Indent logger(level);
  logger("TopEntries", sym_table.size());
  for (const auto& [name, body] : sym_table) {
    Indent logger(level);
    // logger("ClassOrInterface", name);
    std::visit(
        [&level, name](auto&& arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, ClassBody>) {
            Indent logger(level, "Class", name);
            const ClassBody& body = arg;
            if (body.extender) logger("Extender", body.extender.value());
            for (auto impl : body.implementors) {
              logger("ImplementItem", impl);
            }
            for (auto& [id, type] : body.variables) {
              logger("Variable", type, id);
            }
            for (auto& [name, func] : body.functions) {
              logger("Function", name, "->", func.type);
              {
                Indent logger(level);
                for (auto [type, name] : func.parameters) {
                  logger("Parameter", type, name);
                }
              }
            }
          } else if constexpr (std::is_same_v<T, InterfaceBody>) {
            Indent logger(level, "Interface", name);
            const InterfaceBody& body = arg;
            for (auto& [name, func] : body.functions) {
              logger("Prototype", name, "->", func.type);
              {
                Indent logger(level);
                for (auto [type, name] : func.parameters) {
                  logger("parameter", type, name);
                }
              }
            }
          } else {
            static_assert(always_false<T>::value, "WTF");
          }
        },
        body);
  }
}

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
#include <stack>
using std::stack;
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
