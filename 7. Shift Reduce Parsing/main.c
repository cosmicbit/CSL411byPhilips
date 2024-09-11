#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
char stack[50];
int tos=-1;
char buffer[50];
int cursor=0;

 
void printline(char str[]){
	int i;
	printf("$");
	for(i=0; i<=tos; i++){
		printf("%c", stack[i]);
	}
	printf("\t\t");
	for(i=0; i<cursor; i++)
		printf(" ");
	for(i=cursor; i<strlen(buffer); i++){
		printf("%c", buffer[i]);
	}
	printf("$\t\t");
	printf("%s\n", str);
}
// Function to get substr in C
char* getString(int pos, int len, char string[])
{
	int j=0;
	char* substring = (char*)malloc(50 * sizeof(char));
	for(int i=pos; i<len; i++){
		substring[j++]=string[i];
	}
	substring[j]='\0';
	return substring;
}
 
void pop(){
	if(tos!=-1)
		tos--;
	
}

void push(char element){
	char* temp;
	tos++;
	stack[tos]=element;
	stack[tos+1]='\0';
	int len=strlen(stack);
	for(int i=0; i<=tos; i++){
		temp=getString(tos-i, tos+1, stack);
		if(strcmp(temp,"E+E")==0){
			printline("reduce E->E+E\0");
			pop();
			pop();
			pop();
			push('E');
		}
		else if(strcmp(temp,"E*E")==0){
			printline("reduce E->E*E\0");
			pop();
			pop();
			pop();
			push('E');
		}
		else if(strcmp(temp,"(E)")==0){
			printline("reduce E->(E)\0");
			pop();
			pop();
			pop();
			push('E');
			
		}
		else if(strcmp(temp,"i")==0){
			printline("reduce E->i\0");
			pop();
			push('E');
			
		}
		if(strcmp(stack, "E")==0){
			if(cursor==strlen(buffer)){
				printline("Accepted\0");
				exit(0);
			}
		}
	}
 
}
void shift(){
	cursor++;
	push(buffer[cursor-1]);
}
void main(){
	printf("Enter an input string: ");
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		// Remove the newline character if present
		size_t len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n') {
		    buffer[len - 1] = '\0';
		}
	}
	printf("\n\nStack\t\tinput\t\taction\n");
	for(int i=0; i<strlen(buffer); i++){
		printline("Shift\0");
		shift();
	}
}
