%{
#include <stdio.h>
#include "calc.tab.h"
%}
%option noyywrap
%%
[0-9]+ { yylval = atoi(yytext);
        return(DIGIT);}
"(" {return(LPAREN);}
")" {return(RPAREN);}
"+" {return(PLUS);}
"-" {return(MINUS);}
"*" {return(MULT);}
"/" {return(DIV);}
\n {return('\n');}

%%
int main()
{
    yyparse();
    return 0; 
}
int yyerror(char *msg){
    printf("ERROR: %s\n",msg);
}