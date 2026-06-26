/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:32:44 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/26 15:41:49 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef _LS_H_
# define _LS_H_

typedef struct	s_info_inode t_info_inode;

#define	READ_ALL	'a'
#define RECURSIVE	'R'
#define REVERSE		'r'
#define SORTBYTIME	't'
#define LONGFORMAT	'l'

enum lsAttribute {
	ATTR_ALL		= 1,
	ATTR_RECURSIVE	= 2,
	ATTR_REVERSE	= 4,
	ATTR_SORTBYTIME = 8,
	ATTR_LONGFORMAT = 16,	
};

#define ALL_FLAGS (ATTR_ALL \
	| ATTR_RECURSIVE \
	| ATTR_REVERSE \
	| ATTR_SORTBYTIME \
	| ATTR_LONGFORMAT)

typedef struct	s_info_ls {
	t_info_inode	*filesList;
	int				attrLs;
}   			t_info_ls;

enum fileAttribute {
	ATTR_READ_ONLY	= 1,
	ATTR_HIDDEN		= 2,
	ATTR_SYSTEM		= 4,
	ATTR_EXECUTABLE	= 8,
	ATTR_DIRECTORY	= 16,
	ATTR_STARTDIR	= 32,
};

typedef struct	s_info_inode {
	char			*nameFile;
	char			*fullpath;
	int				attrFile;
	int				depth;
	t_info_inode	*nextFile;
}				t_info_inode;

typedef	int	(*t_func_cmplist)(void *, void *);

void	freeInfoInode(t_info_inode **list);
void	*addBackList(t_info_inode **list, char *name_file);
int		fprintfSelf(const int fd, const char *str, ...);
void	*parsingInfoLs(const int argc, const char **argv, t_info_ls *infoLs);
int		strcmpLs(void *str1, void *str2);
void	*addCmpList(t_info_inode **list, t_info_inode model, t_func_cmplist cmpfunc);

char	*strdupself(const char *src);
void	seeInfo(t_info_ls *infoLs);
#endif