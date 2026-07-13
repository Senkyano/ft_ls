/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printinfols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:36:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/07/13 13:54:12 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <time.h>
#include <stdio.h>

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
	int				act_depth = 0;

	tmp = infoLs->filesList;
	while (tmp) {
		if ((tmp->attrFile & ATTR_DIRECTORY) && act_depth == tmp->depth) {
			fprintfSelf(1 ,"%s:\n", tmp->nameFile);
			act_depth = tmp->depth + 1;
		}
		else {
			if (infoLs->attrLs & ATTR_LONGFORMAT) {
				mode_t	modeFile = tmp->st_mode;
				printaccessfile(modeFile);
				fprintfSelf(1, "%c%c%c%c%c%c%c%c%c", (S_IRUSR & modeFile) ? 'r' : '-',
													 (S_IWUSR & modeFile) ? 'w' : '-',
													 (S_IXUSR & modeFile) ? 'x' : '-',
													 (S_IRGRP & modeFile) ? 'r' : '-',
													 (S_IWGRP & modeFile) ? 'w' : '-',
													 (S_IXGRP & modeFile) ? 'x' : '-',
													 (S_IROTH & modeFile) ? 'r' : '-',
													 (S_IWOTH & modeFile) ? 'w' : '-',
													 (S_IXOTH & modeFile) ? 'x' : '-');
				fprintfSelf(1, ". ");
				char *temp = ctime(&tmp->last_modification);

				int	i = strlenSelf(temp) - 1;

				while (i && temp[i] != ':') {
					temp[i] = 0;
					i--;
				}
				temp[i] = 0;
				printf("%ld ", tmp->sizeFile);
				fprintfSelf(1, "%s ", temp);
			}
			fprintfSelf(1, "%c%s%c",containSpecial(tmp->nameFile) ? '\'' : '\0', 
									tmp->nameFile,
									containSpecial(tmp->nameFile) ? '\'' : '\0');
		}
		if (tmp->nextFile)
			fprintfSelf(1, (infoLs->attrLs & ATTR_LONGFORMAT ? "\n" : "   "));
		tmp = tmp->nextFile;
		if (tmp && act_depth > tmp->depth) {
			fprintfSelf(1, "\n\n");
			act_depth = tmp->depth;
		}
	}
	if (infoLs->filesList)
		fprintfSelf(1, "\n");
}
