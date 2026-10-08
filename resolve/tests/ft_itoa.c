#include "test.h"

int	main(void)
{
	int		nums[] = {0, 1, -1, 9, 10, -10, 42, -42, 123456, -987654,
		INT_MAX, INT_MIN};
	char	exp[16];
	char	*got;
	int		i;

	for (i = 0; i < 12; i++)
	{
		snprintf(exp, sizeof(exp), "%d", nums[i]);
		got = ft_itoa(nums[i]);
		CHECK_STR(got, exp, "ft_itoa");
		free(got);
	}
	DONE();
}
