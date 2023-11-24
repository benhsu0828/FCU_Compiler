%{
#include <stdio.h>
int Total_Num=0;
%}
%option noyywrap
%%
[;\n]                                   { /* Ignore semicolon and newline */ }
[-]?[0-9]+; {
    printf("Integer: %s\n",yytext);
}
[-]?[0-9]+/\n {
    printf("Integer: %s\n",yytext);
}
[-]?[0-9]+[.][0-9]+; {
    printf("Float: %s\n",yytext);
}
[-]?[0-9]+[.][0-9]+/\n {
    printf("Float: %s\n",yytext);
}
[a-zA-Z]([a-zA-Z0-9]*_*)*; {
    printf("ID: %s\n",yytext);
}
[a-zA-Z]([a-zA-Z0-9]*_*)*/\n {
    printf("ID: %s\n",yytext);
}
.+ {
    printf("Error: %s \n",yytext);
}
\n {}
%%
int main()
{
    yylex();
    return 0;
}
