#include "test.h"

static char	add_index(unsigned int i, char c)
{
	return (c + i);
}

static char	upper_even(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (toupper(c));
	return (c);
}

int	main(void)
{
	char	*got;

	got = ft_strmapi("aaaa", add_index);
	CHECK_STR(got, "abcd", "ft_strmapi(\"aaaa\", c + i)");
	free(got);
	got = ft_strmapi("hello", upper_even);
	CHECK_STR(got, "HeLlO", "ft_strmapi(\"hello\", upper on even index)");
	free(got);
	got = ft_strmapi("", add_index);
	CHECK_STR(got, "", "ft_strmapi(\"\", f)");
	free(got);
	DONE();
}
