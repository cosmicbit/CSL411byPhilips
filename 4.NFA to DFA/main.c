#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_ALPHABET 26
#define MAX_NEXT_STATES 10

int NFATransitions[MAX_STATES][MAX_ALPHABET][MAX_NEXT_STATES], nNewStates=0, nFinalState, finalStates[20], nNFATransitions=0, nDFATransitions=0;

void initializeNFATransitions() {
    for (int i = 0; i < MAX_STATES; i++)
        for (int j = 0; j < MAX_ALPHABET; j++)
            for (int k = 0; k < MAX_NEXT_STATES; k++)
                NFATransitions[i][j][k] = -1;  // No transition initially
}

void addNFATransition(int state, int symbol, int nextState) {
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

//structure for new DFA States
struct DFAStates{
	int num;
	int s[10];
	int f;
}newStates[20];

//structure for DFA Transitions 
struct transitions2{
	int nFrom;
	int from[100];
	char with;
	int nTo;
	int to[100];
}DFA_Transition[20];

// display DFA Transitions
void printDFA(){
	printf("\n\n-----------Equivalent DFA-------------\n\n");
	printf("no. of DFA Transitions= %d\n",nDFATransitions);
	for(int i=0;i<nDFATransitions; i++){
		printf("{");
		for(int j=0; j<DFA_Transition[i].nFrom; j++){
			printf("q%d,",DFA_Transition[i].from[j]);
		}
		printf("}\t%c\t{", DFA_Transition[i].with);
		for(int j=0; j<DFA_Transition[i].nTo; j++){
			printf("q%d,",DFA_Transition[i].to[j]);
		}
		printf("}\n");
	}
	
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
void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}
void mergeAndRemoveDuplicates(int arr1[], int size1, int arr2[], int size2, int result[], int *resultSize) {
    int i, j, k = 0;
    // Step 1: Copy all elements from arr1 to result
    for (i = 0; i < size1; i++) {
        result[k++] = arr1[i];
    }
    // Step 2: Copy all elements from arr2 to result
    for (i = 0; i < size2; i++) {
        result[k++] = arr2[i];
    }
    // Step 3: Remove duplicates
    int uniqueSize = 0;
    for (i = 0; i < k; i++) {
        int isDuplicate = 0;
        for (j = 0; j < uniqueSize; j++) {
            if (result[i] == result[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            result[uniqueSize++] = result[i];
        }
    }
    *resultSize = uniqueSize;
}


/*	fuction to check whether the current 
	state is already in DFA Transitions		*/
bool isInDFA(int nCurrentState, int currentState[], int nDFATransitions, char input){
	int count=0;
	for(int i=0;i<nDFATransitions; i++){
		if(arraysHaveSameElements(DFA_Transition[i].from, currentState, DFA_Transition[i].nFrom, nCurrentState) && DFA_Transition[i].with==input){
			return true;
		}
	}
	return false;
}

/*	function to find and return the next state of 
	current state and input from NFA Transitions	*/
int findInNFA(int state, int symbol, int nextStates[]){
		int count=0;
		for (int j = 0; j < MAX_NEXT_STATES; j++)
			if (NFATransitions[state][symbol][j] != -1)
				nextStates[count++]=NFATransitions[state][symbol][j];
		return count;
}
bool isFinalState(int state[], int size){
	for(int i=0; i<nFinalState; i++)
		for(int j=0; j<size; j++)
			if(finalStates[i]==state[j])
				return true;
	return false;
}
void addNewState(int state[], int size){
	newStates[nNewStates].num = size;
	copyArray(state,newStates[nNewStates].s,size);
	if(isFinalState(state,size))
		newStates[nNewStates].f=1;
	else
		newStates[nNewStates].f=0;
	nNewStates++;
}

//function to find the next state of the current state and input
void findNextStates(int nCurrentState, int currentState[], int n, char input[], int *nDFATransitions){
	int i,j,l=*nDFATransitions;
	int result[100],nextStates[100];
	int resultSize;
	int count=0;
	for(i=0; i<n; i++){
		if(isInDFA(nCurrentState, currentState, *nDFATransitions, input[i])){
			continue;
		}
		resultSize=0;
		for(j=0; j<nCurrentState; j++){
			count=0;
			count=findInNFA(currentState[j], input[i]-97, nextStates);
			if(count!=0)
				mergeAndRemoveDuplicates(result, resultSize, nextStates, count, result, &resultSize);
		}
		if(resultSize!=0){
			DFA_Transition[l].nFrom = nCurrentState;
			copyArray(currentState, DFA_Transition[l].from, nCurrentState);
			DFA_Transition[l].with = input[i];
			DFA_Transition[l].nTo = resultSize;
			copyArray(result, DFA_Transition[l].to, DFA_Transition[l].nTo);
			l++;
		}
	}
	if(l != *nDFATransitions){
		addNewState(DFA_Transition[l-1].to, DFA_Transition[l-1].nTo);
		for(i=*nDFATransitions; i<l; i++){
			findNextStates(DFA_Transition[i].nTo, DFA_Transition[i].to, n, input, &l);
		}
	}
	*nDFATransitions = l;
}

int main(){
	int s, n, i, j, startState;

	printf("Enter the no. of states: ");
	scanf("%d",&s);

	int states[s];
	printf("Enter the states: ");
	for(i=0;i<s;i++)
		scanf("%d",&states[i]);

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
	initializeNFATransitions();
	int cs, ns;
	char a;
	for(i=0; i<nNFATransitions; i++){
		scanf("%d %c %d", &cs, &a, &ns);
		addNFATransition(cs, a-97, ns);
	}
	printf("\n\n");

	int temp[]={startState};
	findNextStates(1,temp, n, input, &nDFATransitions); // Starting with start state
	printDFA();
	
	printf("\nStates: \n");
	for(i=0; i<nNewStates; i++){
		printf("{");
		for(j=0; j<newStates[i].num; j++){
			printf("q%d,",newStates[i].s[j]);
		}
		printf("}\t");
	}
	printf("\n\n");
	printf("Inputs: \n");
	for(i=0; i<n; i++){
		printf("%c\t",input[i]);
	}
	printf("\n\nStart State: {%d}", startState);
	printf("\n\nFinal States:\n");
	for(i=0; i<nNewStates; i++){
		if(newStates[i].f==1){
			printf("{");
			for(j=0; j<newStates[i].num; j++){
				printf("q%d,",newStates[i].s[j]);
			}
			printf("}\t");
		}
	}
	printf("\n\n");
	return 0;
}
