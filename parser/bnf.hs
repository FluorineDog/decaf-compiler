Program ::= Decl+
Decl ::= VariableDecl | FunctionDecl | ClassDecl | InterfaceDecl
VariableDecl ::= Variable ;
Variable ::= Type ident
Type ::= int | double | bool | string | ident | Type [ ]
TypeVoid ::= Type | void 
FunctionDecl ::= TypeVoid ident ( Formals ) StmtBlock
Formals ::= Variable,*
ClassDecl ::= class ident <extends ident> < implements ident,* > { Field* }
Field ::= VariableDecl | FunctionDecl
InterfaceDecl ::= interface ident { Prototype* }


Field
InterfaceDecl
Prototype
StmtBlock
