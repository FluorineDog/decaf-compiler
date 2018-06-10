Program ::= Decl+
ident ::= ID
Decl ::= VariableDecl | FunctionDecl | ClassDecl | InterfaceDecl
VariableDecl ::= Variable ;
Variable ::= Type ident

Type ::= T_int | T_double | T_bool | T_string | ident | Type [ ]
TypeVoid ::= Type | T_void 
FunctionDecl ::= TypeVoid ident ( Formals ) StmtBlock
Formals ::= Variable,*
ClassDecl ::= T_class ident Extender? Implementor? { Field* }
Extender ::= T_extends ident
Implementor ::= T_implements ident?
Field ::= VariableDecl | FunctionDecl

InterfaceDecl ::= T_interface ident { Prototype* }
Prototype ::= TypeVoid ident ( Formals ) 
StmtBlock ::= { VariableDecl* Stmt* }
Stmt ::= Expr? ; | IfStmt | WhileStmt | ForStmt | \
 BreakStmt | ReturnStmt | PrintStmt | StmtBlock 

IfStmt ::=  T_if ( Expr ) Stmt ElseTail?
ElseTail ::= T_else Expr
WhileStmt ::= T_while ( Expr ) Stmt
ForStmt ::= T_for ( Expr? ; Expr ; Expr? ) Stmt
ReturnStmt ::= T_return Expr? ;
BreakStmt ::= T_break ;
PrintStmt ::= T_Print ( Expr,+ ) ;

Expr ::= Constant | LValue = Expr | LValue | T_this | Call | ( Expr ) | \
 - Expr | T_ReadInteger ( ) | T_ReadLine ( ) | T_New ident  | \
 T_NewArray ( Expr , Type ) 
LValue ::= ident | Expr . ident | Expr [ Expr ]
Call ::= ident ( Actuals ) | Expr . ident ( Actuals )
Actuals ::= Expr,*
Constant ::= NUM_int | NUM_double | T_null
