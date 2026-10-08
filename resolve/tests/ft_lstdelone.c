#include "lst_helpers.h"

static void	free_content(void *content)
{
	g_del_calls++;
	free(content);
}

int	main(void)
{
	int		v[2] = {1, 2};
	t_list	*lst = make_list(v, 2);
	t_list	*second = lst->next;
	t_list	*n;

	ft_lstdelone(lst, count_del);
	CHECK(g_del_calls == 1, "del must be called exactly once (called %d)", g_del_calls);
	CHECK(second->next == NULL && *(int *)second->content == 2,
		"the next node must not be touched");
	free(second);
	g_del_calls = 0;
	n = malloc(sizeof(t_list));
	n->content = strdup("heap content");
	n->next = NULL;
	ft_lstdelone(n, free_content);
	CHECK(g_del_calls == 1, "del must be called on malloc'd content");
	DONE();
}
