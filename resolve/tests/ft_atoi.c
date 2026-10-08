#include "test.h"

int	main(void)
{
	const char	*cases[] = {"0", "42", "-42", "+42", "   \t\n\v\f\r  123",
		"2147483647", "-2147483648", "+-5", "-+5", "--5", "++5", " - 5",
		"12abc34", "abc", "", "   ", "0000042", "-0", "\x01 5", "5 6",
		"\t-00123x", NULL};
	int			i;

	for (i = 0; cases[i]; i++)
		CHECK(ft_atoi(cases[i]) == atoi(cases[i]),
			"ft_atoi(\"%s\") = %d, expected %d", esc(cases[i]),
			ft_atoi(cases[i]), atoi(cases[i]));
	DONE();
}
