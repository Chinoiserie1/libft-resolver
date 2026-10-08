#include "test.h"

int	main(void)
{
	unsigned char	*p;
	size_t			i;
	int				zeroed;

	p = ft_calloc(42, sizeof(int));
	CHECK(p != NULL, "ft_calloc(42, 4) returned NULL");
	zeroed = 1;
	for (i = 0; p && i < 42 * sizeof(int); i++)
		if (p[i] != 0)
			zeroed = 0;
	CHECK(zeroed, "memory must be filled with zeros");
	free(p);
	p = ft_calloc(0, 0);
	CHECK(p != NULL, "ft_calloc(0, 0) should return a free-able pointer (like calloc)");
	free(p);
	p = ft_calloc(SIZE_MAX, 2);
	CHECK(p == NULL, "ft_calloc(SIZE_MAX, 2) must return NULL (overflow)");
	free(p);
	p = ft_calloc(SIZE_MAX / 2 + 2, 2);
	CHECK(p == NULL, "ft_calloc(SIZE_MAX/2 + 2, 2) must return NULL (overflow)");
	free(p);
	DONE();
}
