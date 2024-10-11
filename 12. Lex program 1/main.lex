%{
#include<stdio.h>
int c=0,w=0,line=0,space=0;
%}
%%
[" "]* {space++;}
[\n] {line++;}
[a-zA-Z0-9]+ {w++,c=c+yyleng;}
%%
int yywrap(){
    return 1;
}
int main(){
    yyin=fopen("kit.txt","r");
    yylex();
    printf("No. of characters = %d \nNo. of words = %d\nNo. of spaces = %d\nNo. of lines = %d\n", c, w, space, line);
    return 0;
}