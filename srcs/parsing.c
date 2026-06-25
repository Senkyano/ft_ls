/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:29:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/25 17:16:00 by rihoy            ###   ########.fr       */
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
		(*list) = new_node;
		return (new_node);
	}
	while (tmp->nextFile)
		tmp = tmp->nextFile;
	tmp->nextFile = new_node;
	return (new_node);
}

void	removeElement(t_info_inode **list, void *remove) {
	t_info_inode	*tmp;
	t_info_inode	*prev;

	if (!list || !remove || !(*list))
		return ;

	tmp = *list;
	prev = NULL;
	while (tmp != NULL && tmp != (t_info_inode *)remove) {
		prev = tmp;
		tmp = tmp->nextFile;
	}

	if (!tmp)
		return ;

	if (!prev)
		(*list) = tmp->nextFile;
	else
		prev->nextFile = tmp->nextFile;

	free(tmp);
}

void	seeInfo(t_info_ls *infoLs) {
	fprintfSelf(2, "Attribue Long format: %s\n",
		(infoLs->attrLs & ATTR_LONGFORMAT ? "vraie" : "faux"));
	fprintfSelf(2, "Attribue Recursive: %s\n",
		(infoLs->attrLs & ATTR_RECURSIVE ? "vraie" : "faux"));
	fprintfSelf(2, "Attribue Reverse: %s\n",
		(infoLs->attrLs & ATTR_REVERSE ? "vraie" : "faux"));
	fprintfSelf(2, "Attribue Sort by Time: %s\n",
		(infoLs->attrLs & ATTR_SORTBYTIME ? "vraie" : "faux"));
	fprintfSelf(2, "Attribue All: %s\n",
		(infoLs->attrLs & ATTR_ALL ? "vraie" : "faux"));
	
	t_info_inode	*tmp;
	tmp = infoLs->filesList;
	if (!tmp)
		fprintfSelf(2, "Null \n");
	while (tmp) {
		fprintfSelf(2, "file : %s\n", tmp->nameFile);
		tmp = tmp->nextFile;
	}
}
