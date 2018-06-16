#include "static_analyse.h"
#include "../generated/StaticAnalyseVisitor.h"
#include "../pure_common.h"

void static_analyse(ClassEntries& sym_table) {}

#define HOLD(t) StateHolder sh(call_stack, StateType::t);
class StaticAnalyse {
  friend class StaticAnalyseVisitor;
  StaticAnalyse(ClassEntries& sym_table) : sym_table(sym_table) {}

  void check(TypeEntry type) {}

  void decl(string class_name, ClassBody& body) {}

  void decl(string interface_name, InterfaceBody& body) {
    // nothing to do
    for (auto& [func_name, func_body] : body.functions) {
      auto rt_type = func_body.type;
      for (auto& [type, _] : func_body.parameters) {
        check(type);
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
