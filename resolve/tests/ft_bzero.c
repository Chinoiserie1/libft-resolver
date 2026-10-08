#include "test.h"

int	main(void)
{
	char	a[16];
	char	b[16];

	memset(a, 'x', 16);
	memset(b, 'x', 16);
	ft_bzero(a, 5);
	memset(b, 0, 5);
	CHECK(memcmp(a, b, 16) == 0, "ft_bzero(buf, 5) wrong content");
	ft_bzero(a + 10, 0);
	CHECK(memcmp(a, b, 16) == 0, "n = 0 must not write anything");
	ft_bzero(a, 16);
	memset(b, 0, 16);
	CHECK(memcmp(a, b, 16) == 0, "ft_bzero(buf, 16) wrong content");
	DONE();
}
