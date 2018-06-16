#include "class_decl.h"
// #include "parser.hxx"
#include "common.h"
// #include "../node_defs.h"
// #include "../generated/Visitor.h"
// #include "../generated/PrintVisitor.h"
// #include "../generated/Visitor.h"
template <class T>
struct always_false : std::false_type {};


bool FuncEntry::operator==(const FuncEntry& f) const {
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

void print_sym_table(const ClassEntries& sym_table) {
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
                PrintVisitor v;
                v.level = level - 1;
                // v << func.body;
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
