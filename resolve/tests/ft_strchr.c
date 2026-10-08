#include "test.h"

int	main(void)
{
	const char	*s = "hello world";
	int			cs[] = {'h', 'o', 'd', 'z', '\0', 'l' + 256, -1};
	int			i;

	for (i = 0; i < 7; i++)
		CHECK(ft_strchr(s, cs[i]) == strchr(s, cs[i]),
			"ft_strchr(\"%s\", %d) returned %p, expected %p", s, cs[i],
			(void *)ft_strchr(s, cs[i]), (void *)strchr(s, cs[i]));
	CHECK(ft_strchr("", 'a') == NULL, "ft_strchr(\"\", 'a') must be NULL");
	CHECK(ft_strchr("", '\0') != NULL, "ft_strchr(\"\", '\\0') must find the terminator");
	DONE();
}
