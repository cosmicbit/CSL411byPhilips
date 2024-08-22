#include<stdio.h>
#include<string.h>
void findClosure(char epsilon_closure[], int state, int epsilon_trans[][2], int nEpsilonTrans){
	int i;
	for(i=0; i<nEpsilonTrans; i++){
		if(epsilon_trans[i][0]==state){
			char c[5];
			strcat(epsilon_closure,"q");
			sprintf(c, "%d", epsilon_trans[i][1]);
			strcat(epsilon_closure, c);
			strcat(epsilon_closure," ");
			findClosure(epsilon_closure, epsilon_trans[i][1], epsilon_trans, nEpsilonTrans);
		}
	}
}
int main(){
	int i, s, from, to;
	char input[20],c[5],line[100];
	FILE *fptr=fopen("input.dat", "r");
	printf("Enter the no. of states: ");
	scanf("%d",&s);
	int states[s];
	int epsilon_trans[20][2];
	char epsilon_closure[20][20];

	printf("Enter States:\n");
	for(i=0;i<s;i++){
		printf("q");
		scanf("%d",&states[i]);
		strcpy(epsilon_closure[states[i]],"");
		strcat(epsilon_closure[states[i]],"q");
		sprintf(c,"%d",states[i]);
		strcat(epsilon_closure[states[i]],c);
		strcat(epsilon_closure[states[i]]," ");
	}

	printf("\n Epsilon Transitions\n");
	i=0;
	while(!feof(fptr)){
		fgets(line,sizeof(line),fptr);
		if(line[2] == 'e'){
			epsilon_trans[i][0]=line[0] - '0';
			epsilon_trans[i++][1]=line[4] - '0';
			printf("%d e %d\n",epsilon_trans[i-1][0],epsilon_trans[i-1][1]);
		}
		
	}

	int nEpsilonTrans=i;
	printf("%d\n",nEpsilonTrans);
	for(i=0;i<s;i++){
		findClosure(epsilon_closure[states[i]], states[i], epsilon_trans, nEpsilonTrans);
		printf("Epsilon closure of q%d = { %s}\n",states[i], epsilon_closure[i]);
	}
	
	return 0;
}
