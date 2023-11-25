%{
#include <stdio.h>
int Total_Num=0;
%}
%option noyywrap
%%
[0-9]+ {
    printf("Find a Number: %s\n",yytext);
    Total_Num++;
}
. {}
\n {}
%%
int main()
{
    yylex();
    printf("Total_Num = %d\n",Total_Num);
    return 0;
}
/*
[^;\n]*[;] {
    printf("Error: %s \n",yytext);  
}
    */