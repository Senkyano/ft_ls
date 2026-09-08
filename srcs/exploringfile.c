/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exploringfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:31:50 by rihoy             #+#    #+#             */
/*   Updated: 2026/09/07 14:00:34 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	exploringInfo(t_info_ls *infoLs) {
	DIR				*dossier;
	struct dirent	*element;
	// t_info_inode	*directory;
	// t_info_inode	*nextfile;
	t_info_inode	model = {0};

	if (!(infoLs->attrLs & ATTR_STARTDIR)) {
		dossier = opendir(".");
		if (!dossier) {
			fprintfSelf(2, "Impossible d'ouvrir le dossier\n");
			return (1);
		}
	
		while ((element = readdir(dossier)) != NULL) {
			if (!(infoLs->attrLs & ATTR_ALL) && element->d_name[0] == '.')
				continue;

			model.nameFile = strdupself(element->d_name);
			if (!model.nameFile) {
				fprintfSelf(2, "Error malloc\n");
				closedir(dossier);
				return (1);
			}

			struct stat modelstat;

			if (lstat(model.nameFile, &modelstat) == -1) {
				if (errno == EACCES || errno == ENOENT) {
					fprintfSelf(2, "ft_ls cannot access '%s': No such file or directory\n", model.nameFile);
				}
				free(model.nameFile);
				model.nameFile = NULL;
				continue;
			}
			model.fullpath = joinstrwsep(".", "/", element->d_name);
			if (!model.fullpath) {
				free(model.nameFile);
				closedir(dossier);
				return (1);
			}

			model.depth = 0;
			model.last_modification = modelstat.st_mtime;
			model.nblink = modelstat.st_nlink;
			model.userId = modelstat.st_uid;
			model.grId = modelstat.st_gid;
			model.sizeFile = modelstat.st_size;
			model.st_block = modelstat.st_blocks;
			model.st_mode = modelstat.st_mode;
			if (!addCmpList(&infoLs->filesList, model, &attrcmpLs, infoLs->attrLs)) {
				if (model.nameFile)
					free(model.nameFile);
				if (model.fullpath)
					free(model.fullpath);
			}
		}

		closedir(dossier);
	}
	// else {
	// 	directory = infoLs->filesList;
	// 	while (directory) {
	// 		nextfile = directory->nextFile;
	// 		dossier = opendir(directory->nameFile);
	// 		if(dossier) {
	// 			directory->attrFile |= ATTR_DIRECTORY;
	// 			while ((element = readdir(dossier)) != NULL) {
	// 				model = *directory;
	// 				model.nameFile = strdupself(element->d_name);
	// 				if (!model.nameFile) {
	// 					fprintfSelf(2, "Error malloc\n");
	// 					return (1);
	// 				}
	// 				if (!(infoLs->attrLs & ATTR_ALL) && model.nameFile[0] == '.') {
	// 					free(model.nameFile);
	// 					model.nameFile = NULL;
	// 				}
	// 				model.depth = directory->depth + 1;
	// 				addCmpList(&directory->nextFile, model, &attrcmpLs, infoLs->attrLs);
	// 			}
	// 			closedir(dossier);
	// 		}
	// 		dossier = NULL;
	// 		directory = nextfile;
	// 	}
	// }

	return (0);
}
