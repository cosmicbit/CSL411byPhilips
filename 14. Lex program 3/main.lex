%{
#include<stdio.h>
char str[20];
int i;
%}
%%
[a-zA-Z]* {
    for(i=0; i<yyleng-2; i++){
        if((yytext[i]=='a') && (yytext[i+1]=='b') && (yytext[i+2]=='c')){
            yytext[i]='A';
            yytext[i+1]='B';
            yytext[i+2]='C';
        }
    }
    printf("%s", yytext);
}
[\t]+ {return 1;}
[.]+ {ECHO;}
[\n] {printf("%s", yytext);}
%%
int main(){
    fgets(str, sizeof(str), stdin);
    yy_scan_string(str);
    yylex();
    return 0;
}
int yywrap(){
    return 1;
}