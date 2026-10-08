#include "test.h"

int	main(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(ft_toupper(c) == toupper(c), "ft_toupper(%d) = %d, expected %d", c, ft_toupper(c), toupper(c));
	DONE();
}
