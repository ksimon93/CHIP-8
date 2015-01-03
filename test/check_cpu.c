#include "../src/cpu.h"
#include "../src/mem.h"
#include "../src/gfx.h"
#include "minunit.h"

void test_setup() {
	init_cpu();
}

void test_teardown() {}

MU_TEST(test_00E0) {
	for (int i = 0; i < NUM_PIXELS; i++) {
		gfx[i] = i;
	}
	mem[PC_START_ADDRESS] = 00E0;
	cpu_cycle();
	for (int i = 0; i < NUM_PIXELS; i++) {
		mu_assert_int_eq(0, gfx[i]);
	}
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	printf("Testing opcode 00E0:\n");
	MU_RUN_TEST(test_00E0);
	printf("\nTest successful! Initializing next test.");

}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}