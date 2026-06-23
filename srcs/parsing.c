/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:29:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/23 18:04:38 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "ls.h"

void	setAttr(const char *str, t_info_ls *infoLs) {
	static const int ascii_table[256] = {
		['a'] = ATTR_ALL,
		['r'] = ATTR_REVERSE,
		['R'] = ATTR_RECURSIVE,
		['t'] = ATTR_SORTBYTIME,
		['l'] = ATTR_LONGFORMAT,
	};

	while (*(++str) != '\0') {
		int flag = ascii_table[(unsigned char)*str];
		
		if (!flag) {
			fprintfSelf(2, "ls: invalid option -- '%c'\n", *str);
			// free(list);
			exit(2);
		}

		infoLs->attrLs |= flag;
	}
}

void	*parsingInfoLs(const int argc, const char **argv, t_info_ls *infoLs) {
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			setAttr(argv[i], infoLs);
		} else {
			char	*tmp_name_file;

			tmp_name_file = strdupself(argv[i]);
			if (!tmp_name_file) {
				return (NULL);
			}
			addBackList(&infoLs->filesList, tmp_name_file);
			// free(tmp_name_file);
		}
	}
	return (infoLs->filesList);
}

void	*addCmpList(t_info_inode **list, char *name_file, t_func_cmplist cmpfunc) {
	t_info_inode	*new_node;
	
	if (!list)
		return (NULL);

	new_node = (t_info_inode *)malloc(sizeof(t_info_inode));
	if (!new_node)
		return (NULL);

	new_node->nameFile = name_file;
	new_node->nextFile = NULL;
	t_info_inode	*tmp = *list;
	if (!tmp) {
		tmp = new_node;
		return (new_node);
	}
	while (tmp->nextFile) {
		if (cmpfunc(tmp->nameFile, name_file) > 0) {
			
		}
		tmp = tmp->nextFile;
	}
	return (new_node);
}

void	*addBackList(t_info_inode **list, char *name_file) {
	t_info_inode	*new_node;

	if (!list)
	return (NULL);

	new_node = (t_info_inode *)malloc(sizeof(t_info_inode));
	if (!new_node)
		return (NULL);

	t_info_inode	*tmp = *list;
	new_node->nameFile = name_file;
	new_node->nextFile = NULL;
	if (!tmp) {
		tmp = new_node;
		return (new_node);
	}
	while (tmp->nextFile)
		tmp = tmp->nextFile;
	tmp->nextFile = new_node;
	return (new_node);
}

void	seeInfo(t_info_ls *infoLs) {
	fprintfSelf(2, "Attribue Long format %s\n", (infoLs->attrLs & ATTR_LONGFORMAT ? "vraie" : "faux"));
}
