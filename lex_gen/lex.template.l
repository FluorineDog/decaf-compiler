/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
enum yytokentype{
  T_ID = 0, 
  T_integer = 1, 
  T_float = 2, 
@#0#@
  };
%}

DIGIT    [0-9]
ID       [A-Za-z_][A-Za-z0-9_]*
%x       C_COMMENT

%%

{DIGIT}+    {
            printf( "An integer: %s (%d)\n", yytext,
                    atoi( yytext ) );
            }

[(-|+)]{DIGIT}+"."{DIGIT}*[(e|E)(-|+){DIGIT}+]        {
            printf( "A float: %s (%g)\n", yytext,
                    atof( yytext ) );
            }

@#1#@

{ID}        printf( "An identifier: %s\n", yytext );

"//".*\n    
"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }     

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
