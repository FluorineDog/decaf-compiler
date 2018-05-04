/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <cmath>
#include <string>
#include <iostream>
enum yytokentype{
  T_ID = 0, 
  T_integer = 1, 
  T_real = 2, 
  END_OF_FILE = 3, 
@#0#@
};
int yyval_int;
double yyval_real;
%}

DIGIT    [0-9]
ID       [A-Za-z_][A-Za-z0-9_]*
%x       C_COMMENT

%%

{DIGIT}+    {
                    yyval_real = atoi(yytext) ;
                    return T_int;
            }

[(-|+)]{DIGIT}+"."{DIGIT}*[(e|E)(-|+){DIGIT}+]        {
                    yyval_real = atof(yytext) ;
                    return T_real;
            }

@#1#@

{ID}        { return T_ID; }

"//".*\n    
"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }     

[ \t\n]+          /* eat up whitespace */

<<EOF>>     { return END_OF_FILE; }

.           printf( "Unrecognized character: %s\n", yytext );

%%

int main(int argc, char* argv[] )
{
  ++argv, --argc;  /* skip over program name */
  FILE* yyin;
  if ( argc > 0 )
          yyin = fopen( argv[0], "r" );
  else
          yyin = stdin;
  while(true){
    enum yytokentype enum_num = yylex();
    std::cout << enum_num << "***" << yytext << std::endl
    if(enum_num == END_OF_FILE){
      break;
    }
  }
}
