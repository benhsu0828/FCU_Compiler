%{
#include <stdio.h>
int Total_Num=0;
%}
%option noyywrap
%%
[-]?[0-9]+[;]? {
    printf("Integer: %s\n",yytext);
}
[-]?[0-9]+/[\n] {
    printf("Integer: %s\n",yytext);
}

[-]?[0-9]+[.][0-9]+[;]? {
    printf("Float: %s\n",yytext);
}
[-]?[0-9]+[.][0-9]+/[\n] {
    printf("Float: %s\n",yytext);
}

[a-zA-Z][a-zA-Z0-9_]*[;]? {
    printf("ID: %s\n",yytext);
}
[a-zA-Z][a-zA-Z0-9_]*/[\n] {
    printf("ID: %s \n",yytext);
}

[_][^;\n]*[;]? {
    printf("Error: %s \n",yytext);  //底線當頭
}
[_][^;\n]*/\n {
    printf("Error: %s \n",yytext);  //底線當頭，最後換行
}

[0-9]+([a-zA-Z0-9]|[_])[^;\n]*[;]? {
    printf("Error: %s \n",yytext);  //數字當頭，接底線或字母
}
[0-9]+([a-zA-Z0-9]|[_])[^;\n]*/\n {
    printf("Error: %s \n",yytext);  //數字當頭，接底線或字母，最後換行
}

[^;\n]*[.][^;\n]*[;]? {
    printf("Error: %s \n",yytext); //點當頭
}
[^;\n]*[.][^;\n]*/\n {
    printf("Error: %s \n",yytext); //點當頭，最後換行
}

[^;\n]*[.][^;\n]*[.][;]? {
    printf("Error: %s \n",yytext); //有兩個點以上
}
[^;\n]*[.][^;\n]*[.]/\n {
    printf("Error: %s \n",yytext); //有兩個點以上，最後換行
}

[-][^;\n]*[;]? {
    printf("Error: %s \n",yytext); //減當頭
}
[-][^;\n]*/\n {
    printf("Error: %s \n",yytext); //減當頭，最後換行
}

[^;\n]*[-][^;\n]*[;]? {
    printf("Error: %s \n",yytext); //減在其中
}
[^;\n]*[-][^;\n]*/\n {
    printf("Error: %s \n",yytext); //減在其中，最後換行
}

[;] {
    printf("Error: %s \n",yytext); //純分號
}
\n {}
%%
int main()
{
    yylex();
    return 0; 
}