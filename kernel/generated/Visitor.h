class Visitor {
 public:
  virtual void visit(class Integer* node) = 0;
  virtual void visit(class BinaryExpr* node) = 0;
  virtual void visit(class Block* node) = 0;
};
