#include "test.h"

int	main(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(!!ft_isdigit(c) == !!isdigit(c), "ft_isdigit(%d) = %d, expected %s", c, ft_isdigit(c), isdigit(c) ? "non-zero" : "0");
	DONE();
}
