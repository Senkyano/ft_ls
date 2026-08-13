/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 22:03:50 by rihoy             #+#    #+#             */
/*   Updated: 2026/08/13 10:57:46 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rithylib.h"
#include <stdlib.h>

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

char	*joinstrwsep(char *str1, char *sep, char *str2) {
	size_t	total_len;
	int		i = 0, j = 0, k = 0;
	char	*newstr;

	total_len = str1 ? strlenSelf(str1) : 0;
	total_len += sep ? strlenSelf(sep) : 0;
	total_len += str2 ? strlenSelf(str2) : 0;
	
	if (total_len <= 0)
		return (NULL);
	newstr = (char *)malloc((sizeof(char) * (total_len + 1)));
	if (!newstr)
		return (NULL);
	
	while (str1 && str1[i]) {
		newstr[i] = str1[i];
		i++;
	}
	while (sep && sep[j]) {
		newstr[i] = sep[j];
		i++; j++;
	}
	while (str2 && str2[k]) {
		newstr[i] = str2[k];
		i++; k++;
	}

	newstr[i] = '\0';

	return (newstr);
}