/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printinfols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:36:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/07/30 15:57:10 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <time.h>
#include <stdio.h>
#include "color.h"
#include <grp.h>

void	printaccessfile(mode_t st_mode) {
	if (S_ISREG(st_mode)) {
		fprintfSelf(1, "%c", '-');
	} else if (S_ISDIR(st_mode)) {		
		fprintfSelf(1, "%c", 'd');
	} else if (S_ISCHR(st_mode)) {
		fprintfSelf(1, "%c", 'l');
	} else if (S_ISBLK(st_mode)) {
		fprintfSelf(1, "%c", 'c');
	} else if (S_ISFIFO(st_mode)) {
		fprintfSelf(1, "%c", 'b');
	} else if (S_ISLNK(st_mode)) {
		fprintfSelf(1, "%c", 'p');
	} else if (S_ISSOCK(st_mode)) {
		fprintfSelf(1, "%c", 's');
	}
}

void	printInfoLs(t_info_ls *infoLs) {
	t_info_inode	*tmp;
	// DIR				*dossier;
	// struct dirent	*element;
	int				act_depth = 0;
	t_info_high		hightest = {0};

	tmp = infoLs->filesList;
	if (!(infoLs->attrLs & ATTR_RECURSIVE)) {
		while (tmp) {
			if (infoLs->attrLs & ATTR_LONGFORMAT) {
				if (tmp->depth == act_depth) {
					// calcul lenght of number
				}
			}
			if ((tmp->attrFile & ATTR_DIRECTORY) && act_depth == tmp->depth) {
				fprintfSelf(1 ,"%s:\n", tmp->nameFile);
				act_depth = tmp->depth + 1;
			}
			else {
				if (infoLs->attrLs & ATTR_LONGFORMAT) {
					mode_t	modeFile = tmp->st_mode;
					printaccessfile(modeFile);
					fprintfSelf(1, "%c%c%c%c%c%c%c%c%c ", (S_IRUSR & modeFile) ? 'r' : '-',
														 (S_IWUSR & modeFile) ? 'w' : '-',
														 (S_IXUSR & modeFile) ? 'x' : '-',
														 (S_IRGRP & modeFile) ? 'r' : '-',
														 (S_IWGRP & modeFile) ? 'w' : '-',
														 (S_IXGRP & modeFile) ? 'x' : '-',
														 (S_IROTH & modeFile) ? 'r' : '-',
														 (S_IWOTH & modeFile) ? 'w' : '-',
														 (S_IXOTH & modeFile) ? 'x' : '-');
					fprintfSelf(1, "%d ", tmp->nblink);
					char *temp = ctime(&tmp->last_modification);
	
					int	i = strlenSelf(temp) - 1;
	
					// Print time month date time
					while (i && temp[i] != ':') {
						temp[i] = 0;
						i--;
					}
					temp[i] = 0;
					// proprietaire
					struct passwd *uid;
					uid = getpwuid(tmp->userId);
					fprintfSelf(1, "%s ", uid->pw_name);
					// gr
					struct group *gid;
					gid = getgrgid(tmp->grId);
					fprintfSelf(1, "%s ", gid->gr_name);
	
					fprintfSelf(1 ,"%d ", tmp->sizeFile);
					fprintfSelf(1, "%s ", temp);
				}
				// a modifier pour correspondre \t\n etc
				if (containSpecial(tmp->nameFile))
					fprintfSelf(1, "'");
				fprintfSelf(1, "%s", tmp->nameFile);
				if (containSpecial(tmp->nameFile))
					fprintfSelf(1, "'");
			}
			if (tmp->nextFile) {
				// si il y a une redirection on fait un \n aux lieux de l'autre
				fprintfSelf(1, "%s", (infoLs->attrLs & ATTR_LONGFORMAT ? "\n" : "  "));
			}
			tmp = tmp->nextFile;
			if (tmp && act_depth > tmp->depth) {
				fprintfSelf(1, "\n\n");
				act_depth = tmp->depth;
			}
		}
	}
	if (infoLs->filesList)
		fprintfSelf(1, "\n");
}
