#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef PCH_H
#define PCH_H

const int kQueueCapacity = 5;
const int kQueuePositions = kQueueCapacity + 1;

typedef struct JWQueueArrayImplementation {
	int data[kQueuePositions];// 1 is unusable position
	int insert;
	int pop;
	int capacity;
}queue;

// creates a new queue
queue *create_queue();

// adds value to queue
void enqueue(queue *q, const int value);

// returns value at front of queue, and removes from queue
const int dequeue(queue *q);

// returns true if queue is full
bool full(queue *q);

// prints the content of the queue for debugging purposes
void print_debug(queue *q);

bool empty(queue *q);

// checks to see if memory provided by malloc is valid and exists if not
void check_memory(queue *address);

#endif //PCH_H
