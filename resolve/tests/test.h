/* Shared helpers for the resolve test suite. Not part of the libft. */

#ifndef TEST_H
# define TEST_H

# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <limits.h>
# include <unistd.h>

static int	g_total = 0;
static int	g_failed = 0;

/* CHECK(condition, "printf-style message explaining the case") */
# define CHECK(cond, ...) \
	do { \
		g_total++; \
		if (!(cond)) \
		{ \
			g_failed++; \
			printf("    KO (line %d) ", __LINE__); \
			printf(__VA_ARGS__); \
			printf("\n"); \
			fflush(stdout); \
		} \
	} while (0)

/* Compare two C strings, NULL-safe, and print both on failure. */
# define CHECK_STR(got, exp, label) \
	do { \
		const char	*g_ = (got); \
		const char	*e_ = (exp); \
		CHECK((g_ == NULL && e_ == NULL) \
			|| (g_ != NULL && e_ != NULL && strcmp(g_, e_) == 0), \
			"%s: got \"%s\", expected \"%s\"", (label), \
			esc(g_), esc(e_)); \
	} while (0)

/* Last line printed by every test: parsed by run.sh. */
# define DONE() \
	do { \
		printf("RESULT %d %d\n", g_total - g_failed, g_total); \
		return (g_failed != 0); \
	} while (0)

/* Returns s with \n, \t... escaped, for readable messages (4 slots). */
static inline const char	*esc(const char *s)
{
	static char	bufs[4][256];
	static int	slot = 0;
	char		*out;
	size_t		j;

	if (s == NULL)
		return ("(null)");
	out = bufs[slot++ % 4];
	for (j = 0; *s && j < 250; s++)
	{
		if (*s == '\n' || *s == '\t' || *s == '\v' || *s == '\f' || *s == '\r')
		{
			out[j++] = '\\';
			out[j++] = "ntvfr"[strchr("\n\t\v\f\r", *s) - "\n\t\v\f\r"];
		}
		else if ((unsigned char)*s < 32 || (unsigned char)*s > 126)
			j += snprintf(out + j, 5, "\\x%02x", (unsigned char)*s);
		else
			out[j++] = *s;
	}
	out[j] = '\0';
	return (out);
}

static inline int	same_sign(int a, int b)
{
	return ((a > 0 && b > 0) || (a < 0 && b < 0) || (a == 0 && b == 0));
}

/* Runs fn(arg, fd) with fd being a pipe, returns everything written. */
static inline char	*capture_fd(void (*fn)(const void *, int), const void *arg)
{
	int		fds[2];
	char	*buf;
	ssize_t	n;
	size_t	len;

	if (pipe(fds) != 0)
		return (NULL);
	fn(arg, fds[1]);
	close(fds[1]);
	buf = calloc(4096, 1);
	len = 0;
	while (buf && len < 4095
		&& (n = read(fds[0], buf + len, 4095 - len)) > 0)
		len += (size_t)n;
	close(fds[0]);
	return (buf);
}

static inline void	free_split(char **tab)
{
	size_t	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

#endif
