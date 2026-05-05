/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:57:27 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/05 19:31:43 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_format(char **toprint, va_list ap)
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
	// ret = ft_printf("My first string\n");
	// printf("%d ",ret);
	// ret = ft_printf("%c", '\n');
	// printf("%d ",ret);
	// ret = ft_printf("%s", "My first string as arg\n");
	// printf("%d ",ret);
	// ret = ft_printf("Just wanna print percentage sign: %% \n");
	// printf("%d ",ret);
	// ret = ft_printf(" NULL %s NULL ", NULL);
	// printf("%d ",ret);
	// ret = ft_printf("%d ", 2147483647);
	// printf("%d ",ret);
	// ret = ft_printf("%i ", -2147483648);
	// printf("%d ",ret);
	// ret = ft_printf("%u ", 9223372036854775807);
	// printf("%d ",ret);
	// printf("%lu\n", LONG_MAX);
	// printf("%lu\n", LONG_MIN);
	// printf("%lu\n", ULONG_MAX);
	// printf("%lld\n", 9223372036854775807LL);
	// ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%
	//x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 
	// 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", 
	//-42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	// printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%
	// x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%",
	// 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", 
	//-42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	// printf(" %p %p ", 0, 0);
	// ft_printf("%u \n", LONG_MAX);
	// ft_printf("%x \n", LONG_MAX);
	// 	ft_printf("%d \n", 0.12);
	// 	printf("%d", 0.12);
	// 	return (0);
// }
