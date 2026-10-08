#include "test.h"

static void	call(const void *arg, int fd)
{
	ft_putendl_fd((char *)arg, fd);
}

int	main(void)
{
	char	*got;

	got = capture_fd(call, "hello");
	CHECK_STR(got, "hello\n", "ft_putendl_fd(\"hello\")");
	free(got);
	got = capture_fd(call, "");
	CHECK_STR(got, "\n", "ft_putendl_fd(\"\")");
	free(got);
	DONE();
}
