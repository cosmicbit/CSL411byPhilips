#include<stdio.h>
#include<string.h>
#include<ctype.h>

char production[10][10];
int count;
char first[10][10];
char follow[10][10];
char donefirst[10];
int cdonefirst=-1, cdonefollow=-1;
char donefollow[10];

void initializeFirstAndFollow(){
    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++){
            first[i][j]='\0';
            follow[i][j]='\0';
        }
    printf("initialised successfully\n");
}
void removeDuplicates(char *str) {
    int len = strlen(str);
    int index = 0; // To store index of the resultant string

    // Traverse the string
    for (int i = 0; i < len; i++) {
        int j;
        // Check if str[i] is present before it
        for (j = 0; j < i; j++) {
            if (str[i] == str[j]) {
                break;
            }
        }
        // If not present, then add it to the result
        if (j == i) {
            str[index++] = str[i];
        }
    }
    // Null terminate the result string
    str[index] = '\0';
}
void addToFirst(char c, char element){
    int j,k;
    j=0;
    while(first[j][0]!='\0'){
        if(first[j][0]==c){
            k=2;
            while(first[j][k]!='\0'){
                if(first[j][k]==element){
                    return;
                }
                k++;
            }
            
            first[j][k]=element;
            return;
        }
        j++;
    }
    first[j][0]=c;
    first[j][1]='=';
    first[j][2]=element;
}
void findFirst(char c, char firsts[]){
    int i,j,k;
    char temp[10]="";
    for(i=0; i<count; i++){
        if(production[i][0]==c){
            if(isupper(production[i][2])){
                findFirst(production[i][2], firsts);
            }
            else{
                sprintf(temp, "%c", production[i][2]);
                strcat(firsts, temp);
            }
        }
    }
    for(j=0; j<strlen(firsts); j++)
        addToFirst(c, firsts[j]);
}
void getFirst(char c, char array[]){
    int i,j, k;
    i=0;
    while(first[i][0]!='\0'){
        if(first[i][0]==c){
            j=2;
            k=0;
            while(first[i][j]!='\0'){
                array[k]=first[i][j];
                k++;
                j++;
            }
            array[k]='\0';
            return;
        }
        i++;
    }
}
void addToFollow(char c, char element){
    int j,k;
    j=0;
    while(follow[j][0]!='\0'){
        if(follow[j][0]==c){
            k=2;
            while(follow[j][k]!='\0'){
                if(follow[j][k]==element){
                    return;
                }
                k++;
            }
            
            follow[j][k]=element;
            return;
        }
        j++;
    }
    follow[j][0]=c;
    follow[j][1]='=';
    follow[j][2]=element;
}
void findFollow(char c, char follows[]){
    int i,j,k;
    char temp[10]="";
    char array[10]="";
    for(i=0; i<count; i++){
        for(j=2; j<strlen(production[i]); j++){
            if(production[i][j]==c){
                if(production[i][j+1]!='\0'){
                    if(isupper(production[i][j+1])){
                        strcpy(array, "");
                        getFirst(production[i][j+1], array);
                        if(strcmp(array, "")!=0){
                            strcat(follows, array);
                        }else{
                            findFollow(production[i][j+1], follows);
                        }
                    }else{
                        sprintf(temp, "%c", production[i][j+1]);
                        strcat(follows, temp);
                    }
                }else{
                    findFollow(production[i][j+1], follows);
                }
            }
        }
    }
    removeDuplicates(follows);
    for(j=0; j<strlen(follows); j++)
        addToFollow(c, follows[j]);
}
void printProduction(){
    printf("GRAMMAR\n\n");
    for(int i=0; i<count; i++){
        printf("%s\n", production[i]);
    }
}
void printFirst(){
    printf("First of Symbols\n\n");
    int i,j;
    i=0;
    while(first[i][0]!='\0'){
        printf("First(%c) = { ", first[i][0]);
        j=2;
        while(first[i][j] != '\0'){
            printf("%c, ", first[i][j]);
            j++;
        }
        printf("}\n");
        i++;
    }
}
void printFollow(){
    printf("\nFollow of Symbols\n\n");
    int i,j;
    i=0;
    while(follow[i][0]!='\0'){
        printf("Follow(%c) = { ", follow[i][0]);
        j=2;
        while(follow[i][j] != '\0'){
            printf("%c, ", follow[i][j]);
            j++;
        }
        printf("}\n");
        i++;
    }
}
void main(){
    count = 8;
    int i, j, xxx=0;
    char c;
    char firsts[10]="", follows[50]="";
	strcpy(production[0], "E=TR");
    strcpy(production[1], "R=+TR");
    strcpy(production[2], "R=#");
    strcpy(production[3], "T=FY");
    strcpy(production[4], "Y=*FY");
    strcpy(production[5], "Y=#");
    strcpy(production[6], "F=(E)");
    strcpy(production[7], "F=i");
    printProduction();

    initializeFirstAndFollow();
    for(i=count-1; i>=0; i--){
        c=production[i][0];
        for(j=0; j<cdonefirst; j++)
            if(c==donefirst[j])
                xxx=1;
        if(xxx==1)
            continue;
        findFirst(c,firsts);
        cdonefirst++;
        donefirst[cdonefirst]=c;
        for(j=0; j<strlen(firsts); j++)
            addToFirst(production[i][0], firsts[j]);
        strcpy(firsts, "");
    }
    printFirst();
    follow[0][0]='E';
    follow[0][1]='=';
    follow[0][2]='$';
    for(i=0; i<count; i++){
        c=production[i][0];
        findFollow(production[i][0],follows);
        for(j=0; j<strlen(follows); j++)
            addToFollow(production[i][0], follows[j]);
        strcpy(follows, "");
    }
    printFollow();
}
