#ifndef queue
#define queue
#include<stdio.h>

// Process struct
typedef struct Process {
    int id;
    // phase; phase counter
    int R1; int r1;
    int R2; int r2;
    int B1; int b1;
    int B2; int b2;
    int T;
    int phase;
    int state;

    struct Process *next;

  } Process;

// must keep track of first process
// for getFirst() and addLast()
Process *head = NULL;

// takes a process in the queue
// returns next process in queue
// was used to iterate through queue to make sure
// the queue was behaving as intended
Process *nextProcess(Process *p) {
  if (p->next == NULL) {
    return head;
  } else {
    return p->next;
  }
}

// takes a process
// adds it to the end of the queue
void addLast(Process *p) {
  if (head == NULL) {
    head = p;
  } else {
    Process *pi = head;
    while (pi->next != NULL) {
      pi = pi->next;
    }
    pi->next = p;
  }
}

// returns the first process in the queue
Process *getFirst() {
  return head;
}

// removes first process in queue
void removeFirst() {
  Process *temp = head;
  head = head->next;
  temp->next = NULL;
}

#endif
