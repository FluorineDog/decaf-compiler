/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

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

%option noyywrap c++
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

.           { cout << "Unrecoginized token" << endl;}

%%


int main(int argc, char* argv[] )
{
  yyFlexLexer lexer(std::cin, std::cout);
  while(1){
    int enum_num = lexer.yylex();
    cout << enum_num << " <=> " << lexer.YYText() << endl;
    if(enum_num == END_OF_FILE){
      break;
    }
  }
}
