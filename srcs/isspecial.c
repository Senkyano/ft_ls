/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isspecial.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 22:39:18 by rihoy             #+#    #+#             */
/*   Updated: 2026/07/09 22:44:12 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdbool.h>

bool	isspecialchar(char c) {
	
	if (c <= 32 || c == 127)
		return (1);
	
	if (c == '*' || c == '?' || c == '\\' || c == '\'' || c == '"' ||
		c == '$' || c == '&' || c == ';'  || c == '|'  || c == '<' ||
		c == '>' || c == '(' || c == ')'  || c == '!'  || c == '#' ||
		c == '~' || c == '{' || c == '}'  || c == '['  || c == ']') {
		return (1);
	}

	return (0);
}

bool	containSpecial(char *str) {
	size_t	i = 0;
	
	if (!str) {
		return (0);
	}

	while (str[i]) {
		if (isspecialchar(str[i]))
			return (1);
		i++;
	}
	return (0);
}
