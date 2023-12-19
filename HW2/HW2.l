%{
#include <stdio.h>
%}
%option noyywrap
%%
[0-9]+ {return(DIGIT);}
"(" {return(LPAREN);}
")" {return(RPAREN);}
"+" {return(PLUS);}


\n {}
%%
int main()
{
    yyparse();
    return 0; 
}
int yyerror(chr *msg){
    printf("ERROR: %s\n",msg);
}