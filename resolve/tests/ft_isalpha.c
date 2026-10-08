#include "test.h"

int	main(void)
{
	int	c;

	for (c = -1; c <= 255; c++)
		CHECK(!!ft_isalpha(c) == !!isalpha(c), "ft_isalpha(%d) = %d, expected %s", c, ft_isalpha(c), isalpha(c) ? "non-zero" : "0");
	DONE();
}
