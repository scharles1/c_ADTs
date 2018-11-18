#include "List.h"
#include "unity.h"

static list *l;

typedef struct
{
	list_elem le;
	unsigned data;
} my_node;

static void
my_list_destroy (void *addr)
{
	free (addr);
}

static void 
test_list_init (void)
{
	l = list_init (my_list_destroy);
	TEST_ASSERT_MESSAGE (l != NULL, "failed list initialization");
}

static void
test_list_push_front_one (void)
{
	my_node *to_insert, *front, *back;
	to_insert = malloc (sizeof (my_node));
	to_insert->data = 0xdeadbeef;

	list_push_front (l, to_insert);
	TEST_ASSERT_MESSAGE (list_size (l) == 1, "size incorrect in list push front one");
	
	front = list_front (l);
	TEST_ASSERT_MESSAGE (front->data == 0xdeadbeef, "incorrect data");
	
	back = list_back (l);
	TEST_ASSERT_MESSAGE (back->data == 0xdeadbeef, "incorrect data");

	list_pop_front (l);
	TEST_ASSERT_MESSAGE (list_size (l) == 0, "size incorrect in list push front one");
}

static void
test_list_push_back_one (void)
{
	my_node *to_insert, *front, *back;
	to_insert = malloc (sizeof (my_node));
	to_insert->data = 0xdeadbeef;

	list_push_back (l, to_insert);
	TEST_ASSERT_MESSAGE (list_size (l) == 1, "size incorrect in list push front one");
	
	front = list_front (l);
	TEST_ASSERT_MESSAGE (front->data == 0xdeadbeef, "incorrect data");
	
	back = list_back (l);
	TEST_ASSERT_MESSAGE (back->data == 0xdeadbeef, "incorrect data");

	list_pop_back (l);
	TEST_ASSERT_MESSAGE (list_size (l) == 0, "size incorrect in list push front one");
}

static void
test_list_push_front_large (void)
{
	my_node *to_insert, *front;
	unsigned i;

	for (i = 0; i < 10000; i++)
	{
		to_insert = malloc (sizeof (my_node));
		to_insert->data = 0xdeadbeef;
		list_push_front (l, to_insert);
	}

	while ((front = list_front (l)))
	{
		TEST_ASSERT_MESSAGE (front->data == 0xdeadbeef, "incorrect data");
		list_pop_front (l);
	}
}

static void
test_list_push_back_large (void)
{
	my_node *to_insert, *back;
	unsigned i;

	for (i = 0; i < 10000; i++)
	{
		to_insert = malloc (sizeof (my_node));
		to_insert->data = 0xdeadbeef;
		list_push_back (l, to_insert);
	}

	while ((back = list_back (l)))
	{
		TEST_ASSERT_MESSAGE (back->data == 0xdeadbeef, "incorrect data");
		list_pop_back (l);
	}
}

static void
test_list_destroy (void)
{
	list_destroy (l);
	TEST_ASSERT_MESSAGE (0 == 0, "destroy passes");
}

int 
main(void)
{
	UNITY_BEGIN ();
	RUN_TEST (test_list_init);
	RUN_TEST (test_list_push_front_one);
	RUN_TEST (test_list_push_back_one);
	RUN_TEST (test_list_push_front_large);
	RUN_TEST (test_list_push_back_large);
	RUN_TEST (test_list_destroy);
	return UNITY_END ();
}