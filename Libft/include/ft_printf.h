/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:25:51 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/20 11:47:45 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	ft_putnbr(int n);
void	ft_putnbr_u(unsigned int n);
int		ft_intlen_u(unsigned int i);
int		ft_print(va_list ap, char c);
int		ft_print_2(va_list ap, char c);
int		is_valid(va_list ap, const char *format);
int		ft_hex_len(unsigned int n, int i);
int		ft_hex_len_ptr(unsigned long long n, int i);
int		ft_intlen(int i);
void	ft_fill_hex_ptr(unsigned long long n);
void	ft_fill_hex(unsigned int n);
void	ft_fill_hex_up(unsigned int n);
char	ft_convert_hex(int nb);

#endif
