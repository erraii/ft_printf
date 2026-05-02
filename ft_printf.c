/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:57:27 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/01 00:12:11 by ecakiray         ###   ########.fr       */
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


static size_t	ft_print_idu(long n)
{
	size_t		size;
	char		c;

	size = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		size++;
		n *= -1;
	}
	if (n > 9)
		size += ft_print_idu (n / 10);
	c = 48 + (n % 10);
	write(1, &c, 1);
	size++;
	return (size);
}

static size_t	ft_print_hex(unsigned long n, char c)
{
	size_t		size;
	char		*hex;

	size = 0;
	if (c == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (n > 15)
		size += ft_print_hex (n / 16, c);
	write(1, (hex + (n % 16)), 1);
	size++;
	return (size);
}

static size_t	ft_print_p(uintptr_t addr, int base)
{
	size_t		size;
	char		*hex;

	hex = "0123456789abcdef";
	size = 0;
	if (!addr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	if (base == 0)
	{
		size = 2;
		write(1, "0x", 2);
	}
	if (addr > 15)
		size += ft_print_p(addr / 16, 1);
	write(1, (hex + (addr % 16)), 1);
	size++;
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

int	ft_printf_format(char **toprint, va_list ap)
{
	size_t	tot_chr;

	tot_chr = 0;
	(*toprint)++;
	if (**toprint == 's')
		tot_chr += ft_prints(va_arg(ap, char *));
	else if (**toprint == 'c')
		tot_chr += ft_printc(va_arg(ap, int));
	else if (**toprint == '%')
		tot_chr += ft_printc('%');
	else if (**toprint == 'd' || **toprint == 'i' || **toprint == 'u')
	{
		if (**toprint == 'u')
			tot_chr += ft_print_idu((long)va_arg(ap, unsigned int));
		else
			tot_chr += ft_print_idu((long)va_arg(ap, int));
	}
	else if (**toprint == 'x' || **toprint == 'X')
		tot_chr += ft_print_hex(va_arg(ap, unsigned int), **toprint);
	else if (**toprint == 'p')
		tot_chr += ft_print_p((uintptr_t)va_arg(ap, void *), 0);
	(*toprint)++;
	return (tot_chr);
}

int	ft_printf(const char *string, ...)
{
	char	*toprint;
	size_t	tot_chr;
	va_list	ap;

	va_start(ap, string);
	toprint = (char *)string;
	tot_chr = 0;
	while (*toprint)
	{
		if (*toprint == '%')
			tot_chr += ft_printf_format(&toprint, ap);
		else if (*toprint)
		{
			tot_chr += ft_printc(*toprint);
			toprint++;
		}		
	}
	va_end(ap);
	return (tot_chr);
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
