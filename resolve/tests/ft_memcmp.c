#include "test.h"

int	main(void)
{
	const char	*pairs[][2] = {{"abc", "abc"}, {"abc", "abd"}, {"abd", "abc"},
		{"ab\0x", "ab\0y"}, {"\200", "\0"}, {"\xff", "\x01"}};
	size_t		ns[] = {0, 1, 3, 4};
	int			i;
	int			j;

	for (i = 0; i < 6; i++)
		for (j = 0; j < 4; j++)
		{
			if (ns[j] > 1 && i >= 4)
				continue ;
			CHECK(same_sign(ft_memcmp(pairs[i][0], pairs[i][1], ns[j]),
				memcmp(pairs[i][0], pairs[i][1], ns[j])),
				"ft_memcmp(\"%s\", \"%s\", %zu) = %d, expected sign of %d",
				pairs[i][0], pairs[i][1], ns[j],
				ft_memcmp(pairs[i][0], pairs[i][1], ns[j]),
				memcmp(pairs[i][0], pairs[i][1], ns[j]));
		}
	DONE();
}
