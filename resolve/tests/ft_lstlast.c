#include "lst_helpers.h"

int	main(void)
{
	int		v[4] = {1, 2, 3, 4};
	t_list	*lst;

	CHECK(ft_lstlast(NULL) == NULL, "ft_lstlast(NULL) must be NULL");
	lst = make_list(v, 1);
	CHECK(ft_lstlast(lst) == lst, "last of 1-node list must be the node itself");
	free_list(lst);
	lst = make_list(v, 4);
	CHECK(ft_lstlast(lst) == lst->next->next->next, "wrong last node");
	CHECK(ft_lstlast(lst) && *(int *)ft_lstlast(lst)->content == 4, "last content must be 4");
	free_list(lst);
	DONE();
}
