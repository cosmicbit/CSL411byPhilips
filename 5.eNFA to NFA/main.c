#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_STATes 100
#define MAX_ALPHABET 26
#define MAX_NEXT_STATes 10

int ENFATransitions[MAX_STATes][MAX_ALPHABET][MAX_NEXT_STATes], nFinalState, finalStates[20], nENFATransitions=0;
int epsilon_trans[20][2];
int newStates[MAX_STATes][MAX_STATes];
int NFATransitions[MAX_STATes][MAX_ALPHABET], nNFATransitions=0;

void initializeENFATransitions() {
    memset(ENFATransitions, -1, sizeof(ENFATransitions));  // No transition initially
}
void initializeNFATransitions(){
	memset(NFATransitions, -1, sizeof(NFATransitions));    // No Transition initially
}
void initializeNewStates(){
	memset(newStates, -1, sizeof(newStates));  // No states initially
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

void findClosure(int newStates[], int state, int epsilon_trans[][2], int nEpsilonTrans){
	int i,j;
	for(i=0; i<nEpsilonTrans; i++){
		if(epsilon_trans[i][0]==state){
			j=0;
			while(newStates[j] != -1){
				if(newStates[j]==epsilon_trans[i][1]){
					break;
				}
				j++;
			}
			newStates[j]=epsilon_trans[i][1];
			findClosure(newStates, epsilon_trans[i][1], epsilon_trans, nEpsilonTrans);
		}
	}
}


bool isElementInArray(int arr[], int size, int element) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == element) {
            return true;  // Element found
        }
    }
    return false;  // Element not found
}


int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

bool arraysHaveSameElements(int arr1[], int arr2[], int size, int size1) {
    // Sort both arrays
	if(size!=size1)
		return false;
    qsort(arr1, size, sizeof(int), compare);
    qsort(arr2, size, sizeof(int), compare);
    
    // Compare sorted arrays
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    
    return true;
}

int main(){
    int s, n, i, j, k, l, t, startState, nNewStates;
	int temp[MAX_STATes];
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
	
	// finding closure of all states
	for(i=0; i<s; i++){
		findClosure(newStates[states[i]], states[i], epsilon_trans, nEpsilonTrans);
	}
    int* currentENFATransition;
	int nextState[MAX_STATes], m;
	for(i=0; i<s; i++){
		for(j=0; j<n; j++){
			if(input[j]=='e') continue;
			memset(temp, -1, sizeof(temp));
			t=0; // index for temp
			k=0; // index for closure elements
			while(newStates[states[i]][k] != -1){
				currentENFATransition = ENFATransitions[ newStates[ states[i] ][ k ] ][ input[j]-97 ];
				for (l = 0; l < MAX_NEXT_STATes; l++){
					if(currentENFATransition[l] != -1){
						if(!isElementInArray(temp, t, currentENFATransition[l])){
							temp[t++] = currentENFATransition[l];
						}	
					}
					else break;
				}
				k++;
			}
			m=0;
			for(k=0; k<t; k++){
				l=0;
				while(newStates[temp[k]][l]!=-1 && !isElementInArray(nextState, m, newStates[temp[k]][l])){
					nextState[m++]=newStates[temp[k]][l];
					l++;
				}
			}
			for(k=0; k<nNewStates; k++){
				t=0;
				while(newStates[states[k]][t]!=-1) t++;
				if(arraysHaveSameElements(newStates[states[k]], nextState, t, l)){
					NFATransitions[states[i]][input[j]-97]=states[k];
					nNFATransitions++;
				}
			}
		}	
	}
	printf("\nEquivalent NFA without epsilon\n");
	printf("------------------------------\n");
	printf("Start State: { ");
	k=0;
	while(newStates[startState][k]!=-1){
		printf("q%d, ", newStates[startState][k]);
		k++;
	}
	printf("}\nAlphabets: ");
	for(i=0; i<n; i++)
		printf("%c ",input[i]);
	printf("\nStates: ");
	for(i=0; i<nNewStates; i++){
		printf("{");
		k=0;
		while(newStates[states[i]][k]!=-1){
			printf("q%d, ", newStates[states[i]][k]);
			k++;
		}
		printf("}   ");
	}
	printf("\nTransitions are...:\n");
	for(i=0; i<nNewStates; i++){
		for(j=0; j<n; j++){
			if(input[j]=='e') continue;
			if(newStates[NFATransitions[states[i]][input[j]-97]][0]==-1) continue;
			k=0;
			printf("{ ");
			while(newStates[states[i]][k] != -1){
				printf("q%d, ",newStates[states[i]][k]);
				k++;
			}
			printf("}    %c    { ",input[j]);
			k=0;
			while(newStates[NFATransitions[states[i]][input[j]-97]][k] != -1){
				printf("q%d, ",newStates[NFATransitions[states[i]][input[j]-97]][k]);
				k++;
			}
			printf("}\n");
		}
	}
	printf("\n\nFinal States:   ");
	for(i=0; i< nNewStates; i++){
		k=0;
		while(newStates[states[i]][k] != -1){
			if(isElementInArray(finalStates, nFinalState, newStates[states[i]][k])){
				k=0;
				printf("{ ");
				while(newStates[states[i]][k] != -1){
					printf("q%d, ",newStates[states[i]][k]);
					k++;
				}
				printf("}   ");
				break;
			}
			k++;
		}
	}
	printf("\n");
    return 0;
}