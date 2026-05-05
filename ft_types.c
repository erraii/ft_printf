/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:09:45 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/05 19:25:16 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_idu(long n)
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

size_t	ft_print_hex(unsigned long n, char c)
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

size_t	ft_print_p(uintptr_t addr, int first)
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
	if (first == 0)
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

size_t	ft_prints(char *str)
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

size_t	ft_printc(int c)
{
	write(1, &c, 1);
	return (1);
}
