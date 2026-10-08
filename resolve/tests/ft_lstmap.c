#include "lst_helpers.h"

static void	*plus_ten(void *content)
{
	int	*n = malloc(sizeof(int));

	if (n)
		*n = *(int *)content + 10;
	return (n);
}

int	main(void)
{
	int		v[3] = {1, 2, 3};
	t_list	*lst = make_list(v, 3);
	t_list	*map;
	t_list	*it;
	int		i;

	map = ft_lstmap(lst, plus_ten, free);
	CHECK(map != NULL, "ft_lstmap returned NULL");
	for (i = 0, it = map; it && i < 3; i++, it = it->next)
		CHECK(*(int *)it->content == v[i] + 10,
			"node %d: content = %d, expected %d", i, *(int *)it->content, v[i] + 10);
	CHECK(i == 3 && it == NULL, "new list must have exactly 3 nodes");
	CHECK(v[0] == 1 && v[1] == 2 && v[2] == 3, "original list must not be modified");
	CHECK(map != lst, "ft_lstmap must create a new list");
	while (map)
	{
		it = map->next;
		free(map->content);
		free(map);
		map = it;
	}
	CHECK(ft_lstmap(NULL, plus_ten, free) == NULL, "ft_lstmap(NULL, ...) must be NULL");
	free_list(lst);
	DONE();
}
