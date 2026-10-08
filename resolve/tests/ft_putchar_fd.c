#include "test.h"

static void	call(const void *arg, int fd)
{
	const char	*s = arg;

	while (*s)
		ft_putchar_fd(*s++, fd);
}

int	main(void)
{
	char	*got;

	got = capture_fd(call, "a");
	CHECK_STR(got, "a", "ft_putchar_fd('a')");
	free(got);
	got = capture_fd(call, "Hi!\n\t~");
	CHECK_STR(got, "Hi!\n\t~", "ft_putchar_fd on each char of \"Hi!\\n\\t~\"");
	free(got);
	DONE();
}
