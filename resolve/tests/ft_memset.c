#include "test.h"

int	main(void)
{
	char	a[32];
	char	b[32];
	void	*ret;

	memset(a, 'z', 32);
	memset(b, 'z', 32);
	ret = ft_memset(a, 'A', 10);
	memset(b, 'A', 10);
	CHECK(ret == a, "must return its first argument");
	CHECK(memcmp(a, b, 32) == 0, "ft_memset(buf, 'A', 10) wrong content");
	ft_memset(a, 0x1FF, 5);
	memset(b, 0x1FF, 5);
	CHECK(memcmp(a, b, 32) == 0, "c must be converted to unsigned char (0x1FF)");
	ft_memset(a, -1, 3);
	memset(b, -1, 3);
	CHECK(memcmp(a, b, 32) == 0, "ft_memset(buf, -1, 3) wrong content");
	ft_memset(a, 'Q', 0);
	CHECK(memcmp(a, b, 32) == 0, "n = 0 must not write anything");
	DONE();
}
