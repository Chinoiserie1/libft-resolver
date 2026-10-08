#include "test.h"

int	main(void)
{
	int		v = 42;
	t_list	*n;

	n = ft_lstnew(&v);
	CHECK(n != NULL, "ft_lstnew returned NULL");
	if (n)
	{
		CHECK(n->content == &v, "content must be the given pointer");
		CHECK(n->next == NULL, "next must be NULL");
		free(n);
	}
	n = ft_lstnew(NULL);
	CHECK(n != NULL && n->content == NULL, "ft_lstnew(NULL) must create a node with NULL content");
	free(n);
	DONE();
}
