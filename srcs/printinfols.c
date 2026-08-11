/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printinfols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:36:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/08/11 16:48:06 by rihoy            ###   ########.fr       */
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

int	print_infofile(const int attr, t_info_inode *file, const t_info_high hightest);

void	printInfoLs(t_info_ls *infoLs) {
	(void)infoLs;
	t_info_inode	*tmp;
	// DIR				*dossier;
	// struct dirent	*element;
	int				act_depth = 0;
	t_info_high		hightest = {0};
	static int	lenght_line;

	(void)hightest;
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
				lenght_line += print_infofile(infoLs->attrLs, tmp, hightest);
				if (lenght_line > 81 && tmp->nextFile) {
					fprintfSelf(1, "\n");
					lenght_line = 0;
				}
			}
			if (tmp->nextFile) {
				// si il y a une redirection on fait un \n aux lieux de l'autre
				fprintfSelf(1, "%s", (infoLs->attrLs & ATTR_LONGFORMAT || infoLs->attrLs & ATTR_REDIRECTION ? "\n" : "   "));
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

int	print_infofile(const int attr, t_info_inode *file, const t_info_high hightest) {
	(void)hightest;
	if (attr & ATTR_LONGFORMAT) {
		mode_t	modeFile = file->st_mode;
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
		fprintfSelf(1, "%d ", file->nblink);
		char *temp = ctime(&file->last_modification);

		int	i = strlenSelf(temp) - 1;

		// Print time month date time
		while (i && temp[i] != ':') {
			temp[i] = 0;
			i--;
		}
		temp[i] = 0;
		// proprietaire
		struct passwd *uid;
		uid = getpwuid(file->userId);
		fprintfSelf(1, "%s ", uid->pw_name);
		// gr
		struct group *gid;
		gid = getgrgid(file->grId);
		if (gid->gr_name)
			fprintfSelf(1, "%s ", gid->gr_name);

		fprintfSelf(1 ,"%d ", file->sizeFile);
		fprintfSelf(1, "%s ", temp);
	}
	bool	specialcaracteres;
	specialcaracteres = containSpecial(file->nameFile);

	if (specialcaracteres)
		fprintfSelf(1, "'");
	fprintfSelf(1, "%s", file->nameFile);
	if (specialcaracteres)
		fprintfSelf(1, "'");
	return (strlenSelf(file->nameFile));
}
