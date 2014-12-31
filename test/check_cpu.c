#include "../src/cpu.h"
#include "../src/mem.h"
#include "minunit.h"

void test_setup() {
	init_cpu();
}

void test_teardown() {}

MU_TEST(test_fetch_init) {
	// check if initialization is correct
	mu_assert_int_eq(PC_START_ADDRESS, pc);
	//fetch();
	mu_assert_int_eq(PC_START_ADDRESS+2, pc);
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_fetch_init);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}