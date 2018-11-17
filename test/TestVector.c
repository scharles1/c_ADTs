#include "Vector.h"
#include "unity.h"

static vector *v;

static int compare_unsigned (const void *elem1, const void *elem2)
{
	const unsigned *ptr1 = elem1;
	const unsigned *ptr2 = elem2;

	return (int)(*ptr1 - *ptr2);
}

static void
vector_init_linear (size_t n, bool ascending)
{
	unsigned i;

	vector_clear (v);
	for (i = 0; i < n; i++)
	{
		if (ascending)
		{
			vector_append (v, &i);
		}
		else
		{
			vector_insert (v, &i, 0);
		}
	}
}

static void
vector_init_random (size_t n, size_t max)
{
	unsigned i;

	vector_clear (v);
	for (i = 0; i < n; i++)
	{
		n = (unsigned)(rand() % max);
		vector_append (v, &n);
	}
}

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

	/* write multiple times into vector */
	vector_init_linear (10, true);

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

	/* write a lot of times into vector */
	vector_init_linear (10000, true);

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

	/* write a lot of times into vector */
	vector_init_linear (10000, true);

	/* now replace those values */
	for (i = 0; i < 10000; i++)
	{
		vector_replace (v, &data, i);
	}

	/* check */
	for (i = 0; i < 10000; i++)
	{
		ptr = vector_access (v, i);
		TEST_ASSERT_MESSAGE (data = *ptr, "vector replace fail");
	}
}

static void
test_vector_insert (void)
{
	unsigned i;
	unsigned *ptr;

	vector_clear (v);

	/* insert into front with linear init function */
	vector_init_linear (10000, false);

	/* check */
	for (i = 0; i < 10000; i++)
	{
		ptr = vector_access (v, i);
		TEST_ASSERT_MESSAGE ((10000 - i - 1) == *ptr, "vector insert fail");
	}
}

static void
test_vector_bsearch (void)
{
	unsigned i, key = 497;
	unsigned *ptr1, *ptr2;

	vector_init_linear (1000, true);

	ptr1 = vector_search (v, &key, compare_unsigned, true);
	ptr2 = vector_access (v, key);
	TEST_ASSERT_MESSAGE (ptr1 == ptr2, "vector binary search failed");
	TEST_ASSERT_MESSAGE (*ptr1 = key, "vector binary search failed");
}

static void
test_vector_lsearch (void)
{
	unsigned i, key = 101;
	unsigned *ptr1, *ptr2;

	vector_init_random (1000, 100);
	ptr1 = vector_search (v, &key, compare_unsigned, false);
	TEST_ASSERT_MESSAGE (ptr1 == NULL, "vector linear search failed");

	vector_append (v, &key);
	ptr1 = vector_search (v, &key, compare_unsigned, false);
	ptr2 = vector_access (v, vector_size (v) - 1);
	TEST_ASSERT_MESSAGE (ptr1 == ptr2, "vector linear search failed");
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
	time_t t;

	/* Intializes random number generator */
	srand((unsigned) time(&t));

	UNITY_BEGIN ();
	RUN_TEST (test_vector_init);
	RUN_TEST (test_vector_append_once);
	RUN_TEST (test_vector_append_multiple);
	RUN_TEST (test_vector_append_large);
	RUN_TEST (test_vector_replace);
	RUN_TEST (test_vector_insert);
	RUN_TEST (test_vector_bsearch);
	RUN_TEST (test_vector_lsearch);
	RUN_TEST (test_vector_destroy);
	return UNITY_END ();
}
