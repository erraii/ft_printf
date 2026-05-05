*This project has been created as part of the 42 curriculum by ecakiray.*

# ft_printf

## Description

`ft_printf` is a custom implementation of the C standard library function `printf()`.
The goal of the project is to understand variadic functions in C and to build a small formatted-output library that can be reused in later 42 projects.

The project creates a static library named:

```bash
libftprintf.a
```

The main function has the following prototype:

```c
int ft_printf(const char *str, ...);
```

This implementation does not reproduce the original `printf()` buffer management. It focuses on parsing a format string, reading a variable number of arguments, printing the requested values, and returning the number of printed characters.

## Supported Conversions

The mandatory part handles the following conversions:

| Conversion | Description |
| --- | --- |
| `%c` | Prints a single character |
| `%s` | Prints a string |
| `%p` | Prints a pointer address in hexadecimal format |
| `%d` | Prints a signed decimal integer |
| `%i` | Prints a signed integer in base 10 |
| `%u` | Prints an unsigned decimal integer |
| `%x` | Prints a hexadecimal number in lowercase |
| `%X` | Prints a hexadecimal number in uppercase |
| `%%` | Prints a percent sign |

## Instructions

### Compilation

To compile the library, run:

```bash
make
```

This creates the static library `libftprintf.a` at the root of the repository.

### Cleaning object files

```bash
make clean
```

### Cleaning object files and the library

```bash
make fclean
```

### Recompiling from scratch

```bash
make re
```

## Usage Example

After compiling the library, include the header file in your C file:

```c
#include "ft_printf.h"

int main(void)
{
	ft_printf("Hello %s! Number: %d\n", "42", 42);
	return (0);
}
```

Compile your program with the library:

```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o test
```

Then run it:

```bash
./test
```

## Project Structure

```text
.
├── Makefile
├── README.md
├── ft_printf.c
├── ft_printf.h
└── ft_types.c
```

- `ft_printf.c` contains the main `ft_printf()` function and the format-conversion dispatcher.
- `ft_types.c` contains helper functions for printing characters, strings, integers, hexadecimal numbers, and pointers.
- `ft_printf.h` contains the function prototypes and required includes.
- `Makefile` compiles the source files and creates `libftprintf.a`.

## Algorithm and Data Structure Explanation

The project uses a simple sequential parsing algorithm.

`ft_printf()` receives a format string and uses a pointer to move through it character by character. When the current character is not `%`, the character is printed directly with `write()` and the printed-character counter is increased.

When `%` is found, the parser moves to the next character and checks which conversion is requested. According to the conversion type, the correct argument is extracted from the `va_list` with `va_arg()` and sent to the matching helper function.

The main data used by the algorithm is:

- A `char *` pointer used to traverse the format string.
- A `va_list` used to access variadic arguments.
- A `size_t` counter used to store the number of printed characters.

No complex data structure is needed because the format string can be processed from left to right. This approach is suitable for the mandatory requirements because each conversion is independent and can be handled immediately when it is found.

For number printing, recursive functions are used. The number is divided by its base until the highest digit is reached, then each digit is written in the correct order. Decimal numbers use base 10, while hexadecimal and pointer values use base 16.

This design keeps the code modular: `ft_printf()` handles parsing, while the helper functions handle the actual output of each data type.

## Resources

Useful references for this project:

- `man 3 printf`
- `man 3 stdarg`
- `man 2 write`
- C documentation about variadic functions: `va_start`, `va_arg`, `va_copy`, and `va_end`
- 42 project subject: `ft_printf`

## AI Usage

AI was used to help write and structure this README file according to the project subject requirements.
It was not used to generate the core project logic. The implementation of `ft_printf()`, the helper functions, and the Makefile should be understood, tested, and explained by the student during peer evaluation.
