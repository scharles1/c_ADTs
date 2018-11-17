#include "Vector.h"
#include "unity.h"

static vector *v;

static void 
test_vector_init (void)
{
	v = vector_init (sizeof (unsigned), 200, NULL);
	TEST_ASSERT_MESSAGE (v != NULL, "failed vector initialization");
}

static void
test_vector_append_once (void)
{
	unsigned to_append = 0xdeadbeef;
	unsigned *ptr;

	vector_clear (v);
	vector_append (v, &to_append);
	ptr = vector_access (v, 0);

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
		ptr = vector_access (v, i);
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
		ptr = vector_access (v, i);
		TEST_ASSERT_MESSAGE (ptr != NULL, "vector elem returned null after append");
		TEST_ASSERT_MESSAGE (i == *ptr, "vector append large failed");
	}
}

static void
test_vector_replace (void)
{
	unsigned i, data = 0xdeadbeef;
	unsigned *ptr;

	vector_clear (v);

	/* write a lot of times into vector */
	for (i = 0; i < 10000; i++)
	{
		vector_append (v, &i);
	}

	/* no replace those values */
	for (i = 0; i < 10000; i++)
	{
		vector_replace (v, &data, i);
	}

	/* check */
	for (i = 0; i < 10000; i++)
	{
		ptr = vector_access (v, i);
		TEST_ASSERT_MESSAGE (data = *ptr, "vector replace small fail");
	}
}

static void
test_vector_insert (void)
{
	unsigned i;
	unsigned *ptr;

	vector_clear (v);

	/* insert into front */
	for (i = 0; i < 10000; i++)
	{
		vector_insert (v, &i, 0);
	}

	/* check */
	for (i = 0; i < 10000; i++)
	{
		ptr = vector_access (v, i);
		TEST_ASSERT_MESSAGE ((10000 - i - 1) == *ptr, "vector insert fail");
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
	RUN_TEST (test_vector_append_once);
	RUN_TEST (test_vector_append_multiple);
	RUN_TEST (test_vector_append_large);
	RUN_TEST (test_vector_replace);
	RUN_TEST (test_vector_insert);
	RUN_TEST (test_vector_destroy);
	return UNITY_END ();
}
