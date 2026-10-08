#include "test.h"

static void	call(const void *arg, int fd)
{
	ft_putnbr_fd(*(const int *)arg, fd);
}

int	main(void)
{
	int		nums[] = {0, 7, -7, 42, -42, 100, INT_MAX, INT_MIN};
	char	exp[16];
	char	*got;
	int		i;

	for (i = 0; i < 8; i++)
	{
		snprintf(exp, sizeof(exp), "%d", nums[i]);
		got = capture_fd(call, &nums[i]);
		CHECK_STR(got, exp, "ft_putnbr_fd");
		free(got);
	}
	DONE();
}
