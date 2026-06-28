/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printinfols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:36:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/28 21:48:47 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	printInfoLs(t_info_ls *infoLs) {
	t_info_inode	*tmp;
	int				act_depth = 0;

	tmp = infoLs->filesList;
	if (infoLs->attrLs & ATTR_RECURSIVE)
		fprintfSelf(1, ".:\n");
	while (tmp) {
		if ((tmp->attrFile & ATTR_DIRECTORY) && act_depth == tmp->depth) {
			fprintfSelf(1 ,"%s:\n", tmp->nameFile);
			act_depth = tmp->depth + 1;
		}
		else {
			fprintfSelf(1 ,"%s", tmp->nameFile);
		}
		if (tmp->nextFile)
			fprintfSelf(1, " ");
		tmp = tmp->nextFile;
		if (tmp && act_depth > tmp->depth) {
			fprintfSelf(1, "\n\n");
			act_depth = tmp->depth;
		}
	}
	fprintfSelf(1, "\n");
}
