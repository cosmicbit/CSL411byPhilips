%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern int yylval;
%}

%%

[0-9]+     { yylval = atoi(yytext); return NUMBER; }
[\t ]+     { /* Ignore whitespace */ }
\n         { return 0; }  // End of input
.          { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
