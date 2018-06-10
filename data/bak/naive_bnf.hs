Program ::= Stmt+
Stmt ::= Expr? ; | PrintStmt
Expr ::= Expr + Expr | NUM | Call
NUM ::= NUM_int | NUM_double 
Call ::= ident ( Actuals )
Actuals ::= Expr,* 
PrintStmt ::= Print ( Expr,+ )
