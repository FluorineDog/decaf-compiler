/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
yyFlexLexer lexer;
#include "parser.hxx"
int yylex (void);
void yyerror (char const *);
%}

%option noyywrap c++
DIGIT    [0-9]
ID       [A-Za-z_][A-Za-z0-9_]*
%x       C_COMMENT
%%
{DIGIT}+    {
                    // yyval_real = atoi(yytext) ;
                    yylval = atoi(yytext); 
                    return NUM;
            }

[(-|+)]{DIGIT}+"."{DIGIT}*[(e|E)(-|+){DIGIT}+]        {
                    // yyval_real = atof(yytext) ;
                    yylval = atof(yytext); 
                    return NUM;
            }

@#lexer_rule_list#@

{ID}        { return ID; }

"//".*\n    
"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }     

[ \t\n]+          /* eat up whitespace */

<<EOF>>     { return END_OF_FILE;}

.           { cout << "Unrecoginized token" << endl;}

%%

int yylex (void){
  int enum_num = lexer.yylex();
  cout << enum_num << " <=> " << lexer.YYText() << endl;
  return enum_num;
}

void yyerror (char const * err_msg){
  cerr << err_msg << endl;
}



// int main(int argc, char* argv[] )
// {
//   while(1){
//     int enum_num = lexer.yylex();
//     cout << enum_num << " <=> " << lexer.YYText() << endl;
//     if(enum_num == END_OF_FILE){
//       break;
//     }
//   }
// }
