/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:11:58 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/31 17:42:31 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include "libft.h"

int		arg_int(int nbr, int fd);
int		arg_str(char *str, int fd);
int		ft_printf(int fd, const char *format_str, ...);
int		arg_hex(unsigned long long nbr, char casing);
int		arg_unsigned_int(unsigned int nbr, int fd);

char	*ft_itoa_unsigned(unsigned int n);

#endif
