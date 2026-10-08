#include "test.h"

int	main(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(!!ft_isascii(c) == !!isascii(c), "ft_isascii(%d) = %d, expected %s", c, ft_isascii(c), isascii(c) ? "non-zero" : "0");
	DONE();
}
