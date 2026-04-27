/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:57:27 by ecakiray          #+#    #+#             */
/*   Updated: 2026/04/27 16:40:00 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
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

static size_t	ft_print_i_d(int n)
{
	long	long_nb;
	size_t	size;

	long_nb = n;
	size = 0;
	ft_putdigit(long_nb, &size);
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
			else if (*toprint == 'd' || *toprint == 'i')
			{
				total_char += ft_print_i_d(va_arg(ap, int));
				toprint++;
			}
		}
		if (*toprint)
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
// 	ret = ft_printf("My first string\n");
// 	printf("%d ",ret);
// 	ret = ft_printf("%c", '\n');
// 	printf("%d ",ret);
// 	ret = ft_printf("%s", "My first string as arg\n");
// 	printf("%d ",ret);
// 	ret = ft_printf("Just wanna print percentage sign: %% \n");
// 	printf("%d ",ret);
// 	ret = ft_printf(" NULL %s NULL ", NULL);
// 	printf("%d ",ret);
// 	ret = ft_printf("%d ", 2147483647);
// 	printf("%d ",ret);
// 	ret = ft_printf("%i ", -2147483648);
// 	printf("%d ",ret);
// 	return (0);
// }
