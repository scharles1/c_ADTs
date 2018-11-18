#include "List.h"
#include "unity.h"

static list *l;

typedef struct
{
	list_elem le;
	unsigned data;
} my_node;

static void 
test_list_init (void)
{
	l = list_init (NULL);
	TEST_ASSERT_MESSAGE (l != NULL, "failed list initialization");
}

static void
test_list_push_front_one (void)
{
	my_node n, *front, *back;
	n.data = 0xdeadbeef;

	list_push_front (l, &n);
	TEST_ASSERT_MESSAGE (list_size (l) == 1, "size incorrect in list push front one");
	
	front = list_front (l);
	TEST_ASSERT_MESSAGE (front->data == 0xdeadbeef, "incorrect data");
	
	back = list_back (l);
	TEST_ASSERT_MESSAGE (back->data == 0xdeadbeef, "incorrect data");

	list_pop_front (l);
	TEST_ASSERT_MESSAGE (list_size (l) == 0, "size incorrect in list push front one");
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
	RUN_TEST (test_list_destroy);
	return UNITY_END ();
}