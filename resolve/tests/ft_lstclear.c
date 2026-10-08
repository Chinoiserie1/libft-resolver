#include "lst_helpers.h"

int	main(void)
{
	int		v[4] = {1, 2, 3, 4};
	t_list	*lst = make_list(v, 4);
	t_list	*empty = NULL;

	ft_lstclear(&lst, count_del);
	CHECK(g_del_calls == 4, "del must be called on every node (called %d, expected 4)", g_del_calls);
	CHECK(lst == NULL, "*lst must be set to NULL");
	g_del_calls = 0;
	ft_lstclear(&empty, count_del);
	CHECK(g_del_calls == 0 && empty == NULL, "clearing an empty list must do nothing");
	DONE();
}
