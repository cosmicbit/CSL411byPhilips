%{
#include <stdio.h>
int flag = 0;
void yyerror();
int yylex();
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
ArithmeticExpression: E {
    printf("\nResult = %d\n", $1);
    return 0;
};

E: E '+' E { $$ = $1 + $3; }
 | E '-' E { $$ = $1 - $3; }
 | E '*' E { $$ = $1 * $3; }
 | E '/' E { $$ = $1 / $3; }
 | E '%' E { $$ = $1 % $3; }
 | '(' E ')' { $$ = $2; }
 | NUMBER { $$ = $1; }
 ;

%%
int main() {
    printf("\nEnter any arithmetic expression:\n");
    yyparse();
    if (flag == 0) {
        printf("\nEntered arithmetic expression is valid.\n\n");
    }
    return 0;
}

void yyerror() {
    printf("\nEntered arithmetic expression is invalid.\n\n");
    flag = 1;
}
