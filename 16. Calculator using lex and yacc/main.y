%{
    #include<stdio.h>
    int flag=0;
    void yyeror();
    int yylex()    
%}
%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%%
Arithmetic Expression: E{
    printf(")
}