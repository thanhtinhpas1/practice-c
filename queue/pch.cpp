// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

queue* create_queue() {
	queue* queue_ptr = (queue*)malloc(sizeof(queue));
	check_memory(queue_ptr);
	
	queue_ptr->insert = 0;
	queue_ptr->pop = 0;
	queue_ptr->capacity = kQueueCapacity;

	return queue_ptr;
}

void enqueue(queue *q, const int value) {
	if (full(q)) {
		printf("Cannot enqueue another item");
		exit(EXIT_FAILURE);
	}

	q->data[q->insert] = value;
	q->insert = (q->insert + 1) % kQueuePositions;
}

const int dequeue(queue *q) {
	if (empty(q)) {
		printf("Queue is empty. Cannot dequeue");
		exit(EXIT_FAILURE);
	}

	int value = q->data[q->pop];
	q->data[q->pop] = 0;
	q->pop = (q->pop + 1) % kQueuePositions;
}

void print_debug(queue *q) {
	printf("Queue contents (old to new): ");

	for (int i = q->pop; i != q->insert; i = (i + 1) % kQueuePositions) {
		printf("%d, ", q->data[i]);
	}

	printf("\n");
}

bool empty(queue *q) {
	return q->pop == q->insert;
}

bool full(queue *q) {
	return q->pop == (q->insert + 1) % kQueuePositions;;
}

void check_memory(queue *ptr) {
	if (ptr == 0) {
		printf("Unable to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
}