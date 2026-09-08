/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printinfols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:36:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/09/08 18:22:39 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <time.h>
#include <stdio.h>
#include "color.h"
#include <grp.h>
#include <dirent.h>


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
	t_info_inode	*tmp;
	t_info_inode	*treatment;
	// DIR				*dossier;
	// struct dirent	*element;
	t_info_high		hightest = {0};
	int				act_depth = 0;
	// static unsigned int	lenght_line;

	tmp = infoLs->filesList;
	if (infoLs->attrLs & ATTR_RECURSIVE)
		fprintfSelf(1, ".:\n");
		
	treatment = tmp;
	while (treatment) {
		if (treatment->depth == act_depth) {
			size_t	treatLen = lenNumber(treatment->sizeFile, 10);
			size_t	treatLenblink = lenNumber(treatment->nblink, 10);
			hightest.max_char_sizeFile = treatLen > (size_t)hightest.max_char_sizeFile ? (int)treatLen : hightest.max_char_sizeFile;
			hightest.max_char_nblink = treatLenblink > (size_t)hightest.max_char_nblink ? (int)treatLenblink : hightest.max_char_nblink;
			hightest.total_stblock += treatment->st_block;
		}
		treatment = treatment->nextFile;
	}
	if (infoLs->attrLs & ATTR_LONGFORMAT)
		fprintfSelf(1, "total %d\n", (int)(hightest.total_stblock / 2));
	while (tmp) {
		print_infofile(infoLs->attrLs, tmp, hightest);
		if (tmp->nextFile && (infoLs->attrLs & (ATTR_REDIRECTION | ATTR_LONGFORMAT))) {
			fprintfSelf(1, "\n");
		} else if (tmp->nextFile) {
			fprintfSelf(1, "   ");
		}
		tmp = tmp->nextFile;
	}
// in directory for -R

	tmp = infoLs->filesList;
	while (tmp) {
		tmp = tmp->nextFile;
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
		int n = hightest.max_char_nblink - lenNumber(file->nblink, 10);
		while (n) {
			fprintfSelf(1, " ");n--;
		}
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

		n = hightest.max_char_sizeFile - lenNumber(file->sizeFile, 10);
		while (n) {
			fprintfSelf(1, " ");n--;
		}
		fprintfSelf(1 ,"%d", file->sizeFile);
		fprintfSelf(1, "%s ", temp + 3);
	}
	bool	specialcaracteres;
	specialcaracteres = containSpecial(file->nameFile);

	if (specialcaracteres && !(attr & ATTR_REDIRECTION))
		fprintfSelf(1, "'");
	fprintfSelf(1, "%s", file->nameFile);
	if (specialcaracteres && !(attr & ATTR_REDIRECTION))
		fprintfSelf(1, "'");
	return (strlenSelf(file->nameFile));
}
