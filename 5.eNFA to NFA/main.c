#include<stdio.h>
#include<stdlib.h>

#define MAX_STATES 100
#define MAX_ALPHABET 26
#define MAX_NEXT_STATES 10

int NFATransitions[MAX_STATES][MAX_ALPHABET][MAX_NEXT_STATES], nNewStates=0, nFinalState, finalStates[20], nNFATransitions=0;
int epsilon_trans[20][2],epsilon_closure[MAX_STATES][MAX_STATES];

void initializeENFATransitions() {
    for (int i = 0; i < MAX_STATES; i++)
        for (int j = 0; j < MAX_ALPHABET; j++)
            for (int k = 0; k < MAX_NEXT_STATES; k++)
                NFATransitions[i][j][k] = -1;  // No transition initially
}
void initializeEClosure(){
	for(int i=0; i<MAX_STATES; i++)
		for(int j=0; j<MAX_STATES; j++)
			epsilon_closure[i][j]=-1;
}
void addENFATransition(int state, int symbol, int nextState) {
    int j;
    for (j = 0; j < MAX_NEXT_STATES; j++) {
        if (NFATransitions[state][symbol][j] == -1) {
            NFATransitions[state][symbol][j] = nextState;
            break;
        }
    }
    if (j == MAX_NEXT_STATES) {
        printf("Error: Too many transitions for state %d on input %d\n", state, symbol);
    }
}

void printENFATransitions(int s, int n, int states[], char input[]){
	for (int i = 0; i < s; i++){  
        for (int j = 0; j < n; j++){
            for (int k = 0; k < MAX_NEXT_STATES; k++)
                if(NFATransitions[states[i]][input[j]-97][k] != -1){
					printf("%d\t",states[i]);
            		printf("%c\t",input[j]);
                    printf("%d\n", NFATransitions[states[i]][input[j]-97][k]);
				}
                else
                    break;
        }
    }
}
void getENFATransition(int s, int n, int state, char input){
    for (int k = 0; k < MAX_NEXT_STATES; k++)
        if(NFATransitions[state][input-97][k] != -1){
			printf("%d\t",state);
            printf("%c\t",input);
            printf("%d\n", NFATransitions[state][input-97][k]);
		}
        else
        	break;
}

void findClosure(int epsilon_closure[], int state, int epsilon_trans[][2], int nEpsilonTrans){
	int i,j;
	for(i=0; i<nEpsilonTrans; i++){
		if(epsilon_trans[i][0]==state){
			j=0;
			while(epsilon_closure[j] != -1)
				j++;
			epsilon_closure[j]=epsilon_trans[i][1];
			findClosure(epsilon_closure, epsilon_trans[i][1], epsilon_trans, nEpsilonTrans);
		}
	}
}
void printETransitions(int nEpsilonTrans){
	printf("\nEpsilon Transitions\n");
	for(int i=0;i<nEpsilonTrans; i++)
		printf("%d e %d\n",epsilon_trans[i][0],epsilon_trans[i][1]);
}
int main(){
    int s, n, i, j, k, startState;
	initializeEClosure();
	printf("Enter the no. of states: ");
	scanf("%d",&s);
	s=3;

	int states[s];
	printf("Enter the states: ");
	for(i=0;i<s;i++){
		scanf("%d",&states[i]);
		j=0;
		while(epsilon_closure[states[i]][j] != -1)	j++;
		epsilon_closure[states[i]][j] = states[i];
	}
	printf("Enter start state: ");
	scanf("%d",&startState);
 
	printf("Enter no. of final states: ");
	scanf("%d",&nFinalState);
	
	printf("Enter final states:");
	for(i=0; i<nFinalState; i++)
		scanf("%d",&finalStates[i]);
 
	printf("Enter the no. of Alphabets:");
	scanf("%d",&n);
	char input[n];
	printf("Enter the Alphabets:\n[Note: Only input alphabets]\n");
	for(i=0; i<n; i++){
		getchar();
		input[i]=getchar();	
	}
	input[n] = '\0';  // Null-terminate the string (if treating it as a string)
	
	printf("Enter no. of NFA Transitions: ");
	scanf("%d",&nNFATransitions);
	printf("Enter Transitions:\n");
	initializeENFATransitions();
	int cs, ns;
	char a;
	j=0;
	for(i=0; i<nNFATransitions; i++){
		scanf("%d %c %d", &cs, &a, &ns);
		addENFATransition(cs, a-97, ns);
		if(a == 'e'){
			epsilon_trans[j][0]=cs;
			epsilon_trans[j++][1]=ns;
		}
	}
	int nEpsilonTrans=j;
	printf("\n\n");
	printENFATransitions(s,n,states,input);
	printETransitions(nEpsilonTrans);
	
	for(i=0; i<s; i++){
		findClosure(epsilon_closure[states[i]], states[i], epsilon_trans, nEpsilonTrans);
		printf("Epsilon closure of q%d = { ",states[i]);
		j=0;
		while(epsilon_closure[states[i]][j] != -1){
			printf("q%d ",epsilon_closure[states[i]][j]);
			j++;
		}
		printf("}\n");
	}
    
	for(i=0; i<s; i++){
		
		for(j=0; j<n; j++){
			k=0;
			while(epsilon_closure[states[i]][k] != -1){
				printf("state=%d\t", states[i]);
				printf("Closure[%d]=%d\t", k, epsilon_closure[states[i]][k]);
				printf("input=%c\n", input[j]);
				getENFATransition(s, n, epsilon_closure[states[i]][k], input[j]);
				k++;
			}	
		}
	}
    return 0;
}