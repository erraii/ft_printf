/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 11:19:24 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/05 20:01:41 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
size_t	ft_print_idu(long n);
size_t	ft_print_hex(unsigned long n, char c);
size_t	ft_print_p(uintptr_t addr, int first);
size_t	ft_prints(char *str);
size_t	ft_printc(int c);

#endif