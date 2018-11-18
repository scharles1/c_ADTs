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
	RUN_TEST (test_list_destroy);
	return UNITY_END ();
}