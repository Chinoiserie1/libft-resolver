#include "test.h"

static size_t	ref_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len = strlen(src);
	size_t	n;

	if (size)
	{
		n = len < size - 1 ? len : size - 1;
		memcpy(dst, src, n);
		dst[n] = '\0';
	}
	return (len);
}

int	main(void)
{
	const char	*srcs[] = {"", "a", "hello", "hello world, long string", NULL};
	size_t		sizes[] = {0, 1, 2, 5, 6, 30};
	char		a[32];
	char		b[32];
	size_t		ra;
	size_t		rb;
	int			i;
	int			j;

	for (i = 0; srcs[i]; i++)
	{
		for (j = 0; j < 6; j++)
		{
			memset(a, 'X', 32);
			memset(b, 'X', 32);
			ra = ft_strlcpy(a, srcs[i], sizes[j]);
			rb = ref_strlcpy(b, srcs[i], sizes[j]);
			CHECK(ra == rb, "ft_strlcpy(dst, \"%s\", %zu) returned %zu, expected %zu",
				srcs[i], sizes[j], ra, rb);
			CHECK(memcmp(a, b, 32) == 0, "ft_strlcpy(dst, \"%s\", %zu) wrong dst content",
				srcs[i], sizes[j]);
		}
	}
	DONE();
}
