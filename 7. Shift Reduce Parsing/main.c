#include<stdio.h>
#include<string.h>
 
char stack[50];
//stack[0]='$';
int tos=-1;
char buffer[50];
int cursor=0;
char substring[1000];
 
void printline(char str[50]){
 
	printf("%s\n", str);
	printf("$%s         ",stack);
	for(int i=cursor; i<strlen(buffer); i++){
		printf("%c", buffer[i]);
	}
	printf("        ");
}
// Function to get substr in C
void getString(int pos, int len, int i, char string[])
{
 
 
    while (i < len) {
        substring[i] = string[pos + i - 1];
        i++;
    }
 
    substring[i] = '\0';
 
    // Print the result
    printf("%s",substring);
    printf("\n");
}
 
void pop(){
	char element;
	if(tos!=-1)
		tos--;
}
void push(char element){
	char temp[50];
	tos++;
	stack[tos]=element;
	stack[tos+1]='\0';
	int len=strlen(stack);
	for(int i=0; i<len; i++){
		strcpy(temp,"");
		printf("\ntemp=%s\n", temp);
		printf("i=%d\n", i);
		printf("curlen=%d\n", (len-i));
		printf("source=%s\n",(stack+i));
		getString(i, len-i, 0, stack);
		strcpy(temp, substring);
		printf("\ntemp=%s\n", temp);
		if(strcmp(temp,"E+E")==0){
			pop();
			pop();
			printline("reduce E->E+E\0");
		}
		else if(strcmp(temp,"E*E")==0){
			pop();
			pop();
			printline("reduce E->E*E\0");
		}
		else if(strcmp(temp,"(E)")==0){
			pop();
			pop();
			pop();
			push('E');
			printline("reduce E->(E)\0");
		}
		else if(strcmp(temp,"i")==0){
			pop();
			push('E');
			printline("reduce E->i\0");
		}else if(strcmp(temp, "E")==0){
			if(cursor==strlen(buffer)){
				printline("Accepted\0");
			}
		}
	}
 
}
void shift(){
	push(buffer[cursor]);
	cursor++;
}
 
void main(){
	printf("Enter an input string: ");
	gets(buffer);
	printf("\n\nStack        input        action\n");
	printf("$%s         ",stack);
	for(int i=cursor; i<strlen(buffer); i++){
		printf("%c", buffer[i]);
	}
	printf("        ");
	for(int i=0; i<strlen(buffer); i++){
 
		shift();
		printline("Shift\0");
	}
}
