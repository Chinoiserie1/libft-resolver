#include "test.h"

int	main(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(ft_tolower(c) == tolower(c), "ft_tolower(%d) = %d, expected %d", c, ft_tolower(c), tolower(c));
	DONE();
}
