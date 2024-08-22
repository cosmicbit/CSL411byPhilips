#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
int isKeyword(char buffer[]){
	char keywords[7][10]={
	"int", "float", "char", "double", "include", "main", "return"
	};
	for(int i=0;i<7;i++){
		if(strcmp(keywords[i],buffer))
			return 1;
	}
	return 0;
}
int main(){
	FILE* fp = fopen("democode.txt","r");
	int i,j=0,k=0;
	char operators[6]="+-*/%=";
	char specialch[14]=",;[]{}#<>\'\"().";
	char ch,buffer[15],buf[10];
	while(!feof(fp)){
		ch=fgetc(fp);
		for(i=0;i<6;i++){
			if(ch==operators[i]){
				if(j!=0){
					buffer[j]='\0';
					j=0;
					if(isKeyword(buffer)){
						printf("%s is a keyword.\n",buffer);
					}else{
						printf("%s is an identifier.\n",buffer);
					}
				}
				if(k!=0){
					buf[k]='\0';
					k=0;
					printf("%s is a constant.\n",buf);
				}
				printf("%c is an operator.\n",ch);
				break;
			}
		}
		for(i=0;i<14;i++){
			if(ch==specialch[i]){
				if(j!=0){
					buffer[j]='\0';
			j=0;
			if(isKeyword(buffer)){
				printf("%s is a keyword.\n",buffer);
			}else{
				printf("%s is an identifier.\n",buffer);
			}
				}
				if(k!=0){
					buf[k]='\0';
					k=0;
					printf("%s is a constant.\n",buf);
				}
				printf("%c is an special character.\n",ch);
				break;
			}
		}
		
		if(isalpha(ch)){
			buffer[j++]=ch;
		}
		if(isdigit(ch)){
			buf[k++]=ch;
		}else if((ch==' ' || ch=='\n') && j!=0){
			buffer[j]='\0';
			j=0;
			if(isKeyword(buffer)){
				printf("%s is a keyword.\n",buffer);
			}else{
				printf("%s is an identifier.\n",buffer);
			}
		}else if((ch==' ' || ch=='\n') && k!=0){
			buf[k]='\0';
			k=0;
			printf("%s is a constant.\n",buf);
		}
	}
	return 0;
}
