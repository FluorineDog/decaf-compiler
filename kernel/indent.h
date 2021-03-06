#pragma once
#include <iostream>
#include <string>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Indent {
 public:
  Indent(int& level) : level(level) { level++; }
  template <typename... Args>
  Indent(int& level, Args&&... args) : level(level) {
    level++;
    (*this)(args...);
  }
  void printer_helper() {}
  template <typename T>
  void printer_helper(T a) {
    cout << a;
  }
  template <typename T, typename... Args>
  void printer_helper(T a, Args&&... args) {
    cout << a << ", ";
    printer_helper(args...);
  }
  template <typename... Args>
  void operator()(Args&&... args) {
    for (int i = 0; i < level - 1; ++i) {
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
    std::cout << "<";
    printer_helper(args...);
    cout << ">" << endl;
  }
  ~Indent() { level--; }

 private:
  int& level;
};
