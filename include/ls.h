/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:32:44 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/23 18:04:56 by rihoy            ###   ########.fr       */
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
};

typedef struct	s_info_inode {
	char			*nameFile;
	int				attrFile;
	t_info_inode	*inDir;
	t_info_inode	*nextFile;
}				t_info_inode;

typedef	int	(*t_func_cmplist)(void *, void *);

void	*addBackList(t_info_inode **list, char *name_file);
int		fprintfSelf(const int fd, const char *str, ...);
void	*parsingInfoLs(const int argc, const char **argv, t_info_ls *infoLs);

char	*strdupself(const char *src);
void	seeInfo(t_info_ls *infoLs);
#endif