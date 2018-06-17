#include <cassert>
#include "../generated/StaticAnalyseVisitor.h"
#include "../pure_common.h"
#include "class_decl.h"
using std::make_tuple;
int BlockExt::global_uid = 0;

class BuildAuxInfo {
public:
  enum class State { Unknown = 0, Processing, Ready, Base };

  void load_basetype() {
    auto base_vec = {"void", "bool", "int", "double", "string"};
    for (string type : base_vec) {
      type_record[type] = State::Base;
    }
  }

  BuildAuxInfo(ClassEntries& sym_table): sym_table(sym_table) {

  }

  // int as array_deep
  tuple<State, optional<TypeEntry>> visit_type(TypeEntry type) {
    // assign unknown for unknown type
    int len = type.size();
    bool isArray = false; while (len >= 2 && type.substr(len - 2, 2) == "[]") {
      // is array
      isArray = true;
      type = type.substr(0, len - 2);
      len = type.size();
    }
    auto state = type_record[type];
    auto typeOpt = isArray ? std::optional<TypeEntry>(type) : std::nullopt;
    return make_tuple(state, typeOpt);
  }

  bool is_decl_visited(string decl_name) {
    auto[s, arr_type] = visit_type(decl_name);
    assert(!arr_type);
    if (s == State::Ready || s == State::Base) {
      return true;
    }
    assert(s != State::Processing && "circular extends");
    assert(s == State::Unknown);
    type_record[decl_name] = State::Processing;
    return false;
  }

  InterfaceBody &fetch_complete_interface(string name) {
    auto body_ptr = sym_table.find(name);
    assert(body_ptr != nullptr);
    assert(std::holds_alternative<InterfaceBody>(*body_ptr));
    auto &body = std::get<InterfaceBody>(*body_ptr);
    decl(name, body);
    assert(is_decl_visited(name));
    return body;
  }

  ClassBody &fetch_complete_class(string name) {
    auto body_ptr = sym_table.find(name);
    assert(body_ptr != nullptr);
    assert(std::holds_alternative<ClassBody>(*body_ptr));
    auto &body = std::get<ClassBody>(*body_ptr);
    decl(name, body);
    assert(is_decl_visited(name));
    return body;
  }

  FuncEntry &fetch_complete_function(string class_name, string func_name) {
    auto &class_body = fetch_complete_class(class_name);
    auto ptr = class_body.functions.find(func_name);
    assert(ptr);
    return *ptr;
  }

  void decl(string decl_name, ClassBody &body) {
    if (is_decl_visited(decl_name)) {
      return;
    }

    auto class_name = decl_name;
    if (body.extender) {
      // visit parent first
      string parent_name = body.extender.value();
      auto &parent_body = fetch_complete_class(parent_name);
      // load_extender
      body.available = parent_body.available;
    }

    // variables
    for (auto[var_name, var_type] : body.variables) {
      visit_type(var_type);
      // use SeqMap: overlap
      body.available.variables.append(var_name, var_type);
    }

    // functions
    for (auto&[func_name, func_body] : body.functions) {
      auto rt_type = func_body.return_type;
      visit_type(rt_type);
      for (const auto&[type, _] : func_body.parameters) {
        visit_type(type);
      }
      // use map: override
      if (body.available.functors.count(func_name)) {
        auto &actual_class = body.available.functors[func_name];
        auto &actual_body = fetch_complete_function(actual_class, func_name);
        assert(actual_body == func_body);
      }
      body.available.functors[func_name] = class_name;
    }

    // checkup
    type_record[decl_name] = State::Ready;

    // checkInterface
    for (auto interface_name : body.implementors) {
      if (body.available.interfaces.count(interface_name)) {
        continue;
      }
      auto &interface_body = fetch_complete_interface(interface_name);
      for (auto&[func_name, func_body]: interface_body.functions) {
        assert(body.available.functors.count(func_name));
        auto &actual_class = body.available.functors[func_name];
        auto &actual_body = fetch_complete_function(actual_class, func_name);
        assert(actual_body == func_body);
      }
      body.available.interfaces.insert(interface_name);
    }
  }

  void decl(string decl_name, InterfaceBody &body) {
    if (is_decl_visited(decl_name)) {
      return;
    }
    for (auto&[func_name, func_body] : body.functions) {
      auto rt_type = func_body.return_type;
      visit_type(rt_type);
      for (const auto&[type, _] : func_body.parameters) {
        visit_type(type);
      }
      assert(!func_body.body);
    }
//    cerr << "wtf" << decl_name;
    type_record[decl_name] = State::Ready;
    // classes
  }

  void decl(string decl_name, DeclEntry &body) {
    std::visit([=](auto &body) { decl(decl_name, body); }, body);
  }

  void run() {
    load_basetype();
    for (auto&[decl_name, decl_body] : sym_table) {
      decl(decl_name, decl_body);
    }
    for(auto& [t, s]: type_record) {
//      cerr << "&&" << t;
      assert(s == State::Ready || s == State::Base);
    }

  }

private:
  map<TypeEntry, State> type_record;
  // Trace::Core core;
  ClassEntries &sym_table;
};

void build_stmt(ClassEntries& sym_table){

  for(auto& [class_name, class_body_x]:sym_table){
    if(!std::holds_alternative<ClassBody>(class_body_x)){
      continue;
    }
    auto& class_body = std::get<ClassBody>(class_body_x);
    for(auto &[func_name, func_body]: class_body.functions){
      StaticAnalyseVisitor visitor(sym_table, func_body);
      assert(func_body.body);
      func_body.body.value()->aux.load(func_body);
      visitor << func_body.body.value();
    }
  }
};

void static_analyse(ClassEntries& ce){
  BuildAuxInfo engine(ce);
  engine.run();
  build_stmt(ce);
}
