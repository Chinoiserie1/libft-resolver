#include "lst_helpers.h"

static void	double_it(void *content)
{
	*(int *)content *= 2;
}

int	main(void)
{
	int		v[3] = {1, 2, 3};
	t_list	*lst = make_list(v, 3);

	ft_lstiter(lst, double_it);
	CHECK(v[0] == 2 && v[1] == 4 && v[2] == 6,
		"f must be applied once to each content (got %d %d %d, expected 2 4 6)",
		v[0], v[1], v[2]);
	ft_lstiter(NULL, double_it);
	CHECK(1, "ft_lstiter(NULL, f) must not crash");
	free_list(lst);
	DONE();
}
