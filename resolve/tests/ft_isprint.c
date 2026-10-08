#include "test.h"

int	main(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(!!ft_isprint(c) == !!isprint(c), "ft_isprint(%d) = %d, expected %s", c, ft_isprint(c), isprint(c) ? "non-zero" : "0");
	DONE();
}
