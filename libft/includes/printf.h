/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:11:58 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/14 19:05:42 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include "libft.h"

int		arg_int(int nbr);
int		arg_str(char *str);
int		ft_printf(const char *format_str, ...);
int		arg_hex(unsigned long long nbr, char casing);
int		arg_unsigned_int(unsigned int nbr);

char	*ft_itoa_unsigned(unsigned int n);

#endif
