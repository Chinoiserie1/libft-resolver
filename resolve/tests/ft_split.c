#include "test.h"

static void	check(const char *s, char c, const char **exp)
{
	char	**got;
	int		i;

	got = ft_split(s, c);
	CHECK(got != NULL, "ft_split(\"%s\", '%c') returned NULL", s, c);
	if (got == NULL)
		return ;
	for (i = 0; exp[i] && got[i]; i++)
		CHECK(strcmp(got[i], exp[i]) == 0,
			"ft_split(\"%s\", '%c')[%d] = \"%s\", expected \"%s\"",
			s, c, i, got[i], exp[i]);
	CHECK(got[i] == NULL && exp[i] == NULL,
		"ft_split(\"%s\", '%c'): wrong number of words or missing NULL at [%d]",
		s, c, i);
	free_split(got);
}

int	main(void)
{
	const char	*e1[] = {"hello", "world", NULL};
	const char	*e2[] = {"a", "b", "c", NULL};
	const char	*e3[] = {NULL};
	const char	*e4[] = {"no-sep", NULL};
	const char	*e5[] = {"lorem", "ipsum", "dolor", NULL};
	const char	*e6[] = {"x", NULL};

	check("hello world", ' ', e1);
	check("  hello   world  ", ' ', e1);
	check("a,b,c", ',', e2);
	check(",,,a,,b,c,,", ',', e2);
	check("", ' ', e3);
	check("     ", ' ', e3);
	check("no-sep", ' ', e4);
	check("no-sep", '\0', e4);
	check("lorem ipsum dolor", ' ', e5);
	check("x", ' ', e6);
	DONE();
}
