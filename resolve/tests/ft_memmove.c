#include "test.h"

int	main(void)
{
	char	a[32] = {0};
	char	b[32] = {0};

	strcpy(a, "0123456789abcdef");
	strcpy(b, "0123456789abcdef");
	CHECK(ft_memmove(a + 3, a, 10) == a + 3, "must return dest");
	memmove(b + 3, b, 10);
	CHECK(memcmp(a, b, 32) == 0, "overlap dest > src: got \"%s\", expected \"%s\"", a, b);
	strcpy(a, "0123456789abcdef");
	strcpy(b, "0123456789abcdef");
	ft_memmove(a, a + 4, 10);
	memmove(b, b + 4, 10);
	CHECK(memcmp(a, b, 32) == 0, "overlap dest < src: got \"%s\", expected \"%s\"", a, b);
	ft_memmove(a, "XYZ", 3);
	memmove(b, "XYZ", 3);
	CHECK(memcmp(a, b, 32) == 0, "no overlap: got \"%s\", expected \"%s\"", a, b);
	ft_memmove(a, a, 5);
	CHECK(memcmp(a, b, 32) == 0, "dest == src must not change anything");
	ft_memmove(a + 1, a, 0);
	CHECK(memcmp(a, b, 32) == 0, "n = 0 must not write anything");
	DONE();
}
