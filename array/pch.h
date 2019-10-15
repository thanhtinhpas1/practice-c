// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>  // for malloc

const int kMinCapacity = 16;
const int kGrowthFactor = 2;
const int kShrinkFactor = 4;

typedef struct JWImplementationArray {
	int size;
	int capacity;
	int *data;
}JArray;

// Creates a new JArray (vector in our case) with the initial capacity
JArray *jarray_new(int capacity);
void jarray_destroy(JArray *arrptr);

void check_address(void *p);

void jarray_resize_for_size(JArray *arrptr, int candidate_size);

int jarray_determine_capacity(int capacity);

void jarray_upsize(JArray *arrptr);

void jarray_downsize(JArray *arrptr);

int jarray_size(JArray *arrptr);

// Appends the given item to the end of array
void jarray_push(JArray *arrptr, int item);

int jarray_capacity(JArray *arrptr);

void jarray_print(JArray *arrptr);

bool jarray_is_empty(JArray *arrptr);

int jarray_at(JArray *arrptr, int index);

void jarray_insert(JArray *arrptr, int index, int value);

void jarray_prepend(JArray *arrptr, int value);

int jarray_pop(JArray *arrptr);

void jarray_delete(JArray *arrptr, int index);

void jarray_remove(JArray *arrptr, int value);

int jarray_find(JArray *arrptr, int value);

// test

void run_all_test();

void test_append();
void test_size_init();
void test_append_past_capacity();
void test_capacity();
void test_empty();
void test_resize();
void test_at();
void test_insert();
void test_prepend();
void test_pop();
void test_remove();
void test_find_exists();
void test_find_not_exists();

#endif //PCH_H
