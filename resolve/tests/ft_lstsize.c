#include "lst_helpers.h"

int	main(void)
{
	int		v[5] = {1, 2, 3, 4, 5};
	t_list	*lst;

	CHECK((int)ft_lstsize(NULL) == 0, "ft_lstsize(NULL) = %d, expected 0", (int)ft_lstsize(NULL));
	lst = make_list(v, 1);
	CHECK((int)ft_lstsize(lst) == 1, "size of 1-node list = %d", (int)ft_lstsize(lst));
	free_list(lst);
	lst = make_list(v, 5);
	CHECK((int)ft_lstsize(lst) == 5, "size of 5-node list = %d", (int)ft_lstsize(lst));
	free_list(lst);
	DONE();
}
