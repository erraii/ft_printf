/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:57:27 by ecakiray          #+#    #+#             */
/*   Updated: 2026/04/30 13:45:24 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h> 
//void va_start(va_list ap, last);
//type va_arg(va_list ap, type);
//void va_end(va_list ap);
//void va_copy(va_list dest, va_list src);
//Your function has to handle the following conversions: cspdiuxX%
//++ %c (single char)
//++ %s (string)
// %p  void - hexadecimal format
// %d decimal base
// %i integer base 10
// %u unsigned decimal
// %x hexadecimal lowercase - base 16
// %X hexadecimal uppercase - base 16
//++ %% percentage sign
//Your libftprintf.a has to be created at the root of your repository

static void	ft_puthex(unsigned long nb, size_t *size, char c)
{
	char	to_print;
	char	*hex;
	char	type;

	type = c;
	if (type == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (nb > 15)
		ft_puthex (nb / 16, size, type);
	to_print = *(hex + (nb % 16));
	write(1, &to_print, 1);
	(*size)++;
}

static void	ft_putdigit(long nb, size_t *size)
{
	char	c;

	if (nb < 0)
	{
		write(1, "-", 1);
		(*size)++;
		nb *= -1;
	}
	if (nb > 9)
		ft_putdigit (nb / 10, size);
	c = 48 + (nb % 10);
	write(1, &c, 1);
	(*size)++;
}

static size_t	ft_print_i_d_u(long n)
{
	size_t		size;

	size = 0;
	ft_putdigit(n, &size);
	return (size);
}

static size_t	ft_print_hex(unsigned long n, char c)
{
	size_t		size;

	size = 0;
	ft_puthex(n, &size, c);
	return (size);
}

static size_t	ft_print_p(void *p)
{
	size_t		size;

	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	size = 2;
	write(1, "0x", 2);
	ft_puthex((uintptr_t)p, &size, 'x');
	return (size);
}

static size_t	ft_prints(char *str)
{
	size_t	length;
	char	*to_write;

	length = 0;
	if (!str)
		to_write = "(null)";
	else
		to_write = str;
	while (*to_write)
	{
		write(1, to_write, 1);
		to_write++;
		length++;
	}
	return (length);
}

static size_t	ft_printc(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printf(const char *string, ...)
{
	char	*toprint;
	size_t	total_char;
	// this is our list
	va_list	ap;

	// the start of the list is string
	va_start(ap, string);
	toprint = (char *)string;
	total_char = 0;
	while (*toprint)
	{
		if (*toprint == '%')
		{
			toprint++;
			if (*toprint == 's')
			{
				total_char += ft_prints(va_arg(ap, char *));
				toprint++;
			}
			else if (*toprint == 'c')
			{
				total_char += ft_printc(va_arg(ap, int));
				toprint++;
			}
			else if (*toprint == '%')
			{
				total_char++;
				write(1, toprint, 1);
				toprint++;
			}
			else if (*toprint == 'd' || *toprint == 'i' || *toprint == 'u')
			{
				if (*toprint == 'u')
					total_char += ft_print_i_d_u((long)va_arg(ap, unsigned int));
				else
					total_char += ft_print_i_d_u((long)va_arg(ap, int));
				toprint++;
			}
			else if (*toprint == 'x' || *toprint == 'X')
			{
				total_char += ft_print_hex(va_arg(ap, unsigned int), *toprint);
				toprint++;
			}
			else if (*toprint == 'p')
			{
				total_char += ft_print_p(va_arg(ap, void *));
				toprint++;
			}
		}
		else if (*toprint)
		{
			total_char++;
			write(1, toprint, 1);
			toprint++;
		}		
	}
	return (total_char);
}
// int	main ()
// {
// 	int	ret;
// 	// ret = ft_printf("My first string\n");
// 	// printf("%d ",ret);
// 	// ret = ft_printf("%c", '\n');
// 	// printf("%d ",ret);
// 	// ret = ft_printf("%s", "My first string as arg\n");
// 	// printf("%d ",ret);
// 	// ret = ft_printf("Just wanna print percentage sign: %% \n");
// 	// printf("%d ",ret);
// 	// ret = ft_printf(" NULL %s NULL ", NULL);
// 	// printf("%d ",ret);
// 	// ret = ft_printf("%d ", 2147483647);
// 	// printf("%d ",ret);
// 	// ret = ft_printf("%i ", -2147483648);
// 	// printf("%d ",ret);
// 	// ret = ft_printf("%u ", 9223372036854775807);
// 	// printf("%d ",ret);
// 	// printf("%lu\n", LONG_MAX);
// 	// printf("%lu\n", LONG_MIN);
// 	// printf("%lu\n", ULONG_MAX);
// 	// printf("%lld\n", 9223372036854775807LL);
// 	ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
// 	//printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
// 	//printf(" %p %p ", 0, 0);

// 	return (0);
// }
