#pragma once
#ifndef __RITHYLIB_H__
# define __RITHYLIB_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>

int		fprintfSelf(const int fd, const char *str, ...);
bool	isspecialchar(char c);
bool	containSpecial(char *str);

int		charprint(const int fd, va_list args);
int		strprint(const int fd, va_list args);
int		numberIntprint(const int fd, va_list args);
void	printOption(const int fd, const char option, int *lenght, va_list args);

char	*strdupself(const char *src);

#endif
