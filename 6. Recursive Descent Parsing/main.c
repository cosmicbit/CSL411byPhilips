#include<stdio.h>
#include<string.h>
#include<ctype.h>
 
char input[100];
int i=0, error=0;
 
void E();
void Edash();
void T();
void Tdash();
void F();
void main(){
	printf("Enter an arithmetic expression: ");
	gets(input);
	E();
	if(strlen(input)==i && error==0)
		printf("Accepted\n");
	else
		printf("Rejected\n");
}
void E(){
	T();
	Edash();
}
 
void Edash(){
	if(input[i]=='+'){
		i++;
		T();
		Edash();
	}
}
 
void T(){
	F();
	Tdash();
}
 
void Tdash(){
	if(input[i]=='*'){
		i++;
		F();
		Tdash();
	}
}
 
void F(){
	if(isalnum(input[i]))
		i++;
	else if(input[i]=='('){
		i++;
		E();
		if(input[i]==')')
			i++;
		else
			error=1;
	}
	else
		error=1;
}
