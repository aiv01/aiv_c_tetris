#include "aiv_unit_test.h"

TEST(dumb)
{
	ASSERT_THAT(1)
}

int main(int argc, char **argv)
{
	RUN_TEST(dumb);
	PRINT_TEST_RESULTS();
	return 0;
}
