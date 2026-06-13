/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:29:57 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/14 01:25:27 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "ls.h"

void	setAttr(const char *str, t_info_ls *infoLs) {
	static const int ascii_table[256] = {
		['a'] = ATTR_ALL,
		['r'] = ATTR_REVERSE,
		['R'] = ATTR_RECURSIVE,
		['t'] = ATTR_SORTBYTIME,
		['l'] = ATTR_LONGFORMAT,
	};

	while (*(++str) != '\0') {
		int flag = ascii_table[(unsigned char)*str];
		
		if (!flag) {
			fprintfSelf(2, "ls: invalid option -- '%c'\n", *str);
			exit(2);
		}

		infoLs->attrLs |= flag;
	}
}

void	parsingInfoLs(int argc, char **argv, t_info_ls *infoLs) {
	(void)argc; (void)argv; (void)infoLs;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			setAttr(argv[i], infoLs);
		} else {
			
		}
	}
}