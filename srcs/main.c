/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 14:59:14 by rihoy             #+#    #+#             */
/*   Updated: 2026/08/13 10:38:10 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include "ls.h"
#include <locale.h>
#include <sys/ioctl.h>

// void	actionPrint(t_info_ls *infoLs) {
// 	DIR *dossier = opendir(infoLs->currentDir);

// }

int main(const int argc, const char **argv) {
	t_info_ls	infoLs = {0}; // initialisation moderne

	if (isatty(STDOUT_FILENO) != 1) {
		infoLs.attrLs |= ATTR_REDIRECTION;
	}

	setlocale(LC_ALL, "");

	struct winsize	w;
	infoLs.windows_width = 80;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 0) {
		infoLs.windows_width = w.ws_col;
	}

	parsingInfoLs(argc, argv, &infoLs);
	exploringInfo(&infoLs);
	seeInfo(&infoLs);
	// printInfoLs(&infoLs);
	freeInfoInode(&infoLs.filesList);
	return (0);	
}
