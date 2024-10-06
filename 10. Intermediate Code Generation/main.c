#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct structure1{
    char res, op1, op, op2;
}intermediate_codes[30];
char* cutItAndAddthis(int from, int to, char replaceWith, char string[]){
    int i=0, j=0;
    static char substring[1000];
    while (j < from) {
        substring[i++] = string[j++];
    }
    substring[i++] = replaceWith;
    j=to;
    while(j < strlen(string)){
        substring[i++] = string[j++];
    }
    substring[i++] = '\0';

    return substring;
}

int main(){
    int i, j, nofcodes=0;
    char* expr=(char*)malloc(100 * sizeof(char));
    char tempChar='Z';
    char operators[4]={'/', '*', '+', '-'};
    printf("enter string: ");
    scanf("%s", expr);
    printf("\nIntermediate Code Generation\n\n");
    printf("The Intermediate Code               Expression\n");
    for(i=0; i<4; i++){
        for(j=0; j<strlen(expr); j++){
            if(operators[i]==expr[j]){

                intermediate_codes[nofcodes].op1=expr[j-1];
                intermediate_codes[nofcodes].op=expr[j];
                intermediate_codes[nofcodes].op2=expr[j+1];
                intermediate_codes[nofcodes].res=tempChar;
                printf("\t%c := %c %c %c               ", tempChar, expr[j-1], expr[j], expr[j+1]);
                expr=cutItAndAddthis(j-1, j+2, tempChar--, expr);
                printf("%s\n", expr);
            }
        }
    }
    printf("\t%s\n", expr);
    
    return 0;
}
// w:=a*b+c/d-e/f+g*h