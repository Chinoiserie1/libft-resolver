# my-libft

My clean, from-scratch rewrite of the 42 **libft**.

The `resolve/` folder is a tester: one command checks every function you
have written so far.

---

## Layout

```
my-libft/
├── libft.h          ← create first (prototypes + t_list)
├── Makefile         ← create (all, clean, fclean, re, no relink)
├── ft_*.c           ← one function per file
└── resolve/         ← the tester (not submitted)
    ├── run.sh       ← the command to run
    └── tests/       ← one test file per function
```

---

## Workflow

### 1. Create `libft.h`

The tester includes **your** `libft.h` to get your prototypes, so nothing
compiles without it. It needs:

- the includes (`<stddef.h>`, `<stdlib.h>`, `<unistd.h>`)
- the `t_list` struct (`content` + `next`)
- the prototype of every function you have written

### 2. Write a function

Use one file per function: `ft_strlen.c`, `ft_split.c`, and so on.
List functions can be named either `ft_lstnew.c` or `ft_lstnew_bonus.c`.
The tester accepts both.

The only external functions you may call are `malloc`, `free` and `write`.

### 3. Test it

Run from `my-libft/`:

```bash
./resolve/run.sh              # every function
./resolve/run.sh strlen       # a single function (ft_ prefix optional)
./resolve/run.sh split itoa   # several functions
./resolve/run.sh part1        # one part: part1, part2, part3 (or bonus)
./resolve/run.sh -l split     # also check for memory leaks
./resolve/run.sh -N           # skip norminette
./resolve/run.sh -h           # help
```

Functions you haven't written yet show as `MISSING` and don't stop the
other tests, so you can start testing after your first function.

### 4. Fix and repeat

Read the `KO` line, fix your code, then run `./resolve/run.sh <function>`
again.

---

## Reading the output

```
Part 1 - Libc
  ft_strlen        OK             7/7
  ft_strlcat       KO             140/144
      KO (line 47) dst="abc" src="xyz" size=4: returned 6, expected 7
  ft_strdup        CRASH
      ERROR: AddressSanitizer: heap-buffer-overflow ...
      #1 0x... in ft_strdup ft_strdup.c:8
  ft_itoa          MISSING

12 OK  2 KO  29 missing  1 warning(s)
```

| Status | Meaning |
|--------|---------|
| `OK` | every case passes |
| `KO` | at least one case is wrong; the line shows the input, your result and the expected result |
| `CRASH` | segfault, buffer overflow, double free… The AddressSanitizer trace gives the file and line |
| `TIMEOUT` | the function never returns (infinite loop?) |
| `COMPILE ERROR` | your `.c` doesn't compile with `-Wall -Wextra -Werror` |
| `BUILD ERROR` | the test doesn't compile. Either the prototype in `libft.h` is missing or different, or your function calls one you haven't written yet (e.g. `ft_strdup` calling `ft_strlen`) |
| `MISSING` | `ft_<name>.c` doesn't exist yet |

Warnings show in yellow under an `OK` function:

- **undefined behavior**: UBSan found UB, such as `int` overflow in `ft_atoi`
- **forbidden function(s)**: a call to something other than `malloc`, `free` or `write`
- **norminette**: norm errors in that file (plus `libft.h` at the end)
- **leaks** (with `-l`): memory that is never freed. This uses `leaks` on
  macOS and `valgrind` on Linux.

The exit code is `0` only when no function is `KO`.

---

## What the tester checks

- **Part 1**: compares your results with the real libc (`isalpha`,
  `memmove`, `strncmp`, `atoi`…) on edge cases such as `n = 0`, overlapping
  memory, `unsigned char` conversion, `INT_MIN` and `calloc` overflow.
- **Part 2**: compares with hand-written expected results. The `put*_fd`
  output is captured through a pipe.
- **Part 3**: builds lists and checks links, how many times `del` is
  called, that `*lst` is set to `NULL`, and so on.
- Every file is compiled like at 42 (`cc -Wall -Wextra -Werror`), then run
  with AddressSanitizer and UBSan.

It does **not** check your `Makefile`. Test it by hand:

```bash
make && make      # the second make must not recompile anything (no relink)
make clean && make fclean && make re
```

Build files go to `resolve/.build/`, which is git-ignored.

---

## Suggested order

1. `libft.h` and `Makefile`
2. Characters: `isalpha`, `isdigit`, `isalnum`, `isascii`, `isprint`, `toupper`, `tolower`
3. Memory: `memset`, `bzero`, `memcpy`, `memmove`, `memchr`, `memcmp`
4. Strings: `strlen`, `strlcpy`, `strlcat`, `strchr`, `strrchr`, `strncmp`, `strnstr`
5. `atoi`, `calloc`, `strdup`
6. Part 2: `substr`, `strjoin`, `strtrim`, `split`, `itoa`, `strmapi`, `striteri`, `put*_fd`
7. Part 3 (bonus): the `ft_lst*` functions

`strdup`, `substr` and `strjoin` usually call `ft_strlen`, so write it early.

---

## Before submitting

- [ ] `./resolve/run.sh -l`: everything `OK`, no warnings
- [ ] `norminette *.c libft.h`: no errors
- [ ] the `Makefile` doesn't relink
- [ ] the submission repo contains **only** your files, without `resolve/`
- [ ] the submitted README follows the subject's format (first line in italics:
      *This project has been created as part of the 42 curriculum by &lt;login&gt;.*)
