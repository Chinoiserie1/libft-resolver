#include "test.h"

int	main(void)
{
	const char	*s = "hello world";
	int			cs[] = {'h', 'o', 'l', 'z', '\0', 'o' + 256, -1};
	int			i;

	for (i = 0; i < 7; i++)
		CHECK(ft_strrchr(s, cs[i]) == strrchr(s, cs[i]),
			"ft_strrchr(\"%s\", %d) returned %p, expected %p", s, cs[i],
			(void *)ft_strrchr(s, cs[i]), (void *)strrchr(s, cs[i]));
	CHECK(ft_strrchr("", 'a') == NULL, "ft_strrchr(\"\", 'a') must be NULL");
	CHECK(ft_strrchr(s, '\0') == s + 11, "ft_strrchr(s, '\\0') must return a pointer to the terminator");
	DONE();
}
