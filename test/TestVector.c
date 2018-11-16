#include "Vector.h"
#include "unity.h"

static vector *v;

static void 
test_vector_init(void)
{
	v = vector_init (sizeof (int), 0, NULL);
	TEST_ASSERT_MESSAGE (v != NULL, "failed vector initialization");
}

static void 
test_vector_destroy(void)
{
	vector_destroy (v);
	TEST_ASSERT_MESSAGE (0 == 0, "vector destroy should pass");
}

int 
main(void)
{
	UNITY_BEGIN ();
	RUN_TEST (test_vector_init);
	RUN_TEST (test_vector_destroy);
	return UNITY_END ();
}
