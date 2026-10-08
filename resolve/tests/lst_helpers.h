/* Helpers shared by the linked-list tests. */

#ifndef LST_HELPERS_H
# define LST_HELPERS_H

# include "test.h"

static int	g_del_calls = 0;

static inline void	count_del(void *content)
{
	(void)content;
	g_del_calls++;
}

/* Builds a list of n nodes whose contents point to vals[i] (not malloc'd). */
static inline t_list	*make_list(int *vals, int n)
{
	t_list	*head = NULL;
	t_list	*node;
	int		i;

	for (i = n - 1; i >= 0; i--)
	{
		node = malloc(sizeof(t_list));
		node->content = &vals[i];
		node->next = head;
		head = node;
	}
	return (head);
}

static inline void	free_list(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
}

#endif
