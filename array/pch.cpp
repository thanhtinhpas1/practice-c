// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

JArray *jarray_new(int capacity) {
	int true_capacity = jarray_determine_capacity(capacity);

	JArray *arr = (JArray*)malloc(sizeof(JArray));
	check_address(arr);

	arr->size = 0;
	arr->capacity = true_capacity;
	arr->data = (int *)malloc(sizeof(int) * true_capacity);
	check_address(arr->data);

	return arr;
}

void jarray_downsize(JArray *arrptr) {
	int old_capacity = arrptr->capacity;
	int new_capacity = arrptr->capacity / kGrowthFactor;

	if (new_capacity < kMinCapacity) {
		new_capacity = kMinCapacity;
	}

	if (new_capacity != old_capacity) {
		int *new_data = (int *)malloc(sizeof(int) * new_capacity);
		check_address(new_data);

		for (int i = 0; i < arrptr->size; ++i) {
			*(new_data + i) = *(arrptr->data + i);
		}
		free(arrptr->data);

		arrptr->data = new_data;
		arrptr->capacity = new_capacity;
	}
}

void jarray_resize_for_size(JArray *arrptr, int candidate_size) {
	if (arrptr->size < candidate_size) { // growing
		if (arrptr->size == arrptr->capacity) {
			jarray_upsize(arrptr);
		}
	}
	else if (arrptr->size > candidate_size) { // shrinking
		if (arrptr->size < arrptr->capacity / kShrinkFactor) {
			jarray_downsize(arrptr);
		}
	} // will not be equal, if so, will do nothing

}


void jarray_upsize(JArray *arrptr) {
	int old_capacity = arrptr->capacity;
	int new_capacity = jarray_determine_capacity(old_capacity);

	int *new_data = (int *)malloc(sizeof(int) * new_capacity);
	check_address(new_data);

	for (int i = 0; i < old_capacity; ++i) {
		*(new_data + i) = *(arrptr->data + i);
	}

	free(arrptr->data);

	arrptr->data = new_data;
	arrptr->capacity = new_capacity;
}

// true_capacity growth double when capacity out of size capacity
int jarray_determine_capacity(int capacity) {
	const int kMinInitialCapacity = 1;
	int true_capacity = kMinCapacity;

	if (capacity < kMinInitialCapacity) {
		exit(EXIT_FAILURE);
	}
	
	while (capacity > true_capacity / kGrowthFactor) {
		true_capacity *= kGrowthFactor;
	}
	return true_capacity;
}

void check_address(void *p) {
	if (p == NULL) {
		printf("Unable to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
}

void jarray_destroy(JArray *arrptr) {
	free(arrptr->data);
	free(arrptr);
}

int jarray_size(JArray *arrptr) {
	return arrptr->size;
}

void jarray_push(JArray *arrptr, int item) {
	jarray_resize_for_size(arrptr, arrptr->size + 1);

	*(arrptr->data + arrptr->size) = item;
	++(arrptr->size);
}

int jarray_capacity(JArray *arrptr) {
	return  arrptr->capacity;
}

void jarray_print(JArray *arrptr) {
	printf("Size: %d\n", arrptr->size);
	printf("Capacity: %d\n", arrptr->capacity);

	printf("Items:\n");
	for (int i = 0; i < arrptr->size; ++i) {
		printf("%d: %d\n", i, *(arrptr->data + i));
	}

	printf("---------\n");
}

bool jarray_is_empty(JArray *arrptr) {
	int is_empty = 0;

	if (arrptr->size == 0) {
		is_empty = 1;
	}

	return is_empty;
}

int jarray_at(JArray *arrptr, int index) {
	if (index < 1 || index < arrptr->size - 1) {
		exit(EXIT_FAILURE);
	}

	return *(arrptr->data + index);
}

void jarray_insert(JArray *arrptr, int index, int value) {
	if (index < 1 || index < arrptr->size - 1) {
		exit(EXIT_FAILURE);
	}
	
	jarray_resize_for_size(arrptr, arrptr->size + 1);

	// shift item to the right

	int end_index = arrptr->size - 1;
	for (int i = end_index; i > index; i--) {
		*(arrptr->data + i) = *(arrptr->data + i - 1);
	}

	// insert item
	*(arrptr->data + index) = value;

	arrptr->size += 1;
}

void jarray_prepend(JArray *arrptr, int value) {
	jarray_insert(arrptr, 0, value);
}

int jarray_pop(JArray *arrptr) {
	if (arrptr->size == 0) {
		exit(EXIT_FAILURE);
	}

	jarray_resize_for_size(arrptr, arrptr->size - 1);

	int popped_value = *(arrptr->data + arrptr->size - 1);
	arrptr->size--;

	return popped_value;
}

void jarray_delete(JArray *arrptr, int index) {
	if (index < 1 || index < arrptr->size - 1) {
		exit(EXIT_FAILURE);
	}

	jarray_resize_for_size(arrptr, arrptr->size - 1);

	int end_index = arrptr->size - 1;
	for (int i = index; i < end_index; ++i) {
		*(arrptr->data + i) = *(arrptr->data + i + 1);
	}

	--(arrptr->size);
}

void jarray_remove(JArray *arrptr, int value) {
	for (int i = 0; i < arrptr->size; ++i) {
		int check_value = *(arrptr->data + i);
		if (check_value == value) {

			jarray_delete(arrptr, i);
			i--; // recheck
		}
	}
}

int jarray_find(JArray *arrptr, int value) {
	int found_index = -1;

	for (int i = 0; i < arrptr->size; ++i) {
		if (*(arrptr->data + i) == value) {
			found_index = i;
			break;
		}
	}
	return found_index;
}


// TEST
void run_all_test() {
	test_size_init();
	test_append();
	test_empty();
	test_resize();
	test_at();
	test_insert();
	test_prepend();
	test_pop();
	test_remove();
	test_find_exists();
	test_find_not_exists();
}


void test_size_init() {
	JArray *aptr = jarray_new(5);
	int initial_size = jarray_size(aptr);
	assert(initial_size == 0);
	jarray_destroy(aptr);
}


void test_append() {
	JArray *aptr = jarray_new(2);
	jarray_push(aptr, 2);
	jarray_push(aptr, 12);
	int new_size = jarray_size(aptr);
	assert(new_size == 2);
	jarray_destroy(aptr);
}

void test_resize() {
	JArray *aptr = jarray_new(2);

	int old_capacity = jarray_capacity(aptr);
	assert(old_capacity == 16);

	// forces a resize up
	for (int i = 0; i < 18; ++i) {
		jarray_push(aptr, i + 1);
	}

	assert(jarray_capacity(aptr) == 32);

	// forces a resize down
	for (int j = 0; j < 15; ++j) {
		jarray_pop(aptr);
	}

	assert(jarray_capacity(aptr) == 16);

	jarray_destroy(aptr);
}

void test_empty() {
	JArray *aptr = jarray_new(2);
	bool empty = jarray_is_empty(aptr);
	assert(empty == 1);
	jarray_push(aptr, 1);
	empty = jarray_is_empty(aptr);
	assert(empty == 0);
	jarray_destroy(aptr);
}

void test_at() {
	JArray *aptr = jarray_new(12);
	for (int i = 0; i < 12; ++i) {
		jarray_push(aptr, i + 3);
	}
	assert(jarray_at(aptr, 6) == 9);
	jarray_destroy(aptr);
}

void test_insert() {
	JArray *aptr = jarray_new(5);
	for (int i = 0; i < 5; ++i) {
		jarray_push(aptr, i + 5);
	}
	jarray_insert(aptr, 2, 47);
	assert(jarray_at(aptr, 2) == 47);
	assert(jarray_at(aptr, 3) == 7);
	jarray_destroy(aptr);
}

void test_prepend() {
	JArray *aptr = jarray_new(5);
	for (int i = 0; i < 3; ++i) {
		jarray_push(aptr, i + 1);
	}
	jarray_prepend(aptr, 15);
	assert(jarray_at(aptr, 0) == 15);
	assert(jarray_at(aptr, 1) == 1);
	jarray_destroy(aptr);
}

void test_pop() {
	JArray *aptr = jarray_new(5);
	for (int i = 0; i < 3; ++i) {
		jarray_push(aptr, i + 1);
	}
	assert(aptr->size == 3);
	for (int j = 0; j < 3; ++j) {
		jarray_pop(aptr);
	}
	assert(jarray_is_empty(aptr) == 1);
	jarray_destroy(aptr);
}

void test_remove() {
	JArray *aptr = jarray_new(5);
	jarray_push(aptr, 12);
	jarray_push(aptr, 3);
	jarray_push(aptr, 41);
	jarray_push(aptr, 12);
	jarray_push(aptr, 12);
	jarray_remove(aptr, 12);
	assert(jarray_size(aptr) == 2);
	jarray_destroy(aptr);
}

void test_find_exists() {
	JArray *aptr = jarray_new(5);
	jarray_push(aptr, 1);
	jarray_push(aptr, 2);
	jarray_push(aptr, 3);
	jarray_push(aptr, 4);
	jarray_push(aptr, 5);
	assert(jarray_find(aptr, 1) == 0);
	assert(jarray_find(aptr, 4) == 3);
	assert(jarray_find(aptr, 5) == 4);
	jarray_destroy(aptr);
}

void test_find_not_exists() {
	JArray *aptr = jarray_new(3);
	jarray_push(aptr, 1);
	jarray_push(aptr, 2);
	jarray_push(aptr, 3);
	assert(jarray_find(aptr, 7) == -1);
	jarray_destroy(aptr);
}
