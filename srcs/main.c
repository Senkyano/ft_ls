/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 14:59:14 by rihoy             #+#    #+#             */
/*   Updated: 2026/07/13 14:32:52 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include "ls.h"

// void	actionPrint(t_info_ls *infoLs) {
// 	DIR *dossier = opendir(infoLs->currentDir);

// }

int main(const int argc, const char **argv) {
	t_info_ls	infoLs = {0}; // initialisation moderne
	(void)argc; (void)argv; (void)infoLs;

	parsingInfoLs(argc, argv, &infoLs);
	exploringInfo(&infoLs);
	// seeInfo(&infoLs);
	printInfoLs(&infoLs);
	freeInfoInode(&infoLs.filesList);
	fprintfSelf(1, "%d\n", -2147483648);
	return (0);
}
