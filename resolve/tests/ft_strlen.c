#include "test.h"

int	main(void)
{
	const char	*cases[] = {"", "a", "hello", "hello\0world", "  tabs\t\n",
		"\x80\xff unsigned", NULL};
	char		big[10001];
	int			i;

	for (i = 0; cases[i]; i++)
		CHECK(ft_strlen(cases[i]) == strlen(cases[i]),
			"ft_strlen(\"%s\") = %zu, expected %zu", esc(cases[i]),
			ft_strlen(cases[i]), strlen(cases[i]));
	memset(big, 'x', 10000);
	big[10000] = '\0';
	CHECK(ft_strlen(big) == 10000, "ft_strlen(10000 chars) = %zu",
		ft_strlen(big));
	DONE();
}
