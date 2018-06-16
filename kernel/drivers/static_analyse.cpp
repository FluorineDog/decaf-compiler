#include "static_analyse.h"
#include "../generated/StaticAnalyseVisitor.h"
#include "../pure_common.h"
using std::make_tuple;

void static_analyse(ClassEntries& sym_table) {}

#define HOLD(t) StateHolder sh(call_stack, StateType::t);
class StaticAnalyse {
  friend class StaticAnalyseVisitor;
  enum class State { Unknown = 0, Processing, Ready, Base };
  map<TypeEntry, State> type_record;

  void load_default() {
    auto base_vec = {"void", "bool", "int", "double", "string"};
    for (string type : base_vec) {
      type_record[type] = State::Base;
    }
  }
  StaticAnalyse(ClassEntries& sym_table) : sym_table(sym_table) {}

  // int as array_deep
  tuple<State, optional<TypeEntry>> visit_type(TypeEntry type) {
    // assign unknown for unknown type
    int len = type.size();
    bool isArray = false;
    while (len >= 2 && type.substr(len - 2, 2) == "[]") {
      // is array
      isArray = true;
      type = type.substr(0, len - 2);
      len = type.size();
    }
    auto state = type_record[type];
    auto typeOpt = isArray ? optional<TypeEntry>(type) : std::nullopt;
    return make_tuple(state, typeOpt);
  }

  void decl(string class_name, ClassBody& body) {}

  void decl(string interface_name, InterfaceBody& body) {
    // nothing to do
    for (auto& [func_name, func_body] : body.functions) {
      auto rt_type = func_body.type;
      for (auto& [type, _] : func_body.parameters) {
        visit_type(type);
      }
    }
  }

  void top() {
    for (auto& [decl_name, decl_body] : sym_table) {
      cout << decl_name;
      std::visit(
          [&](auto&& decl_body) {
            using T = std::decay_t<decltype(decl_body)>;
            decl(decl_name, decl_body);
          },
          decl_body);
    }
  }
  StaticAnalyseVisitor visitor;
  std::set<string> type_visited;
  stack<StateType> call_stack;
  ClassEntries& sym_table;
};
