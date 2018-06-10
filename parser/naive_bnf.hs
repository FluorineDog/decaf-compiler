Program ::= Stmt+
Stmt ::= Expr? ; | PrintStmt
Expr ::= Expr + Expr | NUM | Call
NUM ::= NUM_integer | NUM_real 
Call ::= ident ( Actuals )
Actuals ::= Expr,* 
PrintStmt ::= Print( Expr,+ )
