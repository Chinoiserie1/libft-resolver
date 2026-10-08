#include "test.h"

int	main(void)
{
	const char	s[] = "abc\0def\xff";
	int			cs[] = {'a', 'c', '\0', 'e', 0xff, -1, 'z', 'd' + 256};
	size_t		ns[] = {0, 2, 4, 6, 9};
	int			i;
	int			j;

	for (i = 0; i < 8; i++)
		for (j = 0; j < 5; j++)
			CHECK(ft_memchr(s, cs[i], ns[j]) == memchr(s, cs[i], ns[j]),
				"ft_memchr(s, %d, %zu) returned %p, expected %p", cs[i], ns[j],
				ft_memchr(s, cs[i], ns[j]), memchr(s, cs[i], ns[j]));
	DONE();
}
