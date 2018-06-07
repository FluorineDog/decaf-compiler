#pragma once
#include <string>
#include "../build/parser.hxx"

class ASTNodeBase {
  virtual void accept(class Visitor&) = 0;
};

struct Location{
  int row;
  int column; 
};
template <int type_num>
class Terminal {
  std::string raw_text;
  Location loc_beg;
  Location loc_end;
};

class Vistor {
  virtual void visit(Terminal<NUM>* v) = 0;
};
