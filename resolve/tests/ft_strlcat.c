#include "test.h"

static size_t	ref_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen = strnlen(dst, size);
	size_t	slen = strlen(src);
	size_t	n;

	if (dlen == size)
		return (size + slen);
	n = slen < size - dlen - 1 ? slen : size - dlen - 1;
	memcpy(dst + dlen, src, n);
	dst[dlen + n] = '\0';
	return (dlen + slen);
}

int	main(void)
{
	const char	*dsts[] = {"", "abc", "hello wor", NULL};
	const char	*srcs[] = {"", "xyz", "a much longer source", NULL};
	size_t		sizes[] = {0, 1, 3, 4, 6, 10, 15, 40};
	char		a[48];
	char		b[48];
	size_t		ra;
	size_t		rb;
	int			i;
	int			j;
	int			k;

	for (i = 0; dsts[i]; i++)
		for (j = 0; srcs[j]; j++)
			for (k = 0; k < 8; k++)
			{
				memset(a, 'X', 48);
				memset(b, 'X', 48);
				strcpy(a, dsts[i]);
				strcpy(b, dsts[i]);
				ra = ft_strlcat(a, srcs[j], sizes[k]);
				rb = ref_strlcat(b, srcs[j], sizes[k]);
				CHECK(ra == rb, "dst=\"%s\" src=\"%s\" size=%zu: returned %zu, expected %zu",
					dsts[i], srcs[j], sizes[k], ra, rb);
				CHECK(memcmp(a, b, 48) == 0, "dst=\"%s\" src=\"%s\" size=%zu: got \"%s\", expected \"%s\"",
					dsts[i], srcs[j], sizes[k], a, b);
			}
	DONE();
}
