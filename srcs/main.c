/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 14:59:14 by rihoy             #+#    #+#             */
/*   Updated: 2026/08/11 16:47:30 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include "ls.h"
#include <locale.h>

// void	actionPrint(t_info_ls *infoLs) {
// 	DIR *dossier = opendir(infoLs->currentDir);

// }

int main(const int argc, const char **argv) {
	t_info_ls	infoLs = {0}; // initialisation moderne
	(void)argc; (void)argv; (void)infoLs;

	if (isatty(STDOUT_FILENO) != 1) {
		infoLs.attrLs |= ATTR_REDIRECTION;
	}

	setlocale(LC_ALL, "");

	parsingInfoLs(argc, argv, &infoLs);
	exploringInfo(&infoLs);
	// seeInfo(&infoLs);
	printInfoLs(&infoLs);
	freeInfoInode(&infoLs.filesList);
	fprintfSelf(1, "\n\n%d\n\n", 1);
	return (0);	
}
