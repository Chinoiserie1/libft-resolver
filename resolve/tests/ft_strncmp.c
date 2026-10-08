#include "test.h"

int	main(void)
{
	const char	*pairs[][2] = {{"abc", "abc"}, {"abc", "abd"}, {"abd", "abc"},
		{"abc", "ab"}, {"", "a"}, {"a", ""}, {"", ""},
		{"test\200", "test\0"}, {"\xff", "\x01"}, {"abcdef", "abcxyz"}};
	size_t		ns[] = {0, 1, 3, 4, 10};
	int			i;
	int			j;

	for (i = 0; i < 10; i++)
		for (j = 0; j < 5; j++)
			CHECK(same_sign(ft_strncmp(pairs[i][0], pairs[i][1], ns[j]),
				strncmp(pairs[i][0], pairs[i][1], ns[j])),
				"ft_strncmp(\"%s\", \"%s\", %zu) = %d, expected sign of %d",
				pairs[i][0], pairs[i][1], ns[j],
				ft_strncmp(pairs[i][0], pairs[i][1], ns[j]),
				strncmp(pairs[i][0], pairs[i][1], ns[j]));
	DONE();
}
