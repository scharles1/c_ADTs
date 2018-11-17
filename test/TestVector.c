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
vector_init_random (vector *v, size_t n, size_t max)
{
	unsigned i, to_append;

	vector_clear (v);
	for (i = 0; i < n; i++)
	{
		to_append = (unsigned)(rand() % max);
		vector_append (v, &to_append);
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

	vector_init_random (v, 1000, 100);
	ptr1 = vector_search (v, &key, compare_unsigned, false);
	TEST_ASSERT_MESSAGE (ptr1 == NULL, "vector linear search failed");

	vector_append (v, &key);
	ptr1 = vector_search (v, &key, compare_unsigned, false);
	ptr2 = vector_access (v, vector_size (v) - 1);
	TEST_ASSERT_MESSAGE (ptr1 == ptr2, "vector linear search failed");
}

static void
test_vector_sort (void)
{
	unsigned i, min = 0;;
	unsigned *cur, *prev = &min;

	vector_init_random (v, 1000, 1000);
	vector_sort (v, compare_unsigned);

	for (i = 0; i < 1000; i++)
	{
		cur = vector_access (v, i);
		TEST_ASSERT_MESSAGE (*prev <= *cur, "vector sort not sorted correctly");
		prev = cur;
	}

}

static void 
test_vector_destroy (void)
{
	vector_destroy (v);
	TEST_ASSERT_MESSAGE (0 == 0, "vector destroy should pass");
}

static int 
vector_size_compare (const void *elem1, const void *elem2)
{
	vector * const *v1 = elem1;
	vector * const *v2 = elem2;

	return (int)(vector_size (*v1) - vector_size (*v2));
}

static void 
complex_vector_destroy (void *addr)
{
	vector **p_v = addr;
	vector_destroy (*p_v);
}

static void
test_complex_vector (void)
{
	unsigned i, j, min = 0;
	unsigned *cur, *prev;
	vector *v_vectors, *p_v;

	/* initialize vector of vectors */
	v_vectors = vector_init (sizeof (vector *), 0, complex_vector_destroy);

	/* populate with vectors of integers */
	for (i = 0; i < 100; i++)
	{
		p_v = vector_init (sizeof (unsigned), 0, NULL);
		vector_init_random (p_v, (size_t)(rand() % 100), 100);
		vector_append (v_vectors, &p_v);
	}

	/* sort each vector inside the complex vector and verify */
	for (i = 0; i < vector_size (v_vectors); i++)
	{
		p_v = *(vector **)(vector_access (v_vectors, i));
		vector_sort (p_v, compare_unsigned);

		prev = &min;
		for (j = 0; j < vector_size (p_v); j++)
		{
			cur = vector_access (p_v, j);
			TEST_ASSERT_MESSAGE (*prev <= *cur, "vector sort not sorted correctly");
			prev = cur;
		}
	}

	/* sort the vector of vectors by length (shortest first) */
	vector_sort (v_vectors, vector_size_compare);
	
	/* verify shortest vector first */
	size_t prev_len = 0, cur_len;
	for (i = 0; i < vector_size (v_vectors); i++)
	{
		p_v = *(vector **)(vector_access (v_vectors, i));
		cur_len = vector_size (p_v);

		TEST_ASSERT_MESSAGE (prev_len <= cur_len, "vector sort of complex vector failed");
		prev_len = cur_len;
	}

	vector_destroy (v_vectors);
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
	RUN_TEST (test_vector_sort);
	RUN_TEST (test_vector_destroy);
	RUN_TEST (test_complex_vector);
	return UNITY_END ();
}
