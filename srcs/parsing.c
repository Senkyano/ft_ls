/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:29:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/07/09 16:05:58 by rihoy            ###   ########.fr       */
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
			freeInfoInode(&infoLs->filesList);
			exit(2);
		}

		infoLs->attrLs |= flag;
	}
}

void	*parsingInfoLs(const int argc, const char **argv, t_info_ls *infoLs) {
	t_info_inode	model = {0};

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			setAttr(argv[i], infoLs);
		}
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			infoLs->attrLs |= ATTR_STARTDIR;
			model.nameFile = strdupself(argv[i]);
			model.depth = 0;
			
			if (!model.nameFile)
				return (NULL);

			model.fullpath = strdupself(argv[i]);

			if (!model.fullpath)
				return (free(model.nameFile), NULL);
			
			struct stat modelstat;
	
			if (lstat(model.nameFile, &modelstat) == -1) {
				printf("%d errno, %d EACCES, %d ENOENT\n",errno, EACCES,ENOENT);
				if (errno & EACCES || errno & ENOENT) {
					fprintfSelf(2, "ft_ls cannot access '%s': No such file or directory\n", model.nameFile);
				}
				free(model.nameFile); free (model.fullpath);
			} else {
				model.last_modification = modelstat.st_mtime;
				model.sizeFile = modelstat.st_size;
				model.st_mode = modelstat.st_mode;
				if (addCmpList(&infoLs->filesList, model, &attrcmpLs, infoLs->attrLs)) {
					if (model.nameFile)
						free(model.nameFile);
					if (model.fullpath)
						free(model.fullpath);
				}
			}	
		}
	}
	return (infoLs->filesList);
}

void	*addCmpList(t_info_inode **list, t_info_inode model, t_func_cmplist cmpfunc, const int attrLs) {
	t_info_inode	*new_node;
	t_info_inode	**tracer = list;
	
	if (!list)
		return (NULL);

	if (!model.nameFile || !model.fullpath)
		return (NULL);

	new_node = (t_info_inode *)malloc(sizeof(t_info_inode));
	if (!new_node)
		return (NULL);

	new_node->nameFile = model.nameFile;
	new_node->depth = model.depth;
	new_node->attrFile = 0;
	new_node->fullpath = model.fullpath;
	new_node->last_modification = model.last_modification;
	new_node->nextFile = NULL;

	while (*tracer &&
			(*tracer)->depth == model.depth &&
			cmpfunc((*tracer), new_node, attrLs) < 0) {
		tracer = &(*tracer)->nextFile;
	}

	new_node->nextFile = *tracer;
	(*tracer) = new_node;

	return (new_node);
}

int		is_uppercase(unsigned char c) {
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

// reshape
// on ne peut pas faire identique aux meme car il faut acceder aussi a la table ascii local pour bien les triés
int		attrcmpLs(void *nodecheck, void *newnode, const int attrLs) {
	t_info_inode	*nodechecking;
	t_info_inode	*newnodecheck;
	size_t			i = 0;
	int				return_value = 0;

	nodechecking = (t_info_inode *)nodecheck;
	newnodecheck = (t_info_inode *)newnode;

	if (attrLs & ATTR_SORTBYTIME) {
		if (newnodecheck->last_modification != nodechecking->last_modification) {
			return_value = newnodecheck->last_modification - nodechecking->last_modification;

			return (attrLs & ATTR_REVERSE ? -return_value : return_value);
		}
	}

	while (nodechecking->nameFile && newnodecheck->nameFile
			&& nodechecking->nameFile[i] && newnodecheck->nameFile[i]) {
		return_value = (unsigned char)nodechecking->nameFile[i]
						- (unsigned char)newnodecheck->nameFile[i];
		if (return_value != 0)
			break ;
		i++;
	}

	return (attrLs & ATTR_REVERSE ? -return_value : return_value);
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
	fprintfSelf(2, "Attribue All hidden file: %s\n",
		(infoLs->attrLs & ATTR_ALL ? "vraie" : "faux"));
	fprintfSelf(2, "Attribue in Directory: %s\n",
		(infoLs->attrLs & ATTR_STARTDIR ? "vraie" : "faux"));
	
	t_info_inode	*tmp;
	tmp = infoLs->filesList;
	if (!tmp)
		fprintfSelf(2, "Null \n");
	while (tmp) {
		fprintfSelf(2, "file : %s | fullpath : %s -> ", tmp->nameFile, tmp->fullpath);
		printf(" | depth : %d  |  time -> %ld\n", tmp->depth, tmp->last_modification);
		tmp = tmp->nextFile;
	}
}

#include <stdlib.h>

void	freeInfoInode(t_info_inode **list) {
	t_info_inode	*current;
	t_info_inode	*next_node;

	if (!list || !*list)
		return ;
	
	current = *list;
	while (current != NULL) {
		next_node = current->nextFile;
		
		if (current->nameFile)
			free(current->nameFile);
		if (current->fullpath)
			free(current->fullpath);

		free(current);
		current = next_node;
	}

	*list = NULL;
}
