#!/usr/bin/env bash
# resolve - libft checker
# Usage: ./resolve/run.sh [-l] [-N] [-h] [function ...]

set -u

RESOLVE_DIR="$(cd "$(dirname "$0")" && pwd)"
LIB_DIR="${LIBFT_DIR:-$(dirname "$RESOLVE_DIR")}"
TESTS_DIR="$RESOLVE_DIR/tests"
BUILD="$RESOLVE_DIR/.build"
TIMEOUT_SEC=10
JOBS="$(sysctl -n hw.ncpu 2> /dev/null || nproc 2> /dev/null || echo 4)"

CC="${CC:-cc}"
USER_FLAGS="-Wall -Wextra -Werror"
SAN_FLAGS="-g -fsanitize=address,undefined -fno-omit-frame-pointer"
TEST_FLAGS="-Wall -Wextra -Werror=implicit-function-declaration -Wno-unused-function"
ALLOWED_EXTERNALS="malloc free write"

PART1="isalpha isdigit isalnum isascii isprint strlen memset bzero memcpy
memmove strlcpy strlcat toupper tolower strchr strrchr strncmp memchr memcmp
strnstr atoi calloc strdup"
PART2="substr strjoin strtrim split itoa strmapi striteri putchar_fd putstr_fd
putendl_fd putnbr_fd"
PART3="lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear
lstiter lstmap"

CHECK_LEAKS=0
CHECK_NORM=1
SELECTED=""

if [ -t 1 ]; then
	GREEN=$'\033[32m'; RED=$'\033[31m'; YELLOW=$'\033[33m'
	GREY=$'\033[90m'; BOLD=$'\033[1m'; RESET=$'\033[0m'
else
	GREEN=""; RED=""; YELLOW=""; GREY=""; BOLD=""; RESET=""
fi

usage() {
	cat <<EOF
Usage: $0 [options] [function ...]

  (no function)   test every function
  strlen ft_split test only these (ft_ prefix optional)
  part1|part2|part3  test one part of the subject

Options:
  -l   also check memory leaks (leaks on macOS, valgrind on Linux)
  -N   skip norminette
  -h   show this help

Env:  LIBFT_DIR=/path/to/libft   (default: parent folder of resolve/)
EOF
}

parse_args() {
	local arg name
	for arg in "$@"; do
		case "$arg" in
			-l) CHECK_LEAKS=1 ;;
			-N) CHECK_NORM=0 ;;
			-h|--help) usage; exit 0 ;;
			part1) SELECTED="$SELECTED $PART1" ;;
			part2) SELECTED="$SELECTED $PART2" ;;
			part3|bonus) SELECTED="$SELECTED $PART3" ;;
			-*) echo "Unknown option: $arg"; usage; exit 2 ;;
			*)
				name="${arg#ft_}"; name="${name%.c}"
				if [ ! -f "$TESTS_DIR/ft_$name.c" ]; then
					echo "No test for ft_$name"; exit 2
				fi
				SELECTED="$SELECTED $name" ;;
		esac
	done
	if [ -z "$SELECTED" ]; then
		SELECTED="$PART1 $PART2 $PART3"
	fi
	SELECTED="$(sort_selected)"
}

# Keeps the subject order and removes duplicates.
sort_selected() {
	local name out="" wanted
	wanted=" $(echo $SELECTED) "
	for name in $PART1 $PART2 $PART3; do
		case "$wanted" in *" $name "*) out="$out $name" ;; esac
	done
	echo "$out"
}

# Compiles every .c of the user's libft twice: with sanitizers (for tests)
# and plain (for forbidden-function and leak checks). Failures are logged.
build_user_lib() {
	local src base
	rm -rf "$BUILD"
	mkdir -p "$BUILD/san" "$BUILD/plain" "$BUILD/err" "$BUILD/bin" "$BUILD/out"
	for src in "$LIB_DIR"/*.c; do
		[ -e "$src" ] || continue
		compile_user_file "$src" &
	done
	wait
	make_archive san
	make_archive plain
}

compile_user_file() {
	local src="$1" base
	base="$(basename "$src" .c)"
	if ! $CC $USER_FLAGS -I"$LIB_DIR" -c "$src" -o "$BUILD/plain/$base.o" \
		2> "$BUILD/err/$base.log"; then
		rm -f "$BUILD/plain/$base.o"
		return
	fi
	$CC $USER_FLAGS $SAN_FLAGS -I"$LIB_DIR" -c "$src" \
		-o "$BUILD/san/$base.o" 2>> "$BUILD/err/$base.log"
}

# Compiles and runs one test, saving its output for test_function.
prepare_test() {
	local name="$1" bin="$BUILD/bin/ft_$1" code
	if ! $CC $TEST_FLAGS $SAN_FLAGS -I"$LIB_DIR" -I"$TESTS_DIR" \
		"$TESTS_DIR/ft_$name.c" "$BUILD/libsan.a" -o "$bin" \
		2> "$BUILD/err/test_$name.log"; then
		rm -f "$bin"
		return
	fi
	(cd "$BUILD" && ASAN_OPTIONS=detect_leaks=0 run_with_timeout "$bin") \
		> "$BUILD/out/$name.txt" 2>&1
	code=$?
	echo "$code" > "$BUILD/out/$name.code"
}

# Runs norminette once, then every selected test, JOBS at a time.
prepare_all() {
	local name running=0
	if [ $CHECK_NORM -eq 1 ] && command -v norminette > /dev/null 2>&1; then
		(cd "$LIB_DIR" && norminette ./*.c ./*.h > "$BUILD/norm.txt" 2>&1)
	fi
	for name in $SELECTED; do
		[ -n "$(find_source "$name")" ] || continue
		prepare_test "$name" &
		running=$((running + 1))
		if [ $running -ge "$JOBS" ]; then
			wait
			running=0
		fi
	done
	wait
}

make_archive() {
	local dir="$BUILD/$1"
	rm -f "$BUILD/lib$1.a"
	if ls "$dir"/*.o > /dev/null 2>&1; then
		ar rcs "$BUILD/lib$1.a" "$dir"/*.o 2> /dev/null
	else
		ar rcs "$BUILD/lib$1.a" 2> /dev/null || : > "$BUILD/lib$1.a"
	fi
}

find_source() {
	local name="$1"
	if [ -f "$LIB_DIR/ft_$name.c" ]; then
		echo "ft_$name"
	elif [ -f "$LIB_DIR/ft_${name}_bonus.c" ]; then
		echo "ft_${name}_bonus"
	fi
}

indent() {
	sed 's/^/      /'
}

run_with_timeout() {
	perl -e 'alarm shift @ARGV; exec @ARGV or die "exec failed\n"' \
		"$TIMEOUT_SEC" "$@"
}

# Prints external symbols used by an object that the subject forbids.
forbidden_calls() {
	local obj="$1" sym out=""
	for sym in $(nm -u "$obj" 2> /dev/null | awk '{print $NF}'); do
		sym="${sym#_}"
		case "$sym" in
			ft_*|__stack_chk_*|_*) continue ;;
		esac
		case " $ALLOWED_EXTERNALS " in
			*" $sym "*) continue ;;
		esac
		out="$out $sym"
	done
	echo "${out# }"
}

check_leaks() {
	local name="$1" bin="$BUILD/bin/ft_${1}_plain" out
	if ! $CC $TEST_FLAGS -g -I"$LIB_DIR" -I"$TESTS_DIR" \
		"$TESTS_DIR/ft_$name.c" "$BUILD/libplain.a" -o "$bin" 2> /dev/null; then
		echo "build failed"; return
	fi
	if command -v leaks > /dev/null 2>&1; then
		out="$(MallocStackLogging=1 run_with_timeout leaks --atExit -- "$bin" 2>&1)"
		pkill -9 -f "$bin" 2> /dev/null
		if echo "$out" | grep -q " 0 leaks for 0 total leaked bytes"; then
			echo ""
		elif ! echo "$out" | grep -q "leaks for"; then
			echo "leak check failed (leaks could not attach, try outside any sandbox)"
		else
			echo "$out" | grep -E "leaks for|Leak:|ft_" | head -n 12
		fi
	elif command -v valgrind > /dev/null 2>&1; then
		out="$(run_with_timeout valgrind --leak-check=full --error-exitcode=42 "$bin" 2>&1)"
		[ $? -eq 42 ] && echo "$out" | grep -E "definitely|indirectly|by 0x" | head -n 12
	else
		echo "no leak tool found (install valgrind)"
	fi
}

# Prints the norminette errors of one file (from the shared norm.txt).
norm_errors() {
	[ -f "$BUILD/norm.txt" ] || return
	sed $'s/\033\\[[0-9;]*m//g' "$BUILD/norm.txt" | awk -v f="$1" '
		/^[^ ]+: (OK|Error)!/ { cur = $1; sub(/:$/, "", cur); sub(/^\.\//, "", cur); next }
		cur == f && /^Error/ { print }'
}

print_status() {
	local color="$1" status="$2" name="$3" detail="$4"
	printf "  %s%-16s%s %s%-14s%s %s\n" "$BOLD" "ft_$name" "$RESET" \
		"$color" "$status" "$RESET" "$detail"
}

# Tests one function; updates the global counters.
test_function() {
	local name="$1" src bin log out code result passed total extra
	src="$(find_source "$name")"
	if [ -z "$src" ]; then
		print_status "$GREY" "MISSING" "$name" ""
		N_MISSING=$((N_MISSING + 1)); return
	fi
	if [ ! -f "$BUILD/plain/$src.o" ] || [ -s "$BUILD/err/$src.log" ]; then
		print_status "$RED" "COMPILE ERROR" "$name" "($src.c)"
		head -n 15 "$BUILD/err/$src.log" | indent
		N_KO=$((N_KO + 1)); return
	fi
	bin="$BUILD/bin/ft_$name"
	log="$BUILD/err/test_$name.log"
	if [ ! -x "$bin" ]; then
		print_status "$RED" "BUILD ERROR" "$name" "(prototype in libft.h or missing helper?)"
		grep -E "error|undefined|Undefined|_ft_" "$log" | head -n 8 | indent
		N_KO=$((N_KO + 1)); return
	fi
	out="$(cat "$BUILD/out/$name.txt")"
	code="$(cat "$BUILD/out/$name.code")"
	result="$(echo "$out" | grep '^RESULT ' | tail -n 1)"
	if [ $code -eq 142 ]; then
		print_status "$RED" "TIMEOUT" "$name" "(infinite loop? > ${TIMEOUT_SEC}s)"
		echo "$out" | grep "KO" | head -n 10 | indent
		N_KO=$((N_KO + 1)); return
	fi
	if echo "$out" | grep -q "ERROR: AddressSanitizer\|SEGV\|Segmentation"; then
		print_status "$RED" "CRASH" "$name" ""
		echo "$out" | grep "KO" | head -n 10 | indent
		echo "$out" | grep -E "ERROR: AddressSanitizer|SUMMARY|^ *#[0-4] " | grep -v "#[0-9]* .* in start" \
			| sed 's/ (.*)$//' | head -n 8 | indent
		N_KO=$((N_KO + 1)); return
	fi
	if [ -z "$result" ]; then
		print_status "$RED" "CRASH" "$name" "(exit code $code)"
		echo "$out" | tail -n 10 | indent
		N_KO=$((N_KO + 1)); return
	fi
	passed="$(echo "$result" | awk '{print $2}')"
	total="$(echo "$result" | awk '{print $3}')"
	if [ "$passed" != "$total" ]; then
		print_status "$RED" "KO" "$name" "$passed/$total"
		echo "$out" | grep "KO" | head -n 15 | sed 's/^ *//' | indent
		N_KO=$((N_KO + 1)); return
	fi
	print_status "$GREEN" "OK" "$name" "$passed/$total"
	N_OK=$((N_OK + 1))
	report_warnings "$name" "$src" "$out"
}

report_warnings() {
	local name="$1" src="$2" out="$3" forbidden norm leaks
	if echo "$out" | grep -q "runtime error"; then
		echo "      ${YELLOW}undefined behavior:${RESET}"
		echo "$out" | grep "runtime error" | sed 's/^.*runtime error/runtime error/' \
			| sort -u | head -n 3 | indent
		N_WARN=$((N_WARN + 1))
	fi
	forbidden="$(forbidden_calls "$BUILD/plain/$src.o")"
	if [ -n "$forbidden" ]; then
		echo "      ${YELLOW}forbidden function(s):${RESET} $forbidden"
		N_WARN=$((N_WARN + 1))
	fi
	if [ $CHECK_NORM -eq 1 ] && command -v norminette > /dev/null 2>&1; then
		norm="$(norm_errors "$src.c")"
		if [ -n "$norm" ]; then
			echo "      ${YELLOW}norminette:${RESET}"
			echo "$norm" | head -n 5 | indent
			N_WARN=$((N_WARN + 1))
		fi
	fi
	if [ $CHECK_LEAKS -eq 1 ]; then
		leaks="$(check_leaks "$name")"
		if [ -n "$leaks" ]; then
			echo "      ${YELLOW}leaks:${RESET}"
			echo "$leaks" | indent
			N_WARN=$((N_WARN + 1))
		fi
	fi
}

check_header() {
	if [ ! -f "$LIB_DIR/libft.h" ]; then
		echo "${RED}libft.h not found in $LIB_DIR${RESET}"
		echo "Create it first: every test includes it to get your prototypes."
		exit 1
	fi
}

main() {
	local name
	parse_args "$@"
	check_header
	N_OK=0; N_KO=0; N_MISSING=0; N_WARN=0
	echo "${BOLD}resolve${RESET} - testing $LIB_DIR"
	build_user_lib
	prepare_all
	for name in $SELECTED; do
		case " $PART1 " in *" $name "*) section "Part 1 - Libc" ;; esac
		case " $PART2 " in *" $name "*) section "Part 2 - Additional" ;; esac
		case " $PART3 " in *" $name "*) section "Part 3 - Linked list" ;; esac
		test_function "$name"
	done
	if [ $CHECK_NORM -eq 1 ] && [ -n "$(norm_errors libft.h)" ]; then
		echo; echo "${YELLOW}norminette libft.h:${RESET}"
		norm_errors libft.h | head -n 5 | indent
		N_WARN=$((N_WARN + 1))
	fi
	echo
	printf "%s%d OK%s  %s%d KO%s  %s%d missing%s  %s%d warning(s)%s\n" \
		"$GREEN" "$N_OK" "$RESET" "$RED" "$N_KO" "$RESET" \
		"$GREY" "$N_MISSING" "$RESET" "$YELLOW" "$N_WARN" "$RESET"
	[ $N_KO -eq 0 ]
}

CURRENT_SECTION=""
section() {
	if [ "$CURRENT_SECTION" != "$1" ]; then
		CURRENT_SECTION="$1"
		echo; echo "${BOLD}$1${RESET}"
	fi
}

main "$@"
