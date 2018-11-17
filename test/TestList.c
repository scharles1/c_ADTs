#include "List.h"
#include "unity.h"

static void 
test_list_init (void)
{
	TEST_ASSERT_MESSAGE (0 == 1, "failed list initialization");
}

int 
main(void)
{
	UNITY_BEGIN ();
	RUN_TEST (test_list_init);
	return UNITY_END ();
}