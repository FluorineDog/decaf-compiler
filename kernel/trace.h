#pragma once
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::stack;
using std::string;
using std::vector;
using oss = std::ostringstream;

class Trace {
 public:
  using Core = vector<vector<string>>;
  Trace(Core& core) : core(core), count(0) {
    core.emplace_back(vector<string>());
  }

  template <typename... Args>
  Trace(Core& core, Args&&... args) : core(core), count(1) {
    core.emplace_back(vector<string>());
    (*this)(args...);
  }

  void join_helper(oss& sout) {}

  template <typename T>
  void join_helper(oss& sout, T a) {
    sout << a;
  }

  template <typename T, typename... Args>
  void join_helper(oss& sout, T a, Args&&... args) {
    sout << a << ", ";
    join_helper(args...);
  }

  static void indenter(int level) {
    for (int i = 0; i < level; ++i) {
      switch (i % 3) {
        case 0:
          cout << ". ";
          break;
        case 1:
          cout << "| ";
          break;
        case 2:
          cout << "* ";
          break;
      }
    }
  }

  template <typename... Args>
  string join(Args&&... args) {
    string target;
    oss sout(target);
    join_helper(sout, args...);
    return target;
  }

  template <typename... Args>
  void operator()(Args&&... args) {
    string tag = join(args...);
    core.back().emplace_back(tag); 
  }

  template <typename... Args>
  void report(Args&&... args) {}

  ~Trace() {
    core.pop_back();
  }

 private:
  Core& core;
  int count;
  int level;
};
