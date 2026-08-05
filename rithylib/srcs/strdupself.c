/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdupself.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:01:28 by rihoy             #+#    #+#             */
/*   Updated: 2026/06/16 16:19:07 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdio.h>
#include <stdlib.h>

char	*strdupself(const char *src)
{
	char	*copy;
	size_t	len;
	size_t	i;

	i = -1;
    len = 0;
    while (src[len])
        len++;
    copy = malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (++i < len && src[i] != '\0') {
		copy[i] = src[i];
    }
	copy[i] = '\0';
	return (copy);
}
