/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
  enum yytokentype{

  }
%}

DIGIT    [0-9]
ID       [A-Za-z_][A-Za-z0-9_]*

%%

{DIGIT}+    {
            printf( "An integer: %s (%d)\n", yytext,
                    atoi( yytext ) );
            }

[(-|+)]{DIGIT}+"."{DIGIT}*[(e|E)(-|+){DIGIT}+]        {
            printf( "A float: %s (%g)\n", yytext,
                    atof( yytext ) );
            }

if|then|begin|end|procedure|function        {
            printf( "A keyword: %s\n", yytext );
            }

{ID}        printf( "An identifier: %s\n", yytext );
"void" { return T_void; }
"string" { return T_string; }
"bool" { return T_bool; }
"int" { return T_int; }
"double" { return T_double; }
"null" { return T_null; }
"true" { return T_true; }
"false" { return T_false; }
"class" { return T_class; }
"extends" { return T_extends; }
"interface" { return T_interface; }
"implements" { return T_implements; }
"this" { return T_this; }
"while" { return T_while; }
"if" { return T_if; }
"else" { return T_else; }
"for" { return T_for; }
"return" { return T_return; }
"break" { return T_break; }
"Print" { return T_Print; }
"ReadInteger" { return T_ReadInteger; }
"ReadLine" { return T_ReadLine; }
"NewArray" { return T_NewArray; }
"New" { return T_New; }

"{"[^}\n]*"}"     /* eat up one-line comments */

[ \t\n]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );

%%

int main(int argc, char* argv[] )
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
    }
