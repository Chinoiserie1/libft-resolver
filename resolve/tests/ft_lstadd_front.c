#include "lst_helpers.h"

int	main(void)
{
	int		v[3] = {1, 2, 3};
	t_list	*lst = NULL;
	t_list	*a = make_list(&v[0], 1);
	t_list	*b = make_list(&v[1], 1);

	ft_lstadd_front(&lst, a);
	CHECK(lst == a, "add to empty list: head must be the new node");
	CHECK(a->next == NULL, "add to empty list: new->next must be NULL");
	ft_lstadd_front(&lst, b);
	CHECK(lst == b, "head must be the new node");
	CHECK(b->next == a, "new->next must be the old head");
	free_list(lst);
	DONE();
}
