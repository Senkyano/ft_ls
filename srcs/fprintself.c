/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintself.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 23:39:35 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/16 14:27:11 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int		charprint(const int fd, va_list args);
int		strprint(const int fd, va_list args);
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
