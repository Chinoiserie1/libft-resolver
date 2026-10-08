#include "test.h"

int	main(void)
{
	char	src[] = "Hello\0World!";
	char	a[20];
	char	b[20];
	int		ints[4] = {1, -2, 3, INT_MAX};
	int		dst[4];

	memset(a, '.', 20);
	memset(b, '.', 20);
	CHECK(ft_memcpy(a, src, 12) == a, "must return dest");
	memcpy(b, src, 12);
	CHECK(memcmp(a, b, 20) == 0, "must copy through '\\0' (12 bytes)");
	ft_memcpy(a, "zzz", 0);
	CHECK(memcmp(a, b, 20) == 0, "n = 0 must not write anything");
	ft_memcpy(dst, ints, sizeof(ints));
	CHECK(memcmp(dst, ints, sizeof(ints)) == 0, "copying an int array failed");
	DONE();
}
