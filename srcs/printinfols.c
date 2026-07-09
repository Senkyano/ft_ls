/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printinfols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:36:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/07/09 23:29:35 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <time.h>
#include <stdio.h>

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
				char *temp = ctime(&tmp->last_modification);

				int	i = strlenSelf(temp) - 1;

				while (i && temp[i] != ':') {
					temp[i] = 0;
					i--;
				}
				temp[i] = 0;
				fprintfSelf(1, "%s ", temp);
			}
			fprintfSelf(1, "%c",containSpecial(tmp->nameFile) ? '\'' : '\0');
			fprintfSelf(1 ,"%s", tmp->nameFile);
			fprintfSelf(1, "%c",containSpecial(tmp->nameFile) ? '\'' : '\0');
		}
		if (tmp->nextFile)
			fprintfSelf(1, (infoLs->attrLs & ATTR_LONGFORMAT ? "\n" : "   "));
		tmp = tmp->nextFile;
		if (tmp && act_depth > tmp->depth) {
			fprintfSelf(1, "\n\n");
			act_depth = tmp->depth;
		}
	}
	fprintfSelf(1, "\n");
}
