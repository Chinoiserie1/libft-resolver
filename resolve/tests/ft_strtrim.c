#include "test.h"

static void	check(const char *s, const char *set, const char *exp)
{
	char	*got;

	got = ft_strtrim(s, set);
	CHECK(got != NULL && strcmp(got, exp) == 0,
		"ft_strtrim(\"%s\", \"%s\") = \"%s\", expected \"%s\"",
		esc(s), esc(set), esc(got), esc(exp));
	free(got);
}

int	main(void)
{
	check("  hello  ", " ", "hello");
	check("xxhelloxyx", "xy", "hello");
	check("  hel lo  ", " ", "hel lo");
	check("hello", "", "hello");
	check("hello", "xyz", "hello");
	check("   ", " ", "");
	check("", " ", "");
	check("", "", "");
	check("abcba", "ab", "c");
	check("\t\n hi \n\t", " \t\n", "hi");
	DONE();
}
