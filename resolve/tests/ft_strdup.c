#include "test.h"

int	main(void)
{
	const char	*cases[] = {"", "a", "hello world", "with\ttab\n", NULL};
	char		*d;
	int			i;

	for (i = 0; cases[i]; i++)
	{
		d = ft_strdup(cases[i]);
		CHECK_STR(d, cases[i], "ft_strdup");
		CHECK(d != cases[i], "ft_strdup must return a new pointer");
		free(d);
	}
	DONE();
}
