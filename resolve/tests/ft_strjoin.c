#include "test.h"

static void	check(const char *a, const char *b, const char *exp)
{
	char	*got;

	got = ft_strjoin(a, b);
	CHECK(got != NULL && strcmp(got, exp) == 0,
		"ft_strjoin(\"%s\", \"%s\") = \"%s\", expected \"%s\"",
		a, b, got ? got : "(null)", exp);
	free(got);
}

int	main(void)
{
	check("hello ", "world", "hello world");
	check("", "world", "world");
	check("hello", "", "hello");
	check("", "", "");
	check("a", "b", "ab");
	DONE();
}
