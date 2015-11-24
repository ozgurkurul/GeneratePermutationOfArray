#include<stdio.h>
#include<stdlib.h>

//To generate all possible permutation of an array
typedef struct permutation{
	int data[9];
	int state;
}PERMUTATION;

long int lenghtOfPerm = -1;
PERMUTATION *allPermutation = NULL;

long int factorial(int n){
	long int resultOfFactorial = 1;
	int i;
	for(i=n; i>0; i--){
		resultOfFactorial *= i;
	}
	return resultOfFactorial;
}

void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void findAllPermutation(int data[], int s, int f){
 	if(s == f){
 		lenghtOfPerm++;
 		int i;
 		for(i=0; i<9; i++){
 			allPermutation[lenghtOfPerm].data[i] = data[i];
 		}

    }else{
    	int i;
		for(i = s; i <= f; i++){
            swap(&data[s], &data[i]);
            findAllPermutation(data, (s + 1), f);
            swap(&data[s], &data[i]);
        }
    }
}
	
int main(){
	FILE *file;
	long int numberOfPermutation = factorial(9);
	int data[9] = {1,2,3,4,5,6,7,8,9};
	int summing1 = 0;
	int summing2 = 0;
	int summing3 = 0;
	int totalAccept = 0;

	allPermutation = (PERMUTATION*)malloc(sizeof(PERMUTATION)*numberOfPermutation);
	findAllPermutation(data, 0, 8);
	int i;
	for(i=0; i<numberOfPermutation; i++){
		summing1 = allPermutation[i].data[0] + allPermutation[i].data[1] + allPermutation[i].data[2] + allPermutation[i].data[3] + allPermutation[i].data[4]; //a+b+c+d+e
		summing2 = allPermutation[i].data[3] + allPermutation[i].data[4] + allPermutation[i].data[5] + allPermutation[i].data[6] + allPermutation[i].data[7]; //d+e+f+g+h
		summing3 = allPermutation[i].data[0] + allPermutation[i].data[1] + allPermutation[i].data[6] + allPermutation[i].data[7] + allPermutation[i].data[8]; //a+b+g+h+k
		if((summing1 == summing2) && (summing1 == summing3)){ // a+b+c+d+e = a+b+g+h+k = d+e+f+g+h
			allPermutation[i].state = 1;
		}else{
			allPermutation[i].state = 0;
		}
	}
	
	file = fopen("file.txt", "w");
	if(file == NULL){
    	puts("Dosya acilamiyor...");
    	exit(1);
    }

	fprintf(file,"a b c d e f g h k\n"); //printf("a b c d e f g h k\n");
	for(i=0; i<numberOfPermutation; i++){
		if(allPermutation[i].state == 1){
			//printf("%d %d %d %d %d %d %d %d %d -> %d", allPermutation[i].data[0], allPermutation[i].data[1], allPermutation[i].data[2], allPermutation[i].data[3], allPermutation[i].data[4], allPermutation[i].data[5], allPermutation[i].data[6], allPermutation[i].data[7], allPermutation[i].data[8], i);
			fprintf(file,"%d %d %d %d %d %d %d %d %d\n", allPermutation[i].data[0], allPermutation[i].data[1], allPermutation[i].data[2], allPermutation[i].data[3], allPermutation[i].data[4], allPermutation[i].data[5], allPermutation[i].data[6], allPermutation[i].data[7], allPermutation[i].data[8]);
			totalAccept++;
		}
	}
	
	printf("Total element of Acceptable State: %d\nTo see all states, look at the file.txt",totalAccept);
	
	fclose(file);
	return 0;
}
