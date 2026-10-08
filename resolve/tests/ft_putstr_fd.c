#include "test.h"

static void	call(const void *arg, int fd)
{
	ft_putstr_fd((char *)arg, fd);
}

int	main(void)
{
	const char	*cases[] = {"hello", "", "multi\nline\n", NULL};
	char		*got;
	int			i;

	for (i = 0; cases[i]; i++)
	{
		got = capture_fd(call, cases[i]);
		CHECK_STR(got, cases[i], "ft_putstr_fd");
		free(got);
	}
	DONE();
}
