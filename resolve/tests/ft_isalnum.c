#include "test.h"

int	main(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(!!ft_isalnum(c) == !!isalnum(c), "ft_isalnum(%d) = %d, expected %s", c, ft_isalnum(c), isalnum(c) ? "non-zero" : "0");
	DONE();
}
