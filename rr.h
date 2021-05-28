#include<stdio.h>
#include"queue.h"

int areAllDone(int n, Process *pArr);

int roundRobin(Process *pFirst, int n, int q) {
 
  int i;
  // add all to ready queue in numerical order
  for (i = 0; i < n; i++) {
    addLast(pFirst+i);
  }

//  Print header
  printf("%-7s  ", "Cycle");
  for (i = 0; i < n; i++) {

    printf("P%d %-16s", i+1, "State");

  }
  printf("\n"); 

// initialize counters
  int qt = 0;
  int cycles = 0;
  int jobDone = 0;
  Process *p;

// phase: 1 = R1, 2 = B1, 3 = R2, 4 = B2, 5 = T
// state: 1 = running, 2 = ready, 3 = blocking, 4 = terminating

  // while all processes have not finished
  while (areAllDone(n, pFirst) == 0) {
    qt++; cycles++;
    // Mark first process in ready queue as Running
    Process *first = getFirst();
    if (first != NULL) {
      first->state = 1;
    }    

    printf("%-7d  ", cycles);
    // loop through each process
    for (i = 0; i < n; i++) {
      p = pFirst+i;
      switch (p->state) {
        // Running State
        case 1:
          switch (p->phase) {
            // R1
            case 1:
              p->r1++;
              p->state = 2;
              printf("Run (%-2d of %-2d)     ", p->r1, p->R1);
              // finished run
              if (p->r1 == p->R1) {
                // remove frome ready queue, reset q counter
                // change phase and state
                removeFirst();
                p->phase = 2;
                p->state = 3;
                qt = 0;
                jobDone = 1;
              }
              // q counter reached q value and run not finished
              if (qt == q && jobDone == 0) {
                qt = 0;
                if (p != NULL) {
                  // change state to ready,
                  // move process to back of queue
                  p->state = 2;
                  removeFirst();
                  addLast(p);
                }
              } 
              break;
            // R2
            case 3:
              p->r2++;
              p->state = 2;
              printf("Run (%-2d of %-2d)     ", p->r2, p->R2);
              // finished block
              if (p->r2 == p->R2) {
                // remove from ready queue, reset q counter
                // change phase and state
                removeFirst();
                p->phase = 4;
                p->state = 3;
                qt = 0;
                jobDone = 1;
              }
              // q counter reached q value and run not finished
              if (qt == q && jobDone == 0) {
                qt = 0;
                if (p != NULL) {
                  // change state to ready,
                  // move process to back of queue
                  p->state = 2;
                  removeFirst();
                  addLast(p);
                }
              }
              break;
            // Terminating
            case 5:
              printf("%-19s", "Terminate");
              p->state = 4;
              p->T = 1;
              qt = 0;
              removeFirst();
              break;             
          } // end run phase switch         

          // break running case
          break;
        // Ready State
        case 2:
          printf("%-19s", "Ready");
          // break ready case
          break;
        // Blocking State
        case 3:  
          switch (p->phase) {
            // B1
            case 2:                 
              p->b1++;
              printf("Blocked (%-2d of %-2d) ", p->b1, p->B1);
              // blocking done
              if (p->b1 == p->B1) {     
                // change phase and state
                // add to ready queue                  
                p->phase = 3;
                p->state = 2;
                addLast(p);
              }
              break;
            
            // B2
            case 4:                 
              p->b2++;
              printf("Blocked (%-2d of %-2d) ", p->b2, p->B2);
              // blocking done
              if (p->b2 == p->B2) { 
                // change phase and state
                // add to ready queue                              
                p->phase = 5;
                p->state = 2;
                addLast(p);
              }
              break;
          }
          // break blocking state
          break;

        // Terminating State
        default:
          printf("                   ");
          // break terminating state

      // end switch on state
      }
    // end for loop
    }
    // If no process was ready or ran during this cycle
    // reset q counter
    if (first == NULL) {
      qt = 0;
    }
    jobDone = 0;

    printf("\n");
  // end while loop
  }
// end roundRobin
}

// Return 1 if all processes terminated, 0 if not
int areAllDone(int n, Process *pArr) {
  int i = 0, count = 0;
  for (i = 0; i < n; i++) {
    Process *p = pArr+i;
    if (p->T == 1) {
      count++;
    }
  }
  if (count == n) {
    return 1;
  } else {
    return 0;
  }
}
