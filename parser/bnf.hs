Program ::= Decl+
Decl ::= VariableDecl | FunctionDecl | ClassDecl | InterfaceDecl
VariableDecl ::= Variable ;
Variable ::= Type ident
Type ::= int | double | bool | string | ident | Type [ ]
TypeVoid ::= Type | void 
FunctionDecl ::= TypeVoid ident ( Formals ) StmtBlock
Formals ::= Variable,*
ClassDecl ::= class ident Extender? Implementor? { Field* }
Extender ::= extends ident
Implementor ::= implements ident?
Field ::= VariableDecl | FunctionDecl
InterfaceDecl ::= interface ident { Prototype* }
Prototype ::= TypeVoid ident ( Formals ) 
StmtBlock ::= { VariableDecl* Stmt* }
Stmt ::= Expr? ; | IfStmt | WhileStmt | ForStmt | BreakStmt | ReturnStmt | PrintStmt | StmtBlock 
IfStmt ::=  if ( Expr ) Stmt < else Stmt > 

