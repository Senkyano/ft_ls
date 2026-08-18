#pragma once
#ifndef __RITHYLIB_H__
# define __RITHYLIB_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>

/*      File : fprintself.c
*           Main function fprintSelf(int fd, const char *str, ...)
*           Equivalent of fprintf
*/
int		fprintfSelf(const int fd, const char *str, ...);
size_t	lenNumber(int x, int lenghtBase);
int		charprint(const int fd, va_list args);
int		strprint(const int fd, va_list args);
int		numberIntprint(const int fd, va_list args);
void	printOption(const int fd, const char option, int *lenght, va_list args);

/*      File : isspecial.c
*/
bool	isspecialchar(char c);
bool	containSpecial(char *str);

/*      File : strlen.c
*/
size_t	strlenSelf(char *str);

/*      File : strdupself.c
*/
char	*strdupself(const char *src);

/*      File : strjoin.c
*/
char	*strjoin_save(char *str, char *str2);
char	*joinstrwsep(char *str1, char *sep, char *str2);

/*		File : datalist
*/
typedef struct	s_voidlist {
	void		*data;
	t_voidlist	*next;
}	t_voidlist;
void	list_addback(t_voidlist **list, void *data);



#endif
