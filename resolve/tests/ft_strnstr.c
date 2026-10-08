#include "test.h"

static char	*ref_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l = strlen(little);
	size_t	i;

	if (l == 0)
		return ((char *)big);
	for (i = 0; big[i] && i + l <= len; i++)
		if (strncmp(big + i, little, l) == 0)
			return ((char *)big + i);
	return (NULL);
}

int	main(void)
{
	const char	*big = "Foo Bar Baz";
	const char	*littles[] = {"", "Foo", "Bar", "Baz", "z", "Bazz", "o B", "x", NULL};
	size_t		lens[] = {0, 1, 3, 6, 7, 10, 11, 50};
	char		*got;
	char		*exp;
	int			i;
	int			j;

	for (i = 0; littles[i]; i++)
		for (j = 0; j < 8; j++)
		{
			got = ft_strnstr(big, littles[i], lens[j]);
			exp = ref_strnstr(big, littles[i], lens[j]);
			CHECK(got == exp, "ft_strnstr(\"%s\", \"%s\", %zu) returned \"%s\", expected \"%s\"",
				big, littles[i], lens[j], got ? got : "(null)", exp ? exp : "(null)");
		}
	CHECK(ft_strnstr("", "", 0) != NULL, "ft_strnstr(\"\", \"\", 0) must return big");
	CHECK(ft_strnstr("", "a", 5) == NULL, "ft_strnstr(\"\", \"a\", 5) must be NULL");
	DONE();
}
