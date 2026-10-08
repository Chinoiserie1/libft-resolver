#include "lst_helpers.h"

int	main(void)
{
	int		v[3] = {1, 2, 3};
	t_list	*lst = NULL;
	t_list	*a = make_list(&v[0], 1);
	t_list	*b = make_list(&v[1], 1);
	t_list	*c = make_list(&v[2], 1);

	ft_lstadd_back(&lst, a);
	CHECK(lst == a, "add to empty list: head must become the new node");
	ft_lstadd_back(&lst, b);
	ft_lstadd_back(&lst, c);
	CHECK(lst == a, "head must not change");
	CHECK(a->next == b && b->next == c, "nodes must be in order a -> b -> c");
	CHECK(c->next == NULL, "last node must point to NULL");
	free_list(lst);
	DONE();
}
