/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:10:30 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/31 17:41:18 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

static int	printf_arguments(va_list args, char arg, int fd)
{
	int	output_len;

	output_len = 0;
	if (arg == 'c')
		output_len += ft_putchar_fd(va_arg(args, int), fd);
	else if (arg == 's')
		output_len += arg_str(va_arg(args, char *), fd);
	else if (arg == 'i' || arg == 'd')
		output_len += arg_int(va_arg(args, int), fd);
	else if (arg == 'u')
		output_len += arg_unsigned_int(va_arg(args, unsigned int), fd);
	else if (arg == '%')
		output_len += ft_putchar_fd('%', fd);
	else if (arg == 'X' || arg == 'x')
		output_len += arg_hex(va_arg(args, unsigned int), arg);
	else if (arg == 'p')
	{
		output_len += ft_putstr_fd("0x", fd);
		arg = 'x';
		output_len += arg_hex(va_arg(args, unsigned long long), arg);
	}
	return (output_len);
}

int	ft_printf(int fd, const char *format_str, ...)
{
	va_list	args;
	int		output_len;
	int		i;

	va_start(args, format_str);
	i = 0;
	output_len = 0;
	while (format_str[i] != '\0')
	{
		if (format_str[i] != '\0' && format_str[i] != '%')
		{
			ft_putchar_fd(format_str[i], fd);
			output_len++;
			i++;
		}
		if (format_str[i] == '%')
		{
			i++;
			output_len += printf_arguments(args, format_str[i], fd);
			i++;
		}
	}
	va_end(args);
	return (output_len);
}
