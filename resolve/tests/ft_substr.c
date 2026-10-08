#include "test.h"

static void	check(const char *s, unsigned int start, size_t len, const char *exp)
{
	char	*got;

	got = ft_substr(s, start, len);
	CHECK(got != NULL && strcmp(got, exp) == 0,
		"ft_substr(\"%s\", %u, %zu) = \"%s\", expected \"%s\"",
		s, start, len, got ? got : "(null)", exp);
	free(got);
}

int	main(void)
{
	check("hello world", 0, 5, "hello");
	check("hello world", 6, 5, "world");
	check("hello world", 6, 100, "world");
	check("hello world", 0, 0, "");
	check("hello world", 11, 3, "");
	check("hello world", 42, 3, "");
	check("hello world", 4, 1, "o");
	check("", 0, 10, "");
	check("abc", 0, SIZE_MAX, "abc");
	check("abc", UINT_MAX, 2, "");
	DONE();
}
