/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 14:59:14 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/26 14:56:07 by rihoy            ###   ########.fr       */
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
	seeInfo(&infoLs);
	freeInfoInode(&infoLs.filesList);
	return (0);
}
