/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 22:03:50 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/28 22:29:02 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdlib.h>

size_t	strlenSelf(char *str) {
	size_t	x = 0;

	if (!str)
		return (x);

	while (str[x])
		x++;
	return (x);
}

char	*strjoin_save(char *str, char *str2) {
	size_t	len1;
	size_t	len2;
	char	*newstr;
	size_t	i;
	size_t	j;

	len1 = str ? strlenSelf(str) : 0;
	len2 = str2 ? strlenSelf(str2) : 0;

	newstr = (char *)malloc((sizeof(char) * (len1 + len2 + 1)));
	if (!newstr)
		return (NULL);

	i = 0;
	while (str && str[i]) {
		newstr[i] = str[i];
		i++;
	}
	
	j = 0;
	while (str2 && str2[j]) {
		newstr[i] = str2[j];
		i++;
		j++;
	}

	newstr[i] = '\0';

	return (newstr);
}
