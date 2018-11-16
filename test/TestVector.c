#include "Vector.h"
#include "unity.h"

static vector *v;

static void 
test_vector_init (void)
{
	v = vector_init (sizeof (unsigned), 0, NULL);
	TEST_ASSERT_MESSAGE (v != NULL, "failed vector initialization");
}

static void
test_vector_invalid_elem_access (void)
{
	unsigned *ptr;

	ptr = vector_elem (v, -1);
	TEST_ASSERT_MESSAGE (ptr == NULL, "vector elem returned valid pointer");
}

static void
test_vector_append_once (void)
{
	unsigned to_append = 0xdeadbeef;
	unsigned *ptr;

	vector_clear (v);
	vector_append (v, &to_append);
	ptr = vector_elem (v, 0);

	TEST_ASSERT_MESSAGE (ptr != NULL, "vector elem returned null after append");
	TEST_ASSERT_MESSAGE ( *ptr == to_append, "vector append once failed");
}

static void
test_vector_append_multiple (void)
{
	unsigned i;
	unsigned *ptr;

	vector_clear (v);

	/* write multiple times into vector */
	for (i = 0; i < 10; i++)
	{
		vector_append (v, &i);
	}

	/* check the locations */
	for (i = 0; i < 10; i++)
	{
		ptr = vector_elem (v, i);
		TEST_ASSERT_MESSAGE (ptr != NULL, "vector elem returned null after append");
		TEST_ASSERT_MESSAGE (i == *ptr, "append multiple failed");
	}
}

static void
test_vector_append_large (void)
{
	unsigned i;
	unsigned *ptr;

	vector_clear (v);

	/* write a lot of times into vector */
	for (i = 0; i < 10000; i++)
	{
		TEST_ASSERT_MESSAGE (vector_size (v) == i, "vector append large wrong size");
		vector_append (v, &i);
	}

	/* check the locations */
	for (i = 0; i < 10000; i++)
	{
		ptr = vector_elem (v, i);
		TEST_ASSERT_MESSAGE (ptr != NULL, "vector elem returned null after append");
		TEST_ASSERT_MESSAGE (i == *ptr, "vector append large failed");
	}
}

static void 
test_vector_destroy (void)
{
	vector_destroy (v);
	TEST_ASSERT_MESSAGE (0 == 0, "vector destroy should pass");
}

int 
main(void)
{
	UNITY_BEGIN ();
	RUN_TEST (test_vector_init);
	RUN_TEST (test_vector_invalid_elem_access);
	RUN_TEST (test_vector_append_once);
	RUN_TEST (test_vector_append_multiple);
	RUN_TEST (test_vector_append_large);
	RUN_TEST (test_vector_destroy);
	return UNITY_END ();
}
