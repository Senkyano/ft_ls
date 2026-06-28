/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exploringfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:31:50 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/28 21:39:22 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int	exploringInfo(t_info_ls *infoLs) {
	DIR				*dossier;
	struct dirent	*element;
	t_info_inode	*directory;
	t_info_inode	*nextfile;
	t_info_inode	model = {0};

	if (!(infoLs->attrLs & ATTR_STARTDIR)) {
		dossier = opendir(".");
		if (!dossier) {
			fprintfSelf(2, "Impossible d'ouvrir le dossier\n");
			return (1);
		}
	
		while ((element = readdir(dossier)) != NULL) {
			model.nameFile = strdupself(element->d_name);
			if (!model.nameFile) {
				fprintfSelf(2, "Error malloc\n");
				return (1);
			}
			if (!(infoLs->attrLs & ATTR_ALL) && model.nameFile[0] == '.') {
				free(model.nameFile);
				model.nameFile = NULL;
			}
			model.depth = 0;
			addCmpList(&infoLs->filesList, model, &strcmpLs);
		}
	
		closedir(dossier);
	} else {
		directory = infoLs->filesList;
		while (directory) {
			nextfile = directory->nextFile;
			dossier = opendir(directory->nameFile);
			if(dossier) {
				directory->attrFile |= ATTR_DIRECTORY;
				while ((element = readdir(dossier)) != NULL) {
					model = *directory;
					model.nameFile = strdupself(element->d_name);
					if (!model.nameFile) {
						fprintfSelf(2, "Error malloc\n");
						return (1);
					}
					if (!(infoLs->attrLs & ATTR_ALL) && model.nameFile[0] == '.') {
						free(model.nameFile);
						model.nameFile = NULL;
					}
					model.depth = directory->depth + 1;
					addCmpList(&directory->nextFile, model, &strcmpLs);
				}
				closedir(dossier);
			}
			dossier = NULL;
			directory = nextfile;
		}
	}

	return (0);
}
