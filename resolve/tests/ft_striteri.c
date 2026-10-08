#include "test.h"

static void	add_index(unsigned int i, char *c)
{
	*c = *c + i;
}

static void	upper_odd(unsigned int i, char *c)
{
	if (i % 2 == 1)
		*c = toupper(*c);
}

int	main(void)
{
	char	a[] = "aaaa";
	char	b[] = "hello";
	char	e[] = "";

	ft_striteri(a, add_index);
	CHECK_STR(a, "abcd", "ft_striteri(\"aaaa\", c + i)");
	ft_striteri(b, upper_odd);
	CHECK_STR(b, "hElLo", "ft_striteri(\"hello\", upper on odd index)");
	ft_striteri(e, add_index);
	CHECK_STR(e, "", "ft_striteri(\"\", f)");
	DONE();
}
