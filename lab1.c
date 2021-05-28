#include<stdio.h>
#include"rr.h"

int maxRunTime(Process *pArr, int n);

int main() {

  // read input
  int inArr[100];
  int i = 0;
  do {
    scanf("%d", &inArr[i]);
    i++;
  } while(inArr[i-1] != NULL);

  // Create array of processes
  Process pArr[inArr[0]]; 
  int inSize = sizeof inArr / sizeof inArr[0];
  int SA = inArr[1];
  int startInd;
  
  switch (SA) {
    case 1:
      startInd = 2;
      break;

    case 2:
      startInd = 3;
      break;
  }

  // initialize values for each process
  int pInd = 0;
  int idCount = 1;
  for (i = startInd; i < inSize ; i += 4) {
    
    if (inArr[i] == 0) {
      break;
    }
    pArr[pInd].R1 = inArr[i]; pArr[pInd].B1 = inArr[i+1]; 
    pArr[pInd].R2 = inArr[i+2]; pArr[pInd].B2 = inArr[i+3]; 
    pArr[pInd].T = 0;
    pArr[pInd].phase = 1; pArr[pInd].state = 2; pArr[pInd].id = idCount++;
    pArr[pInd].r1 = 0; pArr[pInd].b1 = 0; pArr[pInd].r2 = 0; pArr[pInd].b2 = 0;
    pArr[pInd].next = NULL;
    pInd++;
  }

  // execute roundRobin with proper q
  switch (SA) {
    case 1:
      // FIFO can be simulated as a round robin with a
      // q that is greater than the maximum required running time
      roundRobin(pArr, inArr[0], maxRunTime(pArr, inArr[0])+1);
      break;
    
    case 2:
      roundRobin(pArr, inArr[0], inArr[2]);
      break;
  }  

  return 0;
}

/*
  takes pointer to array of processes and the length of the array
  returns maximum needed runtime of all the processes
*/

int maxRunTime(Process *pArr, int n) {
	int i, max = 0;
	for (i = 0; i < n; i++) {
		Process *p = pArr+i;
		if (p->R1 > max) {
			max = p->R1;
		}
		if (p->R2 > max) {
			max = p->R2;
		}
	}
	return max;
}
