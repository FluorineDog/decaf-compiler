Program
Decl
VariableDecl
Variable
Type
FunctionDecl ::=::=
::=
::=
::=
::= Formals ::= ClassDecl ::= 




Type ident ( Formals ) StmtBlock |
void ident ( Formals ) StmtBlock
Variable+ , | ε
+
class ident 〈 extends ident 〉 〈 implements ident , 〉 { Field* }
Field
InterfaceDecl
Prototype
StmtBlock ::=
::=
::=
::= VariableDecl | FunctionDecl
interface ident { Prototype* }
Type ident ( Formals ) ; | void ident ( Formals ) ;
{ VariableDecl* Stmt* }
Stmt ::= 〈Expr〉 ; | IfStmt | WhileStmt | ForStmt |
BreakStmt | ReturnStmt | PrintStmt | StmtBlock
Expr ) Stmt 〈 else Stmt〉
IfStmt ::= if (
WhileStmt ::= while ( Expr )
ForStmt ::= for (
ReturnStmt ::= return
BreakStmt ::= break ;
PrintStmt
Expr ::=
::= LValue
Call ::=
::= Actuals ::= LValue = Expr | Constant | LValue | this | Call | ( Expr ) |
Expr + Expr | Expr - Expr | Expr * Expr | Expr / Expr |
Expr % Expr | - Expr | Expr < Expr | Expr <= Expr |
Expr > Expr | Expr >= Expr | Expr == Expr | Expr != Expr |
Expr && Expr | Expr || Expr | ! Expr | ReadInteger ( ) |
ReadLine ( ) | new ident | NewArray ( Expr , Type )
ident | Expr . ident | Expr [ Expr ]
ident ( Actuals ) | Expr . ident ( Actuals )
Expr+ , | ε
Constant ::= intConstant
Stmt
〈Expr〉 ; Expr ; 〈Expr〉 ) Stmt
〈Expr〉 ;
Print ( Expr+ , ) ;
| doubleConstant | boolConstant |
stringConstant | null