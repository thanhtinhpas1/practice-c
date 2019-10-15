#include "pch.h"
#include "test.h"

void run_all_tests() {
	test_exists();
	test_add_get();
	test_add_remove();
}

void test_exists() {
	hash_table* states = create_table(kTableSize);

	assert(exists(states, "Texas") == false);

	key_value tx = { _strdup("Texas"), _strdup("Austin") };
	add(states, "Texas", &tx);

	assert(exists(states, "Texas") == true);

	destroy_table(states);
}

void test_add_get() {
	hash_table* states = create_table(kTableSize);

	key_value la = { _strdup("Louisiana"), _strdup("Baton Rouge") };
	add(states, "Louisiana", &la);

	key_value me = { _strdup("Maine"), _strdup("Augusta") };
	add(states, "Maine", &me);

	char* capital1 = get(states, "Louisiana");
	assert(strcmp(capital1, "Baton Rouge") == 0);

	// add LA again, with new capital
	key_value la2 = { _strdup("Louisiana"),_strdup("New Orleans") };
	add(states, "Louisiana", &la2);

	// now capital should be Nawlins
	char* capital2 = get(states, "Louisiana");
	assert(strcmp(capital2, "New Orleans") == 0);

	destroy_table(states);
}

void test_add_remove() {
	hash_table* states = create_table(kTableSize);

	key_value ca = { _strdup("California"), _strdup("Sacramento") };
	add(states, "California", &ca);

	assert(exists(states, "California") == true);

	delete(states, "California");

	assert(exists(states, "California") == false);

	destroy_table(states);
}
