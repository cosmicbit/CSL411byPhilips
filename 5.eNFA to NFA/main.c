#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STATes 100
#define MAX_ALPHABET 26
#define MAX_NEXT_STATes 10

int ENFATransitions[MAX_STATes][MAX_ALPHABET][MAX_NEXT_STATes], nFinalState, finalStates[20], nENFATransitions=0;
int epsilon_trans[20][2];
int newStates[MAX_STATes][MAX_STATes];
int NFATransitions[MAX_STATes][MAX_ALPHABET][1];

void initializeENFATransitions() {
    memset(ENFATransitions, -1, sizeof(ENFATransitions));  // No transition initially
}
void initializeNFATransitions(){
	memset(NFATransitions, -1, sizeof(NFATransitions));
}
void initializeNewStates(){
	memset(newStates, -1, sizeof(newStates));  // No transition initially
}
void addENFATransition(int state, int symbol, int nextState) {
    int j;
    for (j = 0; j < MAX_NEXT_STATes; j++) {
        if (ENFATransitions[state][symbol][j] == -1) {
            ENFATransitions[state][symbol][j] = nextState;
            break;
        }
    }
    if (j == MAX_NEXT_STATes) {
        printf("Error: Too many transitions for state %d on input %d\n", state, symbol);
    }
}

void printENFATransitions(int s, int n, int states[], char input[]){
	for (int i = 0; i < s; i++){  
        for (int j = 0; j < n; j++){
            for (int k = 0; k < MAX_NEXT_STATes; k++)
                if(ENFATransitions[states[i]][input[j]-97][k] != -1){
					printf("%d\t",states[i]);
            		printf("%c\t",input[j]);
                    printf("%d\n", ENFATransitions[states[i]][input[j]-97][k]);
				}
                else
                    break;
        }
    }
}
int* getENFATransition(int s, int n, int state, char input){
	return ENFATransitions[state][input-97];
}

void findClosure(int newStates[], int state, int epsilon_trans[][2], int nEpsilonTrans){
	int i,j;
	for(i=0; i<nEpsilonTrans; i++){
		if(epsilon_trans[i][0]==state){
			j=0;
			while(newStates[j] != -1)
				j++;
			newStates[j]=epsilon_trans[i][1];
			findClosure(newStates, epsilon_trans[i][1], epsilon_trans, nEpsilonTrans);
		}
	}
}
void printETransitions(int nEpsilonTrans){
	printf("\nEpsilon Transitions\n");
	for(int i=0;i<nEpsilonTrans; i++)
		printf("%d e %d\n",epsilon_trans[i][0],epsilon_trans[i][1]);
}

int main(){
    int s, n, i, j, k, startState, nNewStates;
	initializeNewStates();
	initializeENFATransitions();
	initializeNFATransitions();

	printf("Enter the no. of states: ");
	scanf("%d",&s);
	nNewStates=s;

	int states[s];
	printf("Enter the states: ");
	for(i=0;i<s;i++){
		scanf("%d",&states[i]);
		newStates[states[i]][0] = states[i];
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
	scanf("%d",&nENFATransitions);
	printf("Enter Transitions:\n");
	
	int cs, ns;
	char a;
	j=0;
	for(i=0; i<nENFATransitions; i++){
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
		findClosure(newStates[states[i]], states[i], epsilon_trans, nEpsilonTrans);
		printf("Epsilon closure of q%d = { ",states[i]);
		j=0;
		while(newStates[states[i]][j] != -1){
			printf("q%d ",newStates[states[i]][j]);
			j++;
		}
		printf("}\n");
	}
    int* currentENFATransition;
	for(i=0; i<s; i++){
		printf("state=%d\n", states[i]);
		k=0;
		while(newStates[states[i]][k] != -1){
			printf("Closure[%d]=%d\n", k, newStates[states[i]][k]);
			for(j=0; j<n; j++){
				printf("input=%c\n", input[j]);
				currentENFATransition = ENFATransitions[ newStates[ states[i] ][ k ] ][ input[j]-97 ];
				for (int l = 0; l < MAX_NEXT_STATes; l++)
					if(currentENFATransition[l] != -1){
						printf("%d\t",newStates[states[i]][k]);
						printf("%c\t",input[j]);
						printf("%d\n", currentENFATransition[l]);
					}
					else
						break;
			}	
			k++;
		}	
	}
    return 0;
}