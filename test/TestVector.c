#include "Vector.h"
#include "unity.h"

void 
test_vector_init(void)
{
	TEST_ASSERT_MESSAGE (0 == 1, "should fail");
}

int 
main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_vector_init);
	return UNITY_END();
}
