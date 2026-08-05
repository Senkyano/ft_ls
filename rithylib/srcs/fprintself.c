/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintself.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 23:39:35 by rihoy             #+#    #+#             */
/*   Updated: 2026/08/05 23:22:10 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rithylib.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int		charprint(const int fd, va_list args);
int		strprint(const int fd, va_list args);
int		numberIntprint(const int fd, va_list args);
void	printOption(const int fd, const char option, int *lenght, va_list args);

int	fprintfSelf(const int fd, const char *str, ...) {
	int	length = 0;
	va_list	args;

	if (fd < 1)
		return (-1);

	va_start(args, str);
	while (*str != 0) {
		if (*str == '%' && str[1]) {
			printOption(fd, str[1], &length, args);
			str++;
		} else {
			if (write(fd, str, 1) == -1) {
				perror("ls: fprintfSelf write error");
				return (-1);
			}
			length += 1;
		}
		str++;
	}
	
	va_end(args);
	return (length);
}

typedef int	(*t_func_print)(const int ,va_list);

void	printOption(const int fd,
					const char option,
					int *lenght,
					va_list args) {

	static const t_func_print table[256] = {
		['c'] = charprint,
		['s'] = strprint,
		['d'] = numberIntprint,
	};
		
	if (table[(unsigned char)option] != NULL) {
		int ret = table[(unsigned char)option](fd, args);

		if (ret != -1)
			*lenght += ret;
	} else {
		int percent = '%';
		if (write(fd, &percent, 1) != -1)
			*lenght += 1;
		if (write(fd, &option, 1) != -1)
			*lenght += 1; 
	}
}

#include <limits.h>

size_t	lenNumber(int x, int lenghtBase) {
	size_t	lenstr = 0;

	if (x == 0)
		return (1);
	if (x < 0) {
		if (x == INT_MIN)
			x += 1;
		x = -x;
		lenstr++;
	}
	
	while (x) {
		x /= lenghtBase;
		lenstr++;
	}

	return (lenstr);
}

int	numberIntprint(const int fd, va_list args) {
	int		x = va_arg(args, int);
	size_t	stringlen = lenNumber(x, 10);
	char	numberstr[12] = {0};

	if (stringlen > 11)
		return (0);
	if (x < 0) {
		numberstr[0] = '-';
		if (x == INT_MIN)
			return (fprintfSelf(fd, "%s", "-2147483648"));
		x = -x;
	}

	stringlen--;
	while (x > 9) {
		numberstr[stringlen] = ('0' + (x % 10));
		stringlen--;
		x /= 10;
	}

	numberstr[stringlen] = ('0' + (x % 10));

	return (fprintfSelf(fd, "%s", numberstr));
}

int strprint(const int fd, va_list args) {
	char *str = va_arg(args, char *);
	int	lenght = 0;

	if (!str)
		str = "(null)";
	while (str[lenght])
		lenght++;

	int	ret = write(fd, str, lenght);
	if (ret == -1)
		perror("Error: strprint write");
	return (ret);
}

int	charprint(const int fd, va_list args) {
	char c = va_arg(args, int);
	int	error = write(fd, &c, 1);

	if (error == -1)
		perror("ls: write error");
	return (error);
}
