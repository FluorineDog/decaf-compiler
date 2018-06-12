#include <map>
#include <optional>
#include <set>
#include <string>
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
};

struct ClassBody {
  optional<string> extender;
  std::set<string> implementors;
  map<string, TypeEntry> variables;
  map<string, FuncEntry> functions;
};

struct InterfaceBody {
  map<string, FuncEntry> functions;
};

using ClassEntries = map<string, ClassBody>;
using InterfaceEntries = map<string, InterfaceBody>;

